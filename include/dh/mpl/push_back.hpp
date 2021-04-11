/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_PUSH_BACK_INCLUDED
#define DH_MPL_PUSH_BACK_INCLUDED

#include "dh/mpl/list.hpp"

namespace dh {
namespace mpl {

/** @brief Add an element at the end of list, then wrap list into container.
 */
template<typename to_add, template <typename...> class container = dh::mpl::list >
struct push_back {
    template<typename... pack>
    using type = container< pack... , to_add >;
};


}
}

#endif /* DH_MPL_PUSH_BACK_INCLUDED */
