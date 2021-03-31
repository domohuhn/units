#include <iostream>
#include <iomanip>
#include <string_view>
#include <ratio>

struct DimMeter {
    static std::string to_string() {
        return "m";
    }
};


struct DimTime {
    static std::string to_string() {
        return "s";
    }
};

struct DimAngle {
    static std::string to_string() {
        return "°";
    }
};

template <typename Ratio>
inline std::string to_string() {
    double frac = (double)Ratio::num / (double)Ratio::den;
    std::string rv(15U,0);
    int cx = snprintf( &rv[0], 15U ,"*%.2e",frac);
    rv.resize(cx);
    return rv;
}

template <>
inline std::string to_string<std::atto>() {
    return "a";
}

template <>
inline std::string to_string<std::femto>() {
    return "f";
}

template <>
inline std::string to_string<std::pico>() {
    return "p";
}

template <>
inline std::string to_string<std::nano>() {
    return "n";
}

template <>
inline std::string to_string<std::micro>() {
    return "u";
}

template <>
inline std::string to_string<std::milli>() {
    return "m";
}

template <>
inline std::string to_string<std::centi>() {
    return "c";
}

template <>
inline std::string to_string<std::deci>() {
    return "d";
}

template <>
inline std::string to_string<std::ratio<1,1>>() {
    return "";
}

template <>
inline std::string to_string<std::deca>() {
    return "da";
}

template <>
inline std::string to_string<std::hecto>() {
    return "h";
}

template <>
inline std::string to_string<std::kilo>() {
    return "k";
}

template <>
inline std::string to_string<std::mega>() {
    return "M";
}

template <>
inline std::string to_string<std::giga>() {
    return "G";
}

template <>
inline std::string to_string<std::tera>() {
    return "T";
}

template <>
inline std::string to_string<std::peta>() {
    return "P";
}

template <>
inline std::string to_string<std::exa>() {
    return "E";
}


// ======================================================
namespace detail {
template<typename Dim, typename Ratio, intmax_t Power>
class unit {
public:
    using dimension_type = Dim;
    using prefix_type = typename Ratio::type;
    static constexpr intmax_t power_value = Power;

    static std::string to_string() {
        if(Power == 0) {
            return "";
        }
        std::string rv = ::to_string<Ratio>()+Dim::to_string();
        if(Power == 1) {
            return rv;
        }
        else {
            return rv+"^"+std::to_string(Power);
        }
    }
};


template<typename Dim, typename Ratio, intmax_t Power>
std::string to_string( unit<Dim,Ratio,Power> ) {
    if(Power==1) {
        return ::to_string<Ratio>()+Dim::to_string();
    }
    else {
        return ::to_string<Ratio>()+Dim::to_string()+"^"+std::to_string(Power);
    }
}

template<typename Representation, typename UnitTo, typename UnitFrom>
struct conversion_helper {
    static constexpr Representation conversion_factor() noexcept {
       // static_assert(std::is_same<UnitTo,UnitFrom>::value,"These units cannot be converted using a simple factor!");
        return Representation{1};
    }
};


template<typename REP, typename R1, typename R2>
constexpr REP conversion_factor_impl() noexcept {
    return (REP)(R2::num*R1::den)/(REP)(R1::num*R2::den);
}

template<typename REP, typename R1, typename R2>
constexpr REP conversion_factor_impl_inv() noexcept {
    return (REP)(R1::num*R2::den)/(REP)(R2::num*R1::den);
}


template<typename Functor>
struct loop_to_zero {
    static constexpr typename Functor::value_type result(intmax_t index) {
        return index>0 ? Functor::call(true)*result(index-1) : 
        (index<0? Functor::call(false)*result(index+1) : 1);
    };
};

constexpr bool greater_than_zero(intmax_t p) noexcept {
    return p>0;
}

template<typename Representation, typename RatioTo, typename RatioFrom>
struct unit_conversion_functor {
    using value_type = Representation;
    using ratio_to = RatioTo;
    using ratio_from = RatioFrom;

