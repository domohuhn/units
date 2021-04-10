/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_CONVERSION_INCLUDED
#define DH_UNITS_QUANTITY_CONVERSION_INCLUDED

#include "dh/mpl/core.hpp"
#include "dh/units/unit.hpp"
#include "dh/units/traits.hpp"
#include <ratio>

namespace dh {
namespace units {

namespace mpl = ::dh::mpl;

template<typename REP, typename RATIO_TO, typename RATIO_FROM>
constexpr REP ratio_conversion_factor() noexcept {
    return ((REP)(RATIO_FROM::num)*(REP)(RATIO_TO::den))/((REP)(RATIO_TO::num)*(REP)(RATIO_FROM::den));
}

template<typename REP, intmax_t POWER , typename RATIO_TO, typename RATIO_FROM>
struct conversion_factor_holder_type {

    static constexpr REP conversion_factor_power(intmax_t index) {
        return index>0 ? ratio_conversion_factor<REP,RATIO_TO,RATIO_FROM>()*conversion_factor_power(index-1) : 
        (index<0? ratio_conversion_factor<REP,RATIO_FROM,RATIO_TO>()*conversion_factor_power(index+1) : 1);
    };

    static constexpr REP value = conversion_factor_power(POWER);
};

template<typename REP, typename UNIT_TO>
struct compute_conversion_factor {
    template<typename UNIT_FROM>
    using type = typename mpl::conditional< units_have_same_dimension_and_power<UNIT_TO,UNIT_FROM>::value >::template type<
        conversion_factor_holder_type<REP, UNIT_TO::power_value ,typename UNIT_TO::prefix_type ,typename UNIT_FROM::prefix_type>,
        conversion_factor_holder_type<REP,0,std::ratio<1,1>,std::ratio<1,1> > >;
};

template<typename REP, typename LIST_TO,  typename LIST_FROM>
struct unit_list_conversion_factor;

template<typename REP, typename... pack, typename LIST_FROM>
struct unit_list_conversion_factor<REP,mpl::list<pack...>, LIST_FROM > {
    using factor_list = mpl::list< typename LIST_FROM::template then< mpl::transform< compute_conversion_factor<REP,pack> > >::template then< mpl::accumulate_value<mpl::multiply<REP>> >... >;

    static constexpr bool needsComputation() noexcept {
        return !LIST_FROM::empty && sizeof...(pack)>0 && !std::is_same< mpl::list<pack...>, LIST_FROM>::value;
    }

    static constexpr REP value = mpl::conditional<needsComputation()>::template type<
     mpl::invoke_t<factor_list , mpl::accumulate_value<mpl::multiply<REP>> >,
     unit_list_conversion_factor<REP, mpl::empty_list,  mpl::empty_list> >::value;
};

template<typename REP>
struct unit_list_conversion_factor<REP, mpl::empty_list,  mpl::empty_list > {
    static constexpr REP value = static_cast<REP>(1);
};

template<typename REP, typename... pack, typename LIST_FROM> 
constexpr REP unit_list_conversion_factor<REP,mpl::list<pack...>,LIST_FROM>::value;

template<typename REP> 
constexpr REP unit_list_conversion_factor<REP,mpl::empty_list, mpl::empty_list>::value;


struct unit_has_higher_accuracy {
    template<typename current,typename other>
    using use_more_accurate_prefix_t = typename mpl::conditional<std::ratio_less<typename current::prefix_type, typename other::prefix_type>::value>::template type<
        current,dh::units::unit<typename current::dimension_type ,typename other::prefix_type ,current::power_value>
        >;

    template<typename minimum, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<minimum,compare>::value >::template type<
        use_more_accurate_prefix_t<minimum,compare>,
        minimum>;
};

struct select_highest_accuracy_for_first_dimension_in_list {
    template<typename... pack>
    using type = mpl::invoke_t<mpl::list<pack...>, mpl::accumulate<unit_has_higher_accuracy>>;
};

template<typename l1,typename l2>
struct combine_unit_lists_selecting_higher_accuracy;

template<typename... pack1,typename... pack2>
struct combine_unit_lists_selecting_higher_accuracy<mpl::list<pack1...>,mpl::list<pack2...>> {
    
    using unit_list = mpl::list< typename select_highest_accuracy_for_first_dimension_in_list::template type<pack1,pack2...>... >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;
};


template <typename UnitTo,typename UnitFrom, typename = void>
struct quantity_conversion_is_lossless : std::false_type {};

template <typename UnitTo,typename UnitFrom>
struct quantity_conversion_is_lossless<UnitTo,UnitFrom, typename std::enable_if< is_dh_quantity<UnitTo>::value && is_dh_quantity<UnitFrom>::value >::type >
{
    constexpr static bool value = 
    unit_list_conversion_factor<typename UnitTo::value_type,typename UnitTo::unit_list, typename UnitFrom::unit_list>::value >= 1 ||
    std::is_floating_point<typename std::decay<UnitTo>::type::value_type>::value;
};


// ===========================================================================================================================

template<typename operation>
struct combine_unit_power {
    template<typename Unit1, typename Unit2>
    using type = unit<typename Unit1::dimension_type, 
        typename mpl::conditional< std::ratio_less<typename Unit1::prefix_type, typename Unit2::prefix_type >::value  >::
            template type< typename Unit1::prefix_type, typename Unit2::prefix_type  > ,
        operation::call(Unit1::power_value,Unit2::power_value)>;
};

template<typename operation>
struct unit_accumulator {
    template< typename combined, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<combined,compare>::value >::
        template type < typename combine_unit_power<operation>::template type<combined,compare> , combined >;
};

struct unit_accumulator_backpropagate {

