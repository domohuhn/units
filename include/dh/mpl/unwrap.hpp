/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_UNWRAP_INCLUDED
#define DH_MPL_UNWRAP_INCLUDED

namespace dh {
namespace mpl {

/** Unwrap a template pack and put it in a continuation. Can only be nested once! */
template<typename T>
struct unwrap;

template<template<typename...> class container, typename... pack>
struct unwrap<container<pack...>> {
    template<typename next>
    using then = typename next::template type<pack...>;
};

}
}

#endif /* DH_MPL_UNWRAP_INCLUDED */