    static constexpr value_type call(bool b) {
        return b ? conversion_factor_impl<value_type,ratio_to,ratio_from>() :
        conversion_factor_impl_inv<value_type,ratio_to,ratio_from>();
    }
};

template<typename Representation, typename Dim, typename RatioTo, intmax_t Power, typename RatioFrom>
struct conversion_helper<Representation,unit<Dim,RatioTo,Power>,unit<Dim,RatioFrom,Power>> {
    static constexpr Representation conversion_factor() noexcept {
        return loop_to_zero<unit_conversion_functor<Representation,RatioTo,RatioFrom> >::result(Power);
    }
};

constexpr intmax_t pow = 10;
constexpr double get_factor() {
    return conversion_helper<double,unit<DimMeter,std::ratio<1,1>,pow>,unit<DimMeter,std::ratio<10,1>,pow>>::conversion_factor();
}

double get_factor2() {
    return get_factor();
}

template<typename U1, typename U2>
struct check_dim {
    using type = typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;
    constexpr static bool value = type::value;
};

using meter = unit<DimMeter,std::ratio<1,1>,1>;
using millimeter = unit<DimMeter,std::ratio<1,1000>,1>;
using second = unit<DimTime,std::ratio<1,1>,1>;
using per_second = unit<DimTime,std::ratio<1,1>,-1>;
using degree = unit<DimAngle,std::ratio<1,1>,1>;
using arcmin = unit<DimAngle,std::ratio<1,60>,1>;
using arcsec = unit<DimAngle,std::ratio<1,600>,1>;

using meter2 = unit<DimMeter,std::ratio<1,1>,2>;
using millimeter2 = unit<DimMeter,std::ratio<1,1000>,2>;
using degree2 = unit<DimAngle,std::ratio<1,1>,2>;
using arcmin2 = unit<DimAngle,std::ratio<1,60>,2>;
using arcsec2 = unit<DimAngle,std::ratio<1,600>,2>;

template<typename... rest>
struct contains;

template<typename search, typename compare, typename... rest>
struct contains<search,compare,rest...> {
    using value_type = bool;
    constexpr static bool value = std::is_same<search,compare>::value || contains<search,rest...>::value;
};

template<typename search, typename compare>
struct contains<search,compare> {
    using value_type = bool;
    constexpr static bool value =  std::is_same<search,compare>::value;
};

template<typename... rest>
struct contains_dimension;

template<typename search, typename compare, typename... rest>
struct contains_dimension<search,compare,rest...> {
    using value_type = bool;
    constexpr static bool value = check_dim<search,compare>::value || contains_dimension<search,rest...>::value;
};

template<typename search, typename compare>
struct contains_dimension<search,compare> {
    using value_type = bool;
    constexpr static bool value =  check_dim<search,compare>::value;
};

template<typename... Pack>
struct List {
};

template<template<typename...> class checker, typename List, typename... Pack>
struct loop_dimensions;

template<template<typename...> class checker, typename P1, typename... Pack1, typename... Pack2>
struct loop_dimensions<checker, List<P1,Pack1...>,Pack2...> {
    constexpr static typename checker<P1,Pack2...>::value_type value = checker<P1,Pack2...>::value 
    && loop_dimensions<checker,List<Pack1...>,Pack2...>::value;
};

template<template<typename...> class checker, typename P1, typename... Pack2>
struct loop_dimensions<checker, List<P1>,Pack2...> {
    constexpr static typename checker<P1,Pack2...>::value_type value = checker<P1,Pack2...>::value;
};

template<typename List1, typename List2>
struct same_dimensions;

template<typename... Pack1, typename... Pack2>
struct same_dimensions<List<Pack1...>,List<Pack2...>> {
    constexpr static bool value = loop_dimensions<contains_dimension,List<Pack1...>,Pack2...>::value 
    && loop_dimensions<contains_dimension,List<Pack2...>,Pack1...>::value;
};


template<typename List1, typename List2>
struct same_units;

template<typename... Pack1, typename... Pack2>
struct same_units<List<Pack1...>,List<Pack2...>> {
    constexpr static bool value = loop_dimensions<contains,List<Pack1...>,Pack2...>::value 
    && loop_dimensions<contains,List<Pack2...>,Pack1...>::value;
};

using L1 = List<meter,degree>;
using L2 = List<arcmin,millimeter>;

constexpr bool check_list_same() {
    return same_units<L1,L2>::value;
}

constexpr bool check_list_dimension() {
    return same_dimensions<L1,L2>::value;
}

// get list conversion factor

template<template<typename T> class function,class reduction_operation, typename... Pack>
struct transform_reduce;

template<template<typename T> class function,class reduction_operation,typename Current, typename... Pack>
struct transform_reduce<function,reduction_operation,Current,Pack...> {
    constexpr static typename reduction_operation::value_type value = 
    reduction_operation::call(function<Current>::call(), transform_reduce<function,reduction_operation,Pack...>::value);
};

template<template<typename T> class function,class reduction_operation,typename Current>
struct transform_reduce<function,reduction_operation,Current> {
    constexpr static typename reduction_operation::value_type value = function<Current>::call();
};

// transform_reduce<reducer_outer<R,L1>::template type, multiply_<R>, Pack2... >
// reducer_outer = transform_reduce<conditional_factor<R,U>::template type , multiply_<R>, Pack2...>


template<typename Rep>
struct multiply_ {
    using value_type = Rep;
    constexpr static value_type call(value_type lhs, value_type rhs) noexcept {
        return lhs*rhs;
    }
};

struct and_ {
    using value_type = bool;
    constexpr static value_type call(value_type lhs, value_type rhs) noexcept {
        return lhs && rhs;
    }
};

struct or_ {
    using value_type = bool;
    constexpr static value_type call(value_type lhs, value_type rhs) noexcept {
        return lhs || rhs;
    }
};



// define struct with conditional call -> if dimensions same, return factor, else 1
template<typename Representation, typename Unit, typename Other> 
struct conditional_factor_inner_impl {
    using value_type = Representation;


