/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_TRANSFORM_INCLUDED
#define DH_MPL_TRANSFORM_INCLUDED

#include "dh/mpl/list.hpp"

namespace dh {
namespace mpl {

/** @brief Apply the contained type template from the functor to the template pack of the list. */
template<typename functor>  
struct transform {

    template<typename... pack>
    using type = dh::mpl::list< typename functor::template type<pack>... >;
    
    template<template<typename...> class wrapper, typename... pack>
    using wrap = wrapper< typename functor::template type<pack>... >;

};

}
}

#endif /* DH_MPL_TRANSFORM_INCLUDED */

