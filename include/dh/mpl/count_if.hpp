/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_COUNT_IF_INCLUDED
#define DH_MPL_COUNT_IF_INCLUDED

#include "dh/mpl/filter.hpp"

namespace dh {
namespace mpl {

/** @brief Count the number of elements where the predicate is true. 
 * Result is stored in the static data member size.
 */
template<class predicate>
using count_if = filter<predicate>;

}
}

#endif /* DH_MPL_COUNT_IF_INCLUDED */
