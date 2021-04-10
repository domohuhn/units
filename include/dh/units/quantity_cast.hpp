/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_CAST_INCLUDED
#define DH_UNITS_QUANTITY_CAST_INCLUDED

#include "dh/units/si_units.hpp"
#include "dh/units/imperial_units.hpp"
#include "dh/units/math.hpp"


namespace dh {
namespace units {


template<typename T,typename A, typename = typename std::enable_if<is_dh_quantity<A>::value && std::is_arithmetic<T>::value >::type>
T quantity_cast (const A& a) {
    return static_cast<T>(a);
}

template<typename T,typename A, 
typename std::enable_if<is_dh_quantity<A>::value && is_dh_quantity<T>::value &&
    lists_contain_same_dimensions<typename A::unit_list, typename T::unit_list>::value,bool>::type = true >
T quantity_cast (const A& a) {
    return T(static_cast<typename T::value_type>(a.count() * unit_list_conversion_factor<math_return_t<T>,typename T::unit_list, typename A::unit_list>::value));
}

template<typename T>
constexpr T constants_zero_kelvin() {
    return static_cast<T>(273.15L);
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<T,si::unit_kelvin>::value ,int>::type = 0 >
T quantity_cast (const ::si::celsius<A>& a) {
    return si::kelvin<typename T::value_type>{a.count() + constants_zero_kelvin<typename T::value_type>()};
}

template<typename T,typename A,
    typename std::enable_if< is_dh_quantity<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<A,si::unit_kelvin>::value 
        && quantity_convertible_to_unit<T,si::unit_celsius>::value 
        ,int>::type = 0 >
T quantity_cast (const A& a) {
    return si::celsius<typename T::value_type>{si::kelvin<typename T::value_type>(a).count() - constants_zero_kelvin<typename T::value_type>()};
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,imperial::unit_fahrentheit>::value
        ,int>::type = 0 >
T quantity_cast (const ::si::celsius<A>& a) {
    return ::imperial::fahrenheit<typename T::value_type>{ a.count()*1.8 + 32};
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,si::unit_celsius>::value
        ,int>::type = 0 >
T quantity_cast (const ::imperial::fahrenheit<A>& a) {
    return ::si::celsius<typename T::value_type>{ (a.count() - 32)*5.0/9.0 };
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,si::unit_kelvin>::value
        ,int>::type = 0 >
T quantity_cast (const ::imperial::fahrenheit<A>& a) {
    return ::si::kelvin<typename T::value_type>{ (a.count() - 32)*5.0/9.0 + constants_zero_kelvin<typename T::value_type>() };
}

template<typename T,typename A,
    typename std::enable_if< is_dh_quantity<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<A,si::unit_kelvin>::value 
        && quantity_convertible_to_unit<T,imperial::unit_fahrentheit>::value 
        ,int>::type = 0 >
T quantity_cast (const A& a) {
    return ::imperial::fahrenheit<typename T::value_type>{
        (si::kelvin<typename T::value_type>(a).count() - constants_zero_kelvin<typename T::value_type>())*1.8 + 32};
}


}
}

namespace si {
using dh::units::quantity_cast;
}

namespace imperial {
using dh::units::quantity_cast;
}

#endif /* DH_UNITS_QUANTITY_CAST_INCLUDED */
