/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_JOIN_INL_INCLUDED
#define DH_MPL_JOIN_INL_INCLUDED

#include "dh/mpl/list.hpp"
#include "dh/mpl/wrap.hpp"

namespace dh {
namespace mpl {

namespace detail {

template<bool b>
struct join {
    template<typename list, typename... args>
    using type = typename list::template type<args...,wrap<mpl::list>>;
};

template<>
struct join<false> {
    template<typename... pack>
    using type = list<>;
};

} /* namespace detail */

} /* namespace mpl */
} /* namespace dh */

#endif /* DH_MPL_JOIN_INL_INCLUDED */



