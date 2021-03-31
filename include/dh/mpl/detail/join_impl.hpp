/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_JOIN_INL_INCLUDED
#define DH_MPL_JOIN_INL_INCLUDED

#include "dh/mpl/list.hpp"

namespace dh {
namespace mpl {

namespace detail {
// private implementation of join - required for recursion
template<typename ...>
struct join;

template<>
struct join<> {
    using type = list<>;
};

template<typename in>
struct join<in> {
    using type = in;
};

template<typename... pack1, typename... pack2>
struct join<list<pack1...>,list<pack2...>> {
    using type = list<pack1...,pack2...>;
};

template<typename... pack1, typename... pack2, typename... pack3>
struct join<list<pack1...>,list<pack2...>,list<pack3...>> {
    using type = list<pack1...,pack2...,pack3...>;
};

template<typename... pack1, typename... pack2, typename... pack3, typename... pack4>
struct join<list<pack1...>,list<pack2...>,list<pack3...>,list<pack4...>> {
    using type = list<pack1...,pack2...,pack3...,pack4...>;
};

template<typename... pack1, typename... pack2, typename... pack3, typename... pack4, typename... rest>
struct join<list<pack1...>,list<pack2...>,list<pack3...>,list<pack4...>,rest...> {
    using type = typename join<list<pack1...,pack2...,pack3...,pack4...>, typename join<rest...>::type >::type;
};

template<typename... pack1, typename... pack2, typename... pack3, typename... pack4,
typename... pack5, typename... pack6, typename... pack7, typename... pack8, typename... rest>
struct join<list<pack1...>,list<pack2...>,list<pack3...>,list<pack4...>,
list<pack5...>,list<pack6...>,list<pack7...>,list<pack8...>,rest...> {
    using type = typename join< list<pack1...,pack2...,pack3...,pack4...,pack5...,pack6...,pack7...,pack8...>, typename join<rest...>::type >::type;
};

template<typename... pack1, typename... pack2, typename... pack3, typename... pack4,
typename... pack5, typename... pack6, typename... pack7, typename... pack8,
typename... pack9, typename... pack10, typename... pack11, typename... pack12,
typename... pack13, typename... pack14, typename... pack15, typename... pack16,
typename... rest>
struct join<list<pack1...>,list<pack2...>,list<pack3...>,list<pack4...>,
list<pack5...>,list<pack6...>,list<pack7...>,list<pack8...>,
list<pack9...>,list<pack10...>,list<pack11...>,list<pack12...>,
list<pack13...>,list<pack14...>,list<pack15...>,list<pack16...>,rest...> {
    using type = typename join< list<pack1...,pack2...,pack3...,pack4...,pack5...,pack6...,pack7...,pack8...,
        pack9...,pack10...,pack11...,pack12...,pack13...,pack14...,pack15...,pack16...>, typename join<rest...>::type >::type;
};


} /* namespace detail */

} /* namespace mpl */
} /* namespace dh */

#endif /* DH_MPL_JOIN_INL_INCLUDED */



