/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_COMPARISONS_INCLUDED
#define DH_MPL_COMPARISONS_INCLUDED

#include <cstdint>

namespace dh {
namespace mpl {


// comparisons for use in template args

constexpr bool is_less(size_t a, size_t b) noexcept {
    return a<b;
}

constexpr bool is_greater(size_t a, size_t b) noexcept {
    return a>b;
}

template<typename T>
constexpr bool larger_than_one(T a) noexcept {
    return a>T(1);
}

}
}


#endif /* DH_MPL_COMPARISONS_INCLUDED */
