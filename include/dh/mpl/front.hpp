/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FRONT_INCLUDED
#define DH_MPL_FRONT_INCLUDED


namespace dh {
namespace mpl {

/** @brief Get the first element of the template list.
 * Compilation will only work if there is an element.
 */
struct front {
    template<typename first, typename... pack>
    using type = first;
};

template<typename in>
using front_t = typename in::template then<front>;

}
}

#endif /* DH_MPL_FRONT_INCLUDED */
