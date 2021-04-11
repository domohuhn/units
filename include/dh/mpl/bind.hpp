/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_BIND_INCLUDED
#define DH_MPL_BIND_INCLUDED

namespace dh {
namespace mpl {

/** @brief Bind the args as the first arguments of functors type. */
template<class functor, typename... args>
struct bind {
    template<typename... pack>
    using type = typename functor::template type<args...,pack...>;
};

}
}

#endif /* DH_MPL_BIND_INCLUDED */

