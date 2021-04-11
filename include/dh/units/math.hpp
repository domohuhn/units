/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_UNITS_MATH_INCLUDED
#define DH_UNITS_MATH_INCLUDED

#include "dh/units/si_units.hpp"


namespace dh {
namespace units {

template<typename T>
using math_return_t = typename dh::mpl::conditional<
    std::is_floating_point<typename std::decay<T>::type::value_type>::value>::template type<
        typename std::decay<T>::type::value_type ,
        double >;


template<typename T>
using can_be_converted_to_radian_t = typename std::enable_if< 
        dh::units::is_dh_quantity<typename std::decay<T>::type >::value &&
        std::is_convertible<typename std::decay<T>::type,si::radian<math_return_t<T>>>::value >::type;

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> sin(T&& x) {
    return std::sin(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> cos(T&& x) {
    return std::cos(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> tan(T&& x) {
    return std::tan(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> asin(T x) {
    return std::asin(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> acos(T x) {
    return std::acos(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> atan(T x) {
    return std::atan(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> atan2(T y ,T x) {
    return std::atan2(y,x);
}


// abs, min, max, clamp

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T abs (const T& a) {
    using std::abs;
    return T(abs(a.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T min (const T& a, const T& b) {
    using std::min;
    return T(min(a.count(),b.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T max (const T& a, const T& b) {
    using std::max;
    return T(max(a.count(),b.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T clamp (const T& value, const T& minv,const T& maxv) {
    return max(minv ,min(maxv,value));
}


template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value && T::unit_list::empty >::type>
math_return_t<T> exp (const T& value) {
    return std::exp(math_return_t<T>(value.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value && T::unit_list::empty >::type>
math_return_t<T> log (const T& value) {
    return std::log(math_return_t<T>(value.count()));
}

}
}

#endif /* DH_UNITS_MATH_INCLUDED */
