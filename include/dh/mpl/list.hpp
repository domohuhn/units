/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_LIST_INCLUDED
#define DH_MPL_LIST_INCLUDED

#include <cstdint>
#include <type_traits>

namespace dh {
namespace mpl {
    
/** The list type used to transport the variadic template packs from one funciton to the next */
template<typename... pack>
struct list {
    template<typename next>
    using then = typename next::template type<pack...>;

    template<template<typename...> class wrapper, typename... firstargs>
    using wrap = wrapper<firstargs...,pack...>;
    
    static constexpr size_t size = sizeof...(pack);
    static constexpr bool empty = size==0;

    template<class next, typename... firstargs>
    using type = typename next::template type<firstargs...,pack...>;
};

template<typename functor,typename... pack>
auto call( mpl::list<pack...> ) -> typename std::decay<decltype(functor::call(pack::value...))>::type {
    return functor::call(pack::value...);
}

template<typename... pack>
constexpr size_t list<pack...>::size;

template<typename... pack>
constexpr bool list<pack...>::empty;

using empty_list = list<>;

}
}

#endif /* DH_MPL_LIST_INCLUDED */