    constexpr static value_type call() noexcept {
        return call(typename check_dim<Unit,Other>::type{});
    }


    constexpr static value_type call(std::true_type) noexcept {
        return /*std::ratio_less<typename Unit::prefix_type, typename Other::prefix_type>::value ?
         conversion_helper<value_type,Unit,Other>::conversion_factor() :*/
         conversion_helper<value_type,Other,Unit>::conversion_factor();
    }

    constexpr static value_type call(std::false_type) noexcept {
        return 1;
    }

};

template <typename T,typename V>
struct conditional_factor_inner {
    template<typename Other>
    using type = conditional_factor_inner_impl<T,V,Other>;
};

template <typename Rep,typename Unit, typename... Pack>
struct conditional_factor_inner_reduce {
constexpr static Rep value = transform_reduce<conditional_factor_inner<Rep,Unit>::template type , multiply_<Rep>, Pack...>::value;
};


template <typename Rep,typename Unit, typename... Pack>
struct conditional_factor_inner_caller {
    constexpr static Rep call() noexcept {
        return conditional_factor_inner_reduce<Rep,Unit,Pack...>::value;
    }
};

template <typename Rep,typename List>
struct conditional_factor_outer_reduce;

template <typename Rep,typename... Pack>
struct conditional_factor_outer_reduce<Rep,List<Pack...>> {
template <typename Unit>
using type = conditional_factor_inner_caller<Rep,Unit,Pack...>;
};
// transform_reduce<conditinal_outer_reduce<Rep,L1>::template type ,multiply_<Rep>, Pack...>::value;

template<typename Rep,typename L1, typename L2>
struct conversion_factor_unit_pack;


template<typename Rep,typename List1, typename... Pack>
struct conversion_factor_unit_pack<Rep,List1,List<Pack...>> {
constexpr static Rep value = transform_reduce<conditional_factor_outer_reduce<Rep,List1>::template type ,
multiply_<Rep>, Pack...>::value;
};

constexpr double testfactor() {
    return conversion_factor_unit_pack<double,L1,L2>::value;
}

// make list of more accurate type

template<bool b>
struct conditional {
    template<typename Unit, typename Other>
    using type = Unit;
};


template<>
struct conditional<false> {
    template<typename Unit, typename Other>
    using type = Other;
};

template<bool b>
struct select_higher_accuracy {
    template<template<typename...> class fallback,typename Unit, typename Other, typename... Pack>
    using type = typename conditional<std::ratio_less<typename Unit::prefix_type, typename Other::prefix_type>::value>::
    template type<Unit,Other>;
};

template<>
struct select_higher_accuracy<false> {
    template<template<typename...> class fallback,typename Unit, typename Other, typename... Pack>
    using type = typename fallback<Unit,Pack...>::type;
};



template<typename... rest>
struct select_higher_accuracy_from_list;

template<typename search, typename compare, typename... rest>
struct select_higher_accuracy_from_list<search,compare,rest...> {
    // make bool from matching units and accuracy higher, use conditional to select type, reduce list
    using type = 
    typename select_higher_accuracy_from_list<
    typename select_higher_accuracy_from_list<search,compare>::type, rest...>::type;
};

// per_second kilometer per_hour
// cmp per_second, kilometer
// check_dim -> false
// less -> true
// select meter
// next 
// cmp meter, per_hour
// check_dim -> false
// select per_hour // error, should stay search!

template<typename search, typename compare>
struct select_higher_accuracy_from_list<search,compare> {

    using higher_accuracy_type = typename conditional< std::ratio_less<typename search::prefix_type, typename compare::prefix_type>::value >::
    template type<search,compare>;

    using type = typename conditional< 
        check_dim<search,compare>::value >::
    template type<higher_accuracy_type,search>;
};

double getNum() {
    return 0;
}

template<typename other>
using is_meter = check_dim<meter,other>;


template<typename other>
struct check_power_not_zero {
    static constexpr bool value = other::power_value!=0;
};

template<template<typename> class predicate>
struct filter {


    template<typename rv, typename... pack1 >
    struct filter_impl;

    template<typename... pack1,  typename check, typename... pack2>
    struct filter_impl<List<pack1...>,check,pack2...> {
        using type = typename detail::conditional< predicate<check>::value >::template type< 
        typename filter<predicate>::template filter_impl<List<pack1...,check>,pack2...>::type,
        typename filter<predicate>::template filter_impl<List<pack1...>,pack2...>::type>;
    };

