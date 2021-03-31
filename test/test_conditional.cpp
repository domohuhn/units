/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/mpl/conditional.hpp"
#include <type_traits>
#include "gtest/gtest.h"

using namespace dh::mpl;

// Compilation test

static_assert(std::is_same<typename conditional<true>::template type<int,double>,int>::value , "This should select the first type.");
static_assert(std::is_same<typename conditional<false>::template type<int,double>,double>::value , "This should select the second type.");

// if the test compiles, this will never fail
TEST(MPL, Conditional) {
    ASSERT_TRUE((std::is_same<typename conditional<true>::template type<int,double>,int>::value));
    ASSERT_TRUE((std::is_same<typename conditional<false>::template type<int,double>,double>::value));
}
