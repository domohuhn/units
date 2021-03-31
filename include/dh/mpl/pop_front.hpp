/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_POP_FRONT_INCLUDED
#define DH_MPL_POP_FRONT_INCLUDED

#include "dh/mpl/list.hpp"
#include "dh/mpl/comparisons.hpp"
#include "dh/mpl/detail/pop_front_impl.hpp"

namespace dh {
namespace mpl {

/** @brief Remove first element of list, then wrap into container.
 */
template<template <typename...> class container = dh::mpl::list >
struct pop_front {

    template<typename... pack>
    using type = typename detail::pop_front_impl< is_greater(sizeof...(pack),0) >::template type<container,pack...>;
};


}
}

#endif /* DH_MPL_POP_FRONT_INCLUDED */
