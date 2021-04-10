
/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_INCLUDED
#define DH_UNITS_QUANTITY_INCLUDED

#include <cstdint>
#include <string>
#include <chrono>
#include <cmath>
#include "dh/units/traits.hpp"
#include "dh/units/quantity_conversion.hpp"

namespace dh {
namespace units {

template<typename REP, typename... UNITS>
class quantity {
public:
    using value_type = REP;

    using quantity_type = quantity;
    
    using original_unit_list = mpl::list<UNITS...>;
    
    using unit_list = extract_base_units_t<UNITS...>;

    template<typename,typename...> friend class quantity;

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity(const other& in) : 
    value_{in.count() * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value} 
    {
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity(other&& in) : 
    value_{std::move(in.value_) * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value} 
    {
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity& operator=(const other& in) {
        value_ = in.count() * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity& operator=(other&& in) {
        value_ = std::move(in.value_);
        value_ *= unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value;
        return *this;
    }

    template<typename REP2,
        typename = typename std::enable_if< std::is_arithmetic<REP2>::value >::type >
    quantity& operator*=(const REP2& in) {
        value_ *= in;
        return *this;
    }

    template<typename REP2,
        typename = typename std::enable_if< std::is_arithmetic<REP2>::value >::type >
    quantity& operator/=(const REP2& in) {
        value_ /= in;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity<REP,UNITS...>,other>::value>::type >
    quantity& operator+=(const other& in) {
        value_ += in.count()* unit_list_conversion_factor<REP,unit_list, typename other::unit_list >::value;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity<REP,UNITS...>,other>::value>::type >
    quantity& operator-=(const other& in) {
        value_ -= in.count()* unit_list_conversion_factor<REP,unit_list, typename other::unit_list >::value;
        return *this;
    }

    explicit constexpr quantity(const REP& in) : value_{in} 
    {}

    explicit constexpr quantity(REP&& in) : value_{std::move(in)} 
    {}

    constexpr quantity()
    {}

    REP& count() {
        return value_;
    }

    const REP& count() const {
        return value_;
    }

    template<typename A, typename = typename std::enable_if<std::is_convertible<REP,A>::value>::type>
    explicit operator A() const {
        return value_;
    }

private:
    REP value_{};
};

// Add/subtract two quantities

template<typename Scalar, typename Quantity>
using promote_quantity_t = typename mpl::conditional< std::is_same<typename Quantity::value_type, common_value_type_t<Scalar,Quantity> >::value >:: template type<
    Quantity,
    typename Quantity::unit_list:: template wrap< ::dh::units::quantity , common_value_type_t<Scalar,Quantity> >>;

template<typename LHS, typename RHS>
using addition_return_t = typename mpl::conditional< 
        mpl::larger_than_one( unit_list_conversion_factor<common_quantity_representation_t<LHS,RHS>, typename LHS::unit_list, typename RHS::unit_list>::value ) >::
        template type<
            promote_quantity_t<common_quantity_representation_t<LHS,RHS> ,LHS>,
            promote_quantity_t<common_quantity_representation_t<LHS,RHS> ,RHS>
        >;

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
auto operator+ (const LHS& a, const RHS& b ) 
-> addition_return_t<LHS,RHS>
{
    addition_return_t<LHS,RHS> a_conv(a);
    a_conv += b;
    return a_conv;
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
auto operator- (const LHS& a, const RHS& b ) 
-> addition_return_t<LHS,RHS>
{
    addition_return_t<LHS,RHS> a_conv(a);
    a_conv -= b;
    return a_conv;
}

// multiply by scalar
template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator* (const Scalar& a, const T& b ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(a*b.count());
}

template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator* ( const T& b, const Scalar& a ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(a*b.count());
}

// division with scalar
template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator/ ( const T& b, const Scalar& a ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(b.count()/a);
}

template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator/ (const Scalar& a, const T& b ) 
-> typename std::decay<decltype(std::declval<::dh::units::quantity<Scalar>>()/std::declval<T>())>::type {
    return ::dh::units::quantity<Scalar>(a)/b;
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T operator-(const T &a) {
    return  T{-a.count()};
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T operator+(const T &a) {
    return a;
}

// multiply two quantities

template<typename LHS, typename RHS>
using multiplication_result_t = typename multiplication_result<typename LHS::unit_list,typename RHS::unit_list>::
    template type<dh::units::quantity,typename std::common_type<typename LHS::value_type,typename RHS::value_type>::type>;

template<typename LHS, typename RHS>
using division_result_t = typename division_result<typename LHS::unit_list,typename RHS::unit_list>::
    template type<dh::units::quantity,typename std::common_type<typename LHS::value_type,typename RHS::value_type>::type>;


template<typename LHS, typename RHS, typename = typename std::enable_if<is_dh_quantity<LHS>::value && is_dh_quantity<RHS>::value>::type >
auto operator* (const LHS& a, const RHS& b ) 
-> multiplication_result_t<LHS,RHS> {
    using rv_t = multiplication_result_t<LHS,RHS>;
    const auto factor = compute_multiply_conversion_factor<typename rv_t::value_type>(typename LHS::unit_list{},typename RHS::unit_list{});
    return rv_t{factor*a.count()*b.count()};
}

template<typename LHS, typename RHS, typename = typename std::enable_if<is_dh_quantity<LHS>::value && is_dh_quantity<RHS>::value>::type >
auto operator/ (const LHS& a, const RHS& b ) 
-> division_result_t<LHS,RHS> {
    using rv_t = division_result_t<LHS,RHS>;
    const auto factor = compute_division_conversion_factor<typename rv_t::value_type>(typename LHS::unit_list{},typename RHS::unit_list{});
    return rv_t{factor*a.count()/b.count()};
}

// integration with std::chrono
// mult

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator* (const std::chrono::duration<REP1,RATIO>& a, const Quantity& b ) 
-> multiplication_result_t<quantity<REP1,unit<dimensions::time,RATIO,1>>,Quantity > {
    return quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count())*b;
}

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator* (const Quantity& b, const std::chrono::duration<REP1,RATIO>& a ) 
-> multiplication_result_t<quantity<REP1,unit<dimensions::time,RATIO,1>>,Quantity > {
    return quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count())*b;
}

// division 

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator/ (const Quantity& b, const std::chrono::duration<REP1,RATIO>& a ) 
-> division_result_t<Quantity,quantity<REP1,unit<dimensions::time,RATIO,1>> > {
    return b/quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count());
}

// add

template <typename T, typename = void>
struct is_time_quantity : std::false_type {};
template <typename T>
struct is_time_quantity<T, dh::mpl::void_t<typename T::value_type,
    typename T::quantity_type, typename T::unit_list, decltype(std::declval<T>().count()) >>
{
    using time_type = dh::units::unit<dimensions::time,std::ratio<1,1>,1>;
    constexpr static bool value = lists_contain_same_dimensions<dh::mpl::list< time_type >, typename T::unit_list>::value;
};


template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator+ (const std::chrono::duration<REP,RATIO>& a, const T& b ) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())+b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator+ (const T& b, const std::chrono::duration<REP,RATIO>& a) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())+b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator- (const std::chrono::duration<REP,RATIO>& a, const T& b ) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())-b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator- (const T& b, const std::chrono::duration<REP,RATIO>& a) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return b-quantity<REP,unit<dimensions::time,RATIO,1>>(a.count());
}


// comparisons
// hoping that the compiler will remove useless conversions

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator ==(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() == b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator !=(const LHS &a, const RHS &b) {
    return !(a == b);
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator <(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() < b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator >(const LHS &a, const RHS &b) {
    return b<a;
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator <=(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() <= b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator >=(const LHS &a, const RHS &b) {
    return b <= a;
}

template <typename T = double>
class scalar : public
::dh::units::quantity<T>
{
public:
    using base_type = ::dh::units::quantity<T>;
    using base_type::base_type;
    using value_type = T;
    scalar(const base_type& q) : base_type(q) {}
    scalar(base_type&& q) : base_type(std::move(q)) {}
    scalar() = default;
    scalar(const scalar&) = default;
    scalar(scalar&&) = default;
    scalar& operator=(const scalar&) = default;
    scalar& operator=(scalar&&) = default;
    ~scalar() = default;

    operator T() const {
        return this->count();
    }
};


}
}

#endif /* DH_UNITS_QUANTITY_INCLUDED */
