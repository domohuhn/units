
/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_TRAITS_INCLUDED
#define DH_UNITS_TRAITS_INCLUDED

#include <cstdint>
#include <type_traits>
#include "dh/mpl/core.hpp"
#include "dh/units/dimensions.hpp"

namespace dh {
namespace units {

namespace mpl = ::dh::mpl;

template<typename U1, typename U2>
struct units_have_same_dimension_and_power {
    using type =  typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;
    constexpr static bool value = type::value && U1::power_value == U2::power_value;
};


template<typename U1, typename U2>
using units_have_same_dimension =  typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;

template<typename L1, typename L2>
struct lists_contain_same_dimensions;

template<typename... pack1, typename... pack2>
struct lists_contain_same_dimensions<mpl::list<pack1...>, mpl::list<pack2...>> 
{
    static constexpr bool checkPackSizes() {
        return sizeof...(pack1) == sizeof...(pack2) && sizeof...(pack1)>0;
    }

    using combined_list = typename mpl::conditional<checkPackSizes()>::template type<
        mpl::invoke_t<mpl::list< typename mpl::find_if< mpl::bind<mpl::wrap<units_have_same_dimension_and_power> ,pack1> >:: template type<pack2...>... > ,
                        mpl::join>, mpl::list<>>;
    static constexpr bool value = sizeof...(pack1) == sizeof...(pack2) && combined_list::size == sizeof...(pack1);
};

template<typename... pack1>
struct lists_contain_same_dimensions<mpl::list<pack1...>, mpl::list<>> 
{
    static constexpr bool value = false;
};

template<typename... pack1>
struct lists_contain_same_dimensions<mpl::list<>, mpl::list<pack1...>> 
{
    static constexpr bool value = false;
};

template<>
struct lists_contain_same_dimensions<mpl::list<>, mpl::list<>> 
{
    static constexpr bool value = true;
};


template<typename L1, typename L2>
struct lists_contain_same_types;

template<typename... pack1, typename... pack2>
struct lists_contain_same_types<dh::mpl::list<pack1...>, dh::mpl::list<pack2...>> 
{
    using combined_list = mpl::invoke_t<
        mpl::list< typename mpl::find_if< mpl::bind<mpl::wrap<std::is_same> ,pack1> >:: template type<pack2...>... > ,
        mpl::join>;

    static constexpr bool value = sizeof...(pack1) == sizeof...(pack2) && combined_list::size == sizeof...(pack1);
};

template <typename T, typename = void>
struct is_dh_quantity : std::false_type {};
template <typename T>
struct is_dh_quantity<T, dh::mpl::void_t<typename T::value_type,
    typename T::quantity_type, typename T::unit_list, decltype(std::declval<T>().count()) >>
    : std::true_type {};


}
}

#endif /* DH_UNITS_TRAITS_INCLUDED */
