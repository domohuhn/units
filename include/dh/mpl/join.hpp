/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_JOIN_INCLUDED
#define DH_MPL_JOIN_INCLUDED

#include "dh/mpl/list.hpp"
#include "dh/mpl/detail/join_impl.hpp"
#include "dh/mpl/comparisons.hpp"

namespace dh {
namespace mpl {

/** @brief Joins the packs given in the lists provided as template arguments to a single list */
struct join {
    template<typename... pack>
    using type = typename detail::join<is_greater(sizeof...(pack),0)>::template type<pack...>;
};


}
}

#endif /* DH_MPL_JOIN_INCLUDED */



