/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_ACCUMULATE_DETAIL_INCLUDED
#define DH_MPL_ACCUMULATE_DETAIL_INCLUDED

#include "dh/mpl/void_t.hpp"
#include <type_traits>
#include <cstdint>
#include <cstddef>

namespace dh {
namespace mpl {

namespace detail {

constexpr size_t selectTypeAccumulation(size_t value) {
    return  value>8?3 :value>2?2 : value==2 ? 1 : 0;
}

template <class binary_operation, size_t b>
struct accumulate_type {
    template<typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8, typename... rest>
    using type = typename accumulate_type<binary_operation,selectTypeAccumulation( sizeof...(rest)+1)>:: template type
        <typename binary_operation::template type<
            typename binary_operation::template type<
                typename binary_operation::template type<
                    typename binary_operation::template type<
                        typename binary_operation::template type<
                            typename binary_operation::template type<
                                typename binary_operation::template type<t1,t2>,
                            t3>,
                        t4>,
                    t5>,
                t6>,
            t7>,
        t8>,
    rest...>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,2> {
    template<typename current,typename next, typename... rest>
    using type = typename accumulate_type<binary_operation,selectTypeAccumulation( sizeof...(rest)+1)>:: template type
        <typename binary_operation::template type<current,next>, rest...>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,1> {
    template<typename current,typename last>
    using type = typename binary_operation::template type<current,last>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,0> {
    template<typename current>
    using type = current;
};

// value recursion

template<typename binary_operation, typename ... pack>
struct accumulate_value;

template<typename binary_operation, typename current>
struct accumulate_value<binary_operation,current> {
    constexpr static typename binary_operation::value_type value = current::value;
};

template<typename binary_operation, typename current, typename next>
struct accumulate_value<binary_operation,current,next> {
    constexpr static typename binary_operation::value_type 
    value = binary_operation::call(current::value, next::value);
};

template<typename binary_operation, typename current1, typename current2, typename current3>
struct accumulate_value<binary_operation,current1,current2,current3> {
    constexpr static typename binary_operation::value_type 
    value = binary_operation::call(current1::value, binary_operation::call(current2::value, current3::value ));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4>
struct accumulate_value<binary_operation,current1,current2,current3,current4> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,current4::value)));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4, typename... rest>
struct accumulate_value<binary_operation,current1,current2,current3,current4,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,current1,current2,current3,current4>::value , accumulate_value<binary_operation,rest...>::value );
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8>
struct accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,
                binary_operation::call(current4::value,
                    binary_operation::call(current5::value, 
                        binary_operation::call(current6::value, 
                            binary_operation::call(current7::value,current8::value)))))));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, typename... rest>
struct accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8>::value , accumulate_value<binary_operation,rest...>::value );
};

template<typename binary_operation, 
 typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, 
 typename current9, typename current10, typename current11, typename current12,
 typename current13, typename current14, typename current15, typename current16>
struct accumulate_value<binary_operation,
  current1,current2,current3,current4,current5,current6,current7,current8,
  current9,current10,current11,current12,current13,current14,current15,current16> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,
                binary_operation::call(current4::value,
                    binary_operation::call(current5::value, 
                        binary_operation::call(current6::value, 
                            binary_operation::call(current7::value,
                                binary_operation::call(current8::value, 
                                    binary_operation::call(current9::value, 
                                        binary_operation::call(current10::value,
                                            binary_operation::call(current11::value,
                                                binary_operation::call(current12::value, 
                                                    binary_operation::call(current13::value, 
                                                        binary_operation::call(current14::value,
                                                            binary_operation::call(current15::value,current16::value)))))))))))))));
};

template<typename binary_operation, 
 typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, 
 typename current9, typename current10, typename current11, typename current12,
 typename current13, typename current14, typename current15, typename current16, typename... rest>
struct accumulate_value<binary_operation,
  current1,current2,current3,current4,current5,current6,current7,current8,
  current9,current10,current11,current12,current13,current14,current15,current16,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,
            current1,current2,current3,current4,current5,current6,current7,current8,
            current9,current10,current11,current12,current13,current14,current15,current16>::value ,
        accumulate_value<binary_operation,rest...>::value );
};

struct no_accumulate_implementation {};

template <typename T, typename = void>
struct can_accumulate_value : std::false_type {};
template <typename T>
struct can_accumulate_value<T, 
    ::dh::mpl::void_t<typename T::value_type,
        decltype(T::call( std::declval<typename T::value_type>(), std::declval<typename T::value_type>() ))>>
    : std::true_type {};


}

}
}

#endif /* DH_MPL_ACCUMULATE_DETAIL_INCLUDED */
