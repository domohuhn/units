/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_PUSH_FRONT_INCLUDED
#define DH_MPL_PUSH_FRONT_INCLUDED

#include "dh/mpl/list.hpp"

namespace dh {
namespace mpl {

/** @brief Add element in front of list
 */
template<typename to_add, template <typename...> class container = dh::mpl::list >
struct push_front {
    template<typename... pack>
    using type = container< to_add, pack... >;
};


}
}

#endif /* DH_MPL_PUSH_FRONT_INCLUDED */