    template<typename other>
    using set_power_to_zero = unit<typename other::dimension_type,std::ratio<1,1>,0>;

    template< typename combined, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<combined,compare>::value >::
        template type < set_power_to_zero<combined> , combined >;
};

struct unit_power_not_zero {
    template< typename unit >
    using type =  typename mpl::conditional< unit::power_value!=0 >:: template type< std::true_type , std::false_type >;
};

template<typename l1,typename l2>
struct multiplication_result;

template<typename... pack1,typename... pack2>
struct multiplication_result <mpl::list<pack1...>,mpl::list<pack2...>> {

    using unfiltered_list = mpl::list<typename mpl::accumulate<unit_accumulator<mpl::add<intmax_t>>>::template type<pack1,pack2...>...,
        typename mpl::accumulate<unit_accumulator_backpropagate>::template type<pack2,pack1...>...>;

    using unit_list = mpl::invoke_t<unfiltered_list, mpl::filter<unit_power_not_zero> >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;

};

template<typename l1,typename l2>
struct division_result;

template<typename... pack1,typename... pack2>
struct division_result <mpl::list<pack1...>,mpl::list<pack2...>> {

    template<typename other>
    using invert_power = unit<typename other::dimension_type,typename other::prefix_type, -other::power_value >;

    using unfiltered_list = mpl::list<typename mpl::accumulate<unit_accumulator<mpl::subtract<intmax_t>>>::template type<pack1,pack2...>...,
        invert_power<typename mpl::accumulate<unit_accumulator_backpropagate>::template type<pack2,pack1...>>...>;

    using unit_list = mpl::invoke_t<unfiltered_list, mpl::filter<unit_power_not_zero> >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;

};


template<typename RV,typename... UNITS1,typename... UNITS2>
constexpr RV compute_multiply_conversion_factor(const mpl::list<UNITS1...>& /*a*/,const mpl::list<UNITS2...>& /*b*/) 
{
    return unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS1,UNITS2...>...>,
        mpl::list<UNITS1...>>::value *
    unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS2,UNITS1...>...>,
        mpl::list<UNITS2...>>::value;
}

template<typename RV,typename... UNITS1,typename... UNITS2>
constexpr RV compute_division_conversion_factor(const mpl::list<UNITS1...>& /*a*/,const mpl::list<UNITS2...>& /*b*/) 
{
    return unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS1,UNITS2...>...>,
        mpl::list<UNITS1...>>::value /
    unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS2,UNITS1...>...>,
        mpl::list<UNITS2...>>::value;
}


template<typename Scalar, typename Quantity>
using common_value_type_t = typename std::common_type<Scalar, typename Quantity::value_type>::type;

template<typename LHS, typename RHS>
using common_quantity_representation_t =  typename std::common_type<typename LHS::value_type, typename RHS::value_type>::type;

template<typename LHS, typename RHS>
using can_be_added_t = typename std::enable_if< 
            is_dh_quantity<LHS>::value &&
            is_dh_quantity<RHS>::value &&
            lists_contain_same_dimensions<typename LHS::unit_list, typename RHS::unit_list>::value 
        >::type;

template <typename unit>
using contained_unit_list_t = typename is_derived_unit<unit>::unit_list;

template<typename l1,typename l2>
struct multiplication_result_assert_same_prefixes;

template<typename... pack1,typename... pack2>
struct multiplication_result_assert_same_prefixes <mpl::list<pack1...>,mpl::list<pack2...>> {
    using check = mpl::invoke_t< 
        mpl::list< mpl::invoke_t<mpl::list<pack2...>,
            mpl::find_if<mpl::bind< mpl::wrap<units_have_same_dimension_and_different_prefixes>,pack1>> >... 
        >,
        mpl::join>;
    static_assert( check::empty , "A list of units for a quantity cannot have the same unit with different prefixes! Check derived units!");
    using type = typename multiplication_result<mpl::list<pack1...>,mpl::list<pack2...>>::unit_list;
};


struct unit_extraction_accumulator {
    template< typename accumulated, typename current>
    using type = typename multiplication_result_assert_same_prefixes<accumulated,current>::type;
};

template<bool b>
struct extract_base_units_impl {
    template <typename... pack>
    using type = mpl::invoke_t<mpl::list< contained_unit_list_t<pack>...  >,mpl::accumulate<unit_extraction_accumulator>>;
};

template<>
struct extract_base_units_impl<false> {
    template <typename... pack>
    using type = mpl::list<>;
};

template <typename... pack>
using extract_base_units_t = typename extract_base_units_impl<mpl::is_greater(sizeof...(pack),0)>::template type<pack...>;

}
}

#endif /* DH_UNITS_QUANTITY_CONVERSION_INCLUDED */
