/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_CONDITIONAL_INCLUDED
#define DH_MPL_CONDITIONAL_INCLUDED

namespace dh {
namespace mpl {

/** @brief Structure for conditionals.
 * The contained type is the first template value for true
 * and the second one if the conditional is false.
 */
template<bool b>
struct conditional {
    template<typename success, typename other>
    using type = success;
};

template<>
struct conditional<false> {
    template<typename success, typename other>
    using type = other;
};

}
}

#endif /* DH_MPL_CONDITIONAL_INCLUDED */