    template< typename... pack1, typename last>
    struct filter_impl<List<pack1...>,last> {
        using type = typename detail::conditional< predicate<last>::value >::template type< List<pack1...,last>,List<pack1...> >;
    };

    template< typename... moo>
    using type = typename filter<predicate>::template filter_impl<List<>,moo...>::type;

};


using L3 = List<degree,millimeter,arcsec,arcmin,meter>;


using filter_result = typename filter<check_power_not_zero>::template type<meter,degree,arcmin,arcsec,millimeter>;
static_assert(std::is_same<filter_result,List<meter,degree,arcmin,arcsec,millimeter>>::value, "should be the same");



template<typename operation>
struct combine_unit_power {
    template<typename Unit1, typename Unit2>
    using type = unit<
    typename Unit1::dimension_type, 
    typename detail::conditional< std::ratio_less<typename Unit1::prefix_type, typename Unit2::prefix_type >::value  >::template type< typename Unit1::prefix_type, typename Unit2::prefix_type  > ,
    operation::call(Unit1::power_value,Unit2::power_value)>;
};

struct add_power {
    static constexpr intmax_t call(intmax_t a, intmax_t b) noexcept {
        return a+b;
    }

    template<typename other>
    using type = unit<typename other::dimension_type,typename other::prefix_type,other::power_value>;
};

struct subtract_power {
    static constexpr intmax_t call(intmax_t a, intmax_t b) noexcept {
        return a-b;
    }

    template<typename other>
    using type = unit<typename other::dimension_type,typename other::prefix_type,-other::power_value>;
};

using add_combine_result = typename combine_unit_power<add_power>::template type<meter,millimeter>;
static_assert(std::is_same<add_combine_result, unit<DimMeter,std::ratio<1,1000>,2> >::value, "should be the same");

// Search matching unit from pack and then select correct accuracy
// inputs unit , pack
// loop pack 
// if unit matches
// combine
// else
// recurse
// at end return unit

template<typename operation, typename... units>
struct combine_unit_power_pack;


template<typename operation,typename search,typename current, typename... units>
struct combine_unit_power_pack<operation,search,current,units...> {
    using type = typename detail::conditional< check_dim<search,current>::value >::template type
     < typename combine_unit_power<operation>::template type<search,current> , 
     typename combine_unit_power_pack<operation,search,units...>::type
     >;
};

template<typename operation,typename search, typename last>
struct combine_unit_power_pack<operation,search,last> {
     using type = typename detail::conditional< check_dim<search,last>::value >::template type
     < typename combine_unit_power<operation>::template type<search,last> , search>;
};

using add_combine_result_pack = typename combine_unit_power_pack<add_power,meter,degree,arcmin,arcsec,millimeter>::type;
static_assert(std::is_same<add_combine_result_pack, unit<DimMeter,std::ratio<1,1000>,2> >::value, "should be the same");



// backwards feed
// if there is a matching unit, discard by setting power to 0
// otherwise use unit
struct set_power_to_zero {
    template<typename other>
    using type = unit<typename other::dimension_type,typename other::prefix_type,0>;
};

template<typename operation,typename... units>
struct combine_unit_power_pack_back;


template<typename operation,typename search,typename current, typename... units>
struct combine_unit_power_pack_back<operation,search,current,units...> {
    using type = typename detail::conditional< check_dim<search,current>::value >::template type
     <  typename set_power_to_zero::template type<search> , 
        typename combine_unit_power_pack_back<operation,search,units...>::type
     >;
};

template<typename operation,typename search, typename last>
struct combine_unit_power_pack_back<operation,search,last> {
     using type = typename detail::conditional< check_dim<search,last>::value >::template type
     < typename set_power_to_zero::template type<search> , typename operation::template type<search>>;
};


using add_combine_result_pack_back = typename combine_unit_power_pack_back<add_power,second,meter,per_second>::type;
static_assert(std::is_same<add_combine_result_pack_back, unit<DimTime,std::ratio<1,1>,0> >::value, "should be the same");


// combine two packs

template<typename operation, typename q1, typename q2>
struct combine_two_packs;


template<typename operation, typename... pack1, typename... pack2>
struct combine_two_packs<operation,List<pack1...>,List<pack2...>> {
    using type = typename filter<check_power_not_zero>::template type<
    typename combine_unit_power_pack<operation,pack1,pack2... >::type...,
    typename combine_unit_power_pack_back<operation,pack2,pack1... >::type...>;
};


using Lc1 = List<second>;
using Lc2 = List<meter,per_second>;
using combined_lists = List<meter>;
using combined_units_result = combine_two_packs<add_power,Lc1,Lc2>::type;
using combined_units_result_sub = combine_two_packs<subtract_power,L1,L2>::type;
static_assert(std::is_same<combined_lists, combined_units_result >::value, "should be the same");
static_assert(std::is_same<List<>, combined_units_result_sub >::value, "should be the same");

// get string from pack

template<typename A,typename... T>
std::string to_string(A first, T... args) {
    return first.to_string()+" "+to_string(args...);
}

template<typename A>
std::string to_string(A first) {
    return first.to_string();
}

std::string to_string() {
    return "";
}

}


