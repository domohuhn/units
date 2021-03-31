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
#include <type_traits>
#include <tuple>
#include "gtest/gtest.h"

using namespace dh::mpl;

// Compilation test

constexpr intmax_t add_result1 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine>::value;
constexpr intmax_t add_result2 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero>::value;
constexpr intmax_t add_result3 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four>::value;
constexpr intmax_t add_result4 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five>::value;
constexpr intmax_t add_result5 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five,one>::value;
constexpr intmax_t add_result6 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five,one,seven>::value;
constexpr intmax_t add_result7 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five,one,seven,eight>::value;
constexpr intmax_t add_result8 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five,one,seven,eight,nine>::value;
constexpr intmax_t add_result9 = accumulate_value<dh::mpl::add<intmax_t>>::template type<two,nine,zero,four,five,one,seven,eight,nine,three>::value;

static_assert( add_result1 == 11 , "values should be the same");
static_assert( add_result2 == 11   , "values should be the same");
static_assert( add_result3 == 15   , "values should be the same");
static_assert( add_result4 == 20   , "values should be the same");
static_assert( add_result5 == 21   , "values should be the same");
static_assert( add_result6 == 28   , "values should be the same");
static_assert( add_result7 == 36   , "values should be the same");
static_assert( add_result8 == 45   , "values should be the same");
static_assert( add_result9 == 48   , "values should be the same");

// if the test compiles, this will never fail
TEST(MPL, AccumulateValue) {
    ASSERT_EQ(add_result1 , 11);
    ASSERT_EQ(add_result2 , 11);
    ASSERT_EQ(add_result3 , 15);
    ASSERT_EQ(add_result4 , 20);
    ASSERT_EQ(add_result5 , 21);
    ASSERT_EQ(add_result6 , 28);
    ASSERT_EQ(add_result7 , 36);
    ASSERT_EQ(add_result8 , 45);
    ASSERT_EQ(add_result9 , 48);
}
