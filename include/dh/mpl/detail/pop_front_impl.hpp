/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_POP_FRONT_INCLUDED
#define DH_MPL_DETAIL_POP_FRONT_INCLUDED

#include "dh/mpl/comparisons.hpp"

namespace dh {
namespace mpl {
namespace detail {

template<bool b>
struct pop_front_impl {
    template<template <typename...> class container, typename first ,typename... pack>
    using type = container<pack...>;
};


template<>
struct pop_front_impl<false> {
    template<template <typename...> class container>
    using type = container<>;
};

}
}
}

#endif /* DH_MPL_DETAIL_POP_FRONT_INCLUDED */