// ======================================================

template<typename REP, typename... UNITS>
class quantity {
public:
    using value_type = REP;

    template<typename,typename...> friend class quantity;

    template<typename REP2, typename... UNITS2>
    quantity(const quantity<REP2, UNITS2...>& in) : 
    value_{in.count() * detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value} 
    {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
    }

    template<typename REP2, typename... UNITS2>
    quantity(quantity<REP2, UNITS2...>&& in) : 
    value_{std::move(in.value_) * detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value} 
    {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
    }

    template<typename REP2, typename... UNITS2>
    quantity& operator=(const quantity<REP2, UNITS2...>& in) {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
        value_ = in.count() * detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value;
        return *this;
    }

    template<typename REP2, typename... UNITS2>
    quantity& operator=(quantity<REP2, UNITS2...>&& in) {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
        value_ = std::move(in.value_);
        value_ *= detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value;
        return *this;
    }

    template<typename REP2, typename... UNITS2>
    quantity& operator+=(const quantity<REP2, UNITS2...>& in) {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
        value_ += in.count()* detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value;
        return *this;
    }

    template<typename REP2, typename... UNITS2>
    quantity& operator-=(const quantity<REP2, UNITS2...>& in) {
        static_assert(detail::same_dimensions<detail::List<UNITS...>,detail::List<UNITS2...>>::value ,"Cannot convert different dimensions");
        value_ -= in.count()* detail::conversion_factor_unit_pack<REP,detail::List<UNITS...>,detail::List<UNITS2...>>::value;
        return *this;
    }

    explicit constexpr quantity(const REP& in) : value_{in} 
    {}

    constexpr quantity()
    {}

    REP& count() {
        return value_;
    }

    const REP& count() const {
        return value_;
    }

    std::string to_string() const {
        using std::to_string;
        return to_string(value_)+detail::to_string(UNITS{}...);
    }

    template<typename A, typename = typename std::enable_if<std::is_convertible<REP,A>::value>::type>
    explicit operator A() const {
        return value_;
    }

private:
    REP value_{};
};

template<typename REP, typename... UNITS>
std::ostream& operator<<(std::ostream& os, const quantity<REP,UNITS...>& a)
{
    os << a.to_string();
    return os;
}

namespace detail {



template<typename l1,typename l2>
struct combine_unit_lists_add;

template<typename REP,typename... pack1,typename... pack2>
struct combine_unit_lists_add<quantity<REP,pack1...>,quantity<REP,pack2...>> {
    using type = quantity<REP,typename detail::select_higher_accuracy_from_list<pack1,pack2...>::type...>;
};

template<typename Rep,typename l>
struct convert_list_to_quantity;


template<typename Rep,typename... l>
struct convert_list_to_quantity<Rep,detail::List<l...>> {
    using type = quantity<Rep,l...>;
};

}

// Add/subtract two quantities

template<typename REP, typename... UNITS, typename... UNITS2>
auto operator+ (const quantity<REP,UNITS...>& a, const quantity<REP,UNITS2...>& b ) 
-> typename detail::combine_unit_lists_add<quantity<REP,UNITS...>,quantity<REP,UNITS2...>>::type {
    using ret_type = typename detail::combine_unit_lists_add<quantity<REP,UNITS...>,quantity<REP,UNITS2...>>::type;
    ret_type a_conv(a);
    a_conv += b;
    return a_conv;
}

template<typename REP, typename... UNITS, typename... UNITS2>
auto operator- (const quantity<REP,UNITS...>& a, const quantity<REP,UNITS2...>& b ) 
-> typename detail::combine_unit_lists_add<quantity<REP,UNITS...>,quantity<REP,UNITS2...>>::type {
    using ret_type = typename detail::combine_unit_lists_add<quantity<REP,UNITS...>,quantity<REP,UNITS2...>>::type;
    ret_type a_conv(a);
    a_conv -= b;
    return a_conv;
}

// multiply by scalar
template<typename REP1,typename REP2, typename... UNITS>
auto operator* (const REP1& a, const quantity<REP2,UNITS...>& b ) 
-> quantity<typename std::common_type<REP1, REP2>::type,UNITS...> {
    return quantity<typename std::common_type<REP1, REP2>::type,UNITS...>(a*b.count());
}


