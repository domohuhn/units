/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_IS_UNIQUE_INCLUDED
#define DH_MPL_IS_UNIQUE_INCLUDED

#include "dh/mpl/detail/is_unique_impl.hpp"

namespace dh {
namespace mpl {

/** @brief Check if the binary predicate holds true if applied to any pair of arguments.
 * Instantiates O(n) types for the predicate and does O(n^2) comparisions. 
 * @return Contains either std::true_type or std::false_type
 **/
template<class binary_predicate>
struct is_unique {

    template<typename... pack>
    using type = typename detail::is_unique_impl<binary_predicate, is_less(1,sizeof...(pack)) >::template type<pack...>;
};

}
}

#endif /* DH_MPL_IS_UNIQUE_INCLUDED */

