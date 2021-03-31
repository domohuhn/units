/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/mpl/accumulate.hpp"
#include "dh/mpl/functors.hpp"
#include "numbered_structs.hpp"
#include "gtest/gtest.h"
#include <type_traits>

using namespace dh::mpl;

// Compilation test


struct accumulate_type_tester {
    template< typename A, typename B>
    using type = accumulate_type_test_struct<A::value + B::value>;
};

using type_result1 = typename accumulate<accumulate_type_tester>::template type<two,nine>;
using type_result2 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero>;
using type_result3 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four>;
using type_result4 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five>;
using type_result5 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five,one>;
using type_result6 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five,one,seven>;
using type_result7 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five,one,seven,eight>;
using type_result8 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five,one,seven,eight,nine>;
using type_result9 = typename accumulate<accumulate_type_tester>::template type<two,nine,zero,four,five,one,seven,eight,nine,three>;

static_assert( type_result1::value == 11   , "types should be the same");
static_assert( type_result2::value == 11   , "types should be the same");
static_assert( type_result3::value == 15   , "types should be the same");
static_assert( type_result4::value == 20   , "types should be the same");
static_assert( type_result5::value == 21   , "types should be the same");
static_assert( type_result6::value == 28   , "types should be the same");
static_assert( type_result7::value == 36   , "types should be the same");
static_assert( type_result8::value == 45   , "types should be the same");
static_assert( type_result9::value == 48   , "types should be the same");

// if the test compiles, this will never fail
TEST(MPL, AccumulateType) {
    ASSERT_EQ(type_result1::value , 11);
    ASSERT_EQ(type_result2::value , 11);
    ASSERT_EQ(type_result3::value , 15);
    ASSERT_EQ(type_result4::value , 20);
    ASSERT_EQ(type_result5::value , 21);
    ASSERT_EQ(type_result6::value , 28);
    ASSERT_EQ(type_result7::value , 36);
    ASSERT_EQ(type_result8::value , 45);
    ASSERT_EQ(type_result9::value , 48);
}