template<typename REP1,typename REP2, typename... UNITS>
auto operator* (const quantity<REP2,UNITS...>& b, const REP1& a ) 
-> quantity<typename std::common_type<REP1, REP2>::type,UNITS...> {
    return quantity<typename std::common_type<REP1, REP2>::type,UNITS...>(a*b.count());
}

template<typename REP1,typename REP2, typename... UNITS>
auto operator/ (const quantity<REP2,UNITS...>& b, const REP1& a ) 
-> quantity<typename std::common_type<REP1, REP2>::type,UNITS...> {
    return quantity<typename std::common_type<REP1, REP2>::type,UNITS...>(b.count()/a);
}

template<typename REP, typename... UNITS>
auto operator-(const quantity<REP,UNITS...> &a)
-> quantity<REP,UNITS...> {
    return  quantity<REP,UNITS...>{-a.count()};
}

template<typename REP, typename... UNITS>
auto operator+(const quantity<REP,UNITS...> &a)
-> quantity<REP,UNITS...> {
    return a;
}

// multiply two quantities
namespace detail {
template<typename REP1,typename REP2, typename... UNITS1>
struct multiply_result {
    template <typename... UNITS2>
    using type = typename detail::convert_list_to_quantity<typename std::common_type<REP1,REP2>::type,
typename detail::combine_two_packs<detail::add_power,detail::List<UNITS1...>,detail::List<UNITS2...>>::type>::type;
};

template<typename REP1,typename REP2, typename... UNITS1>
struct divide_result {
    template <typename... UNITS2>
    using type = typename detail::convert_list_to_quantity<typename std::common_type<REP1,REP2>::type,
typename detail::combine_two_packs<detail::subtract_power,detail::List<UNITS1...>,detail::List<UNITS2...>>::type>::type;
};

template<typename REP1,typename REP2,typename... UNITS1,typename... UNITS2>
constexpr typename std::common_type<REP1,REP2>::type compute_multiply_factor(const quantity<REP1,UNITS1...>& /*a*/,
 const quantity<REP2,UNITS2...>& /*b*/) 
  {
       return detail::conversion_factor_unit_pack<
       typename std::common_type<REP1,REP2>::type,
       detail::List<typename detail::select_higher_accuracy_from_list<UNITS1,UNITS2...>::type...>,
       detail::List<UNITS1...>>::value * detail::conversion_factor_unit_pack<
       typename std::common_type<REP1,REP2>::type,
       detail::List<typename detail::select_higher_accuracy_from_list<UNITS2,UNITS1...>::type...>,
       detail::List<UNITS2...>>::value;
  }

  template<typename REP1,typename REP2,typename... UNITS1,typename... UNITS2>
constexpr typename std::common_type<REP1,REP2>::type compute_divide_factor(const quantity<REP1,UNITS1...>& /*a*/,
 const quantity<REP2,UNITS2...>& /*b*/) 
  {
       return detail::conversion_factor_unit_pack<
       typename std::common_type<REP1,REP2>::type,
       detail::List<typename detail::select_higher_accuracy_from_list<UNITS1,UNITS2...>::type...>,
       detail::List<UNITS1...>>::value / detail::conversion_factor_unit_pack<
       typename std::common_type<REP1,REP2>::type,
       detail::List<typename detail::select_higher_accuracy_from_list<UNITS2,UNITS1...>::type...>,
       detail::List<UNITS2...>>::value;
  }

}

template<typename REP1,typename REP2, typename... UNITS, typename... UNITS2>
auto operator* (const quantity<REP1,UNITS...>& a, const quantity<REP2,UNITS2...>& b ) 
-> typename detail::multiply_result<REP1,REP2, UNITS... >::template type<UNITS2...> {
    using rv_t = typename detail::multiply_result<REP1,REP2, UNITS... >::template type<UNITS2...>;
    auto factor = detail::compute_multiply_factor(a,b);
    return rv_t{factor*a.count()*b.count()};
}


template<typename REP1,typename REP2, typename... UNITS, typename... UNITS2>
auto operator/(const quantity<REP1,UNITS...>& a, const quantity<REP2,UNITS2...>& b ) 
-> typename detail::divide_result<REP1,REP2, UNITS... >::template type<UNITS2...> {
    using rv_t = typename detail::divide_result<REP1,REP2, UNITS... >::template type<UNITS2...>;
    auto factor = detail::compute_divide_factor(a,b);
    return rv_t{factor*a.count()/b.count()};
}

using unit_kilometer_t = detail::unit<DimMeter,std::ratio<1000,1>,1>;
using unit_meter_t = detail::unit<DimMeter,std::ratio<1,1>,1>;
using unit_degree_t = detail::unit<DimAngle,std::ratio<1,1>,1>;
using unit_square_meter_t = detail::unit<DimMeter,std::ratio<1,1>,2>;
using unit_cubic_meter_t = detail::unit<DimMeter,std::ratio<1,1>,3>;
using unit_perhour_t = detail::unit<DimTime,std::ratio<3600,1>,-1>;
using unit_persecond_t = detail::unit<DimTime,std::ratio<1,1>,-1>;
using unit_second_t = detail::unit<DimTime,std::ratio<1,1>,1>;


