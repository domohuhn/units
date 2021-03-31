/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_TEST_NUMBERED_STRUCTS_INCLUDED
#define DH_TEST_NUMBERED_STRUCTS_INCLUDED

#include <cstdint>

template<intmax_t v>
struct accumulate_type_test_struct {
    static constexpr intmax_t value = v;
};
using zero = accumulate_type_test_struct<0>;
using one = accumulate_type_test_struct<1>;
using two = accumulate_type_test_struct<2>;
using three = accumulate_type_test_struct<3>;
using four = accumulate_type_test_struct<4>;
using five = accumulate_type_test_struct<5>;
using six = accumulate_type_test_struct<6>;
using seven = accumulate_type_test_struct<7>;
using eight = accumulate_type_test_struct<8>;
using nine = accumulate_type_test_struct<9>;


#endif /* DH_TEST_NUMBERED_STRUCTS_INCLUDED */
