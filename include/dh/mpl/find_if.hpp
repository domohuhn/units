/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_FIND_IF_INCLUDED
#define DH_MPL_FIND_IF_INCLUDED

#include "dh/mpl/detail/find_if_impl.hpp"

namespace dh {
namespace mpl {

/** @brief Find the first element for which the predicate is true.
 * 
 * @note Since c++11 does not have variable templates, this filter cannot use a nested
 * value template. Instead, a class predicate with a nested type containing a value has to be provided as argument.
 */
template<class predicate>
struct find_if {
    template<typename... pack>
    using type = typename detail::find_if_impl<predicate, is_less(1,sizeof...(pack)) >::template type<pack...>;
};

}
}

#endif /* DH_MPL_FIND_IF_INCLUDED */