template <typename T>
class kilometer : public 
quantity<T, unit_kilometer_t>
{
public:
    using base_type = quantity<T, unit_kilometer_t>;
    using base_type::base_type;
};

template <typename T>
class meter : public 
quantity<T, unit_meter_t>
{
public:
    using base_type = quantity<T, unit_meter_t>;
    using base_type::base_type;
    meter(const base_type& q) : base_type(q) {}
    meter(base_type&& q) : base_type(std::move(q)) {}
};


#define DH_DECLARE_QUANTITY( NAME, ... ) \
template <typename T> \
class NAME : public  \
quantity<T, __VA_ARGS__ > \
{ \
public: \
    using base_type = quantity<T, __VA_ARGS__>; \
    using base_type::base_type; \
    using value_type = T; \
    NAME(const base_type& q) : base_type(q) {} \
    NAME(base_type&& q) : base_type(std::move(q)) {} \
    NAME() = default; \
    NAME(const NAME&) = default; \
    NAME(NAME&&) = default; \
    NAME& operator=(const NAME&) = default; \
    NAME& operator=(NAME&&) = default; \
    ~NAME() = default; \
};

#define DH_DECLARE_QUANTITY_ALL_PREFIXES( NAME, DIMENSION ) \
DH_DECLARE_QUANTITY( atto  ## NAME , (dh::unit<DIMENSION, std::atto, 1 >) ) \
DH_DECLARE_QUANTITY( femto ## NAME , (dh::unit<DIMENSION, std::femto, 1 >) ) \
DH_DECLARE_QUANTITY( pico  ## NAME , (dh::unit<DIMENSION, std::pico, 1 >) ) \
DH_DECLARE_QUANTITY( nano  ## NAME , (dh::unit<DIMENSION, std::nano, 1 >) ) \
DH_DECLARE_QUANTITY( micro ## NAME , (dh::unit<DIMENSION, std::micro, 1 >) ) \
DH_DECLARE_QUANTITY( milli ## NAME , (dh::unit<DIMENSION, std::milli, 1 >) ) \
DH_DECLARE_QUANTITY( centi ## NAME , (dh::unit<DIMENSION, std::centi, 1 >) ) \
DH_DECLARE_QUANTITY( deci  ## NAME , (dh::unit<DIMENSION, std::deci, 1 >) ) \
DH_DECLARE_QUANTITY(          NAME , (dh::unit<DIMENSION, std::ratio<1,1>, 1 >) ) \
DH_DECLARE_QUANTITY( deca  ## NAME , (dh::unit<DIMENSION, std::deca, 1 >) ) \
DH_DECLARE_QUANTITY( hecto ## NAME , (dh::unit<DIMENSION, std::hecto, 1 >) ) \
DH_DECLARE_QUANTITY( kilo  ## NAME , (dh::unit<DIMENSION, std::kilo, 1 >) ) \
DH_DECLARE_QUANTITY( mega  ## NAME , (dh::unit<DIMENSION, std::mega, 1 >) ) \
DH_DECLARE_QUANTITY( giga  ## NAME , (dh::unit<DIMENSION, std::giga, 1 >) ) \
DH_DECLARE_QUANTITY( tera  ## NAME , (dh::unit<DIMENSION, std::tera, 1 >) ) \
DH_DECLARE_QUANTITY( peta  ## NAME , (dh::unit<DIMENSION, std::peta, 1 >) ) \
DH_DECLARE_QUANTITY( exa   ## NAME , (dh::unit<DIMENSION, std::exa, 1 >) )

using ratio_minute = std::ratio<60,1>;
using ratio_hour = std::ratio<3600,1>;
using ratio_day = std::ratio<86400,1>;
using ratio_week = std::ratio<604800,1>;
using ratio_month = std::ratio<2629800,1>;
using ratio_year = std::ratio<31557600,1>; // julian year
using ratio_astronomical_unit = std::ratio<149597870700,1>;
using ratio_lightyear = std::ratio<9460730472580800,1>;
using ratio_speed_of_light = std::ratio<299792458,1>;
using ratio_mile = std::ratio<1609344,1000>;
using ratio_yard = std::ratio<9144,10000>;
using ratio_foot = std::ratio<3048,10000>;
using ratio_inch = std::ratio<254,10000>;

template <typename T>
class degree : public 
quantity<T, unit_degree_t>
{
public:
    using base_type = quantity<T, unit_degree_t>;
    using base_type::base_type;
};

template <typename T>
class square_meter : public 
quantity<T, unit_square_meter_t>
{
public:
    using base_type = quantity<T, unit_square_meter_t>;
    using base_type::base_type;

    square_meter(const base_type& q) : base_type(q) {}
    square_meter(base_type&& q) : base_type(std::move(q)) {}
};


template <typename T>
class second : public 
quantity<T, unit_second_t>
{
public:
    using base_type = quantity<T, unit_second_t>;
    using base_type::base_type;

    second(const base_type& q) : base_type(q) {}
    second(base_type&& q) : base_type(std::move(q)) {}
};


template <typename T>
class cubic_meter : public 
quantity<T, unit_cubic_meter_t>
{
public:
    using base_type = quantity<T, unit_cubic_meter_t>;
    using base_type::base_type;
    cubic_meter(const base_type& q) : base_type(q) {}
    cubic_meter(base_type&& q) : base_type(std::move(q)) {}
};


template <typename T>
class kilometer_per_hour : public 
quantity<T, unit_kilometer_t, unit_perhour_t>
{
public:
    using base_type = quantity<T, unit_kilometer_t, unit_perhour_t>;
    using base_type::base_type;
    kilometer_per_hour(const base_type& in) : base_type(in) {}
    kilometer_per_hour(base_type&& in) : base_type(std::move(in)) {}
};

template <typename T>
class meter_per_second : public 
quantity<T, unit_meter_t, unit_persecond_t>
{
public:
    using base_type = quantity<T, unit_meter_t, unit_persecond_t>;
    using base_type::base_type;
    meter_per_second(const base_type& in) : base_type(in) {}
    meter_per_second(base_type&& in) : base_type(std::move(in)) {}
};

int main() {
    constexpr auto v = detail::get_factor();
    std::cout<<"F "<<v<<"\n";


    std::cout<<"D1 "<<detail::check_dim<detail::meter,detail::millimeter>::value <<"\n";
    std::cout<<"D0 "<<detail::check_dim<detail::meter,detail::degree>::value <<"\n";
    std::cout<<"L "<<detail::check_list_same() <<"\n";
    std::cout<<"L2 "<<detail::check_list_dimension() <<"\n";
    std::cout<<"L3 "<<detail::testfactor() <<"\n";
    std::cout<<"getNum() "<<detail::getNum() <<"\n";
    std::cout<<sizeof(intmax_t)<<"\n";

    kilometer<double> km(100.0);
    meter<double> m(km);

    std::cout<<km.count()<<"km is "<<m.count()<<"m\n";

    kilometer_per_hour<double> kmph(100.0);
    meter_per_second<double> mps(kmph);

    std::cout<<kmph.count()<<"km/h is "<<mps.count()<<"m/s\n";


    meter_per_second<double> mps2(100.0);
    kilometer_per_hour<double> kmph2(mps2);

    std::cout<<kmph2.count()<<"km/h is "<<mps2.count()<<"m/s\n";

    kilometer<double> rv=m-km;
    std::cout<<m.count()<<"m - "<<km.count()<<"km = "<< rv.count() <<"km\n";


    meter_per_second<double> rv2 = mps2+kmph;
    std::cout<<mps2.count()<<"m/s + "<<kmph.count()<<"km/h = "<< rv2.count() <<"m/s\n";
    std::cout<<detail::to_string(unit_perhour_t{})<<"\n";

    auto m5 = 5*m;
    auto m6 = m*4.5;
    auto m7 = -m/2.0;
    std::cout<<m5.count()<<"m\n"<<m6.count()<<"m\n"<<m7.count()<<"m\n";
{
    meter<double> m(2);
    meter<double> m2(3);
    square_meter<double> squared(m*m2);
    cubic_meter<double> cubeb(m*squared);
    std::cout<<"MULT "<<squared.to_string()<<"==6\n";
    std::cout<<"MULT "<<cubeb.to_string()<<"==12\n";
}

{
    meter_per_second<double> mps(100);
    second<double> ts(0.5);
    meter<double> m2(ts*mps);
    std::cout<<"MULT "<<m2.to_string()<<"==50\n";
}

{
    meter<double> m(100);
    second<double> t(0.5);
    auto mps = m/t;
    meter_per_second<double> mps2(m/t);
    std::cout<<"Div "<<mps<<"==200\n";
    std::cout<<"fixed type "<<mps2<<"==200\n";
}

{
    meter<double> m(10);
    kilometer<double> km(2);
     std::cout<<km*m<<" == 20000.000000m^2\n";
     std::cout<<m*km<<" == 20000.000000m^2\n";
     std::cout<<km/m<<" == 200.000000\n";
     std::cout<<static_cast<float>(m/km)<<" == 0.005000\n";
}

    return 0;
}

// TODO 
// Add unit conversion for multiply and divide!
// add print function
// add si units