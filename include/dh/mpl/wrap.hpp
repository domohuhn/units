/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_WRAP_INCLUDED
#define DH_MPL_WRAP_INCLUDED

namespace dh {
namespace mpl {

/** @brief Wrapper for other templates. Can be used to wrap a template for usage with e.g. min element or to extract the list at the end.
 * 
 * @note is this is added with any other type than mpl::list, then the mpl sequence terminates.
 */
template<template<typename...> class container>
struct wrap {
    template<typename... pack>
    using type = container<pack...>;
};

}
}

#endif /* DH_MPL_WRAP_INCLUDED */

