/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/mpl/min_element.hpp"
#include "dh/mpl/wrap.hpp"
#include "numbered_structs.hpp"
#include <type_traits>
#include <tuple>

using namespace dh::mpl;

// Compilation test

template<typename lhs, typename rhs>
struct is_greater {
    static constexpr bool value = lhs::value < rhs::value;
};

using type_result1 = typename min_element<wrap<is_greater>>::template type<seven,nine>;
using type_result2 = typename min_element<wrap<is_greater>>::template type<five,five,nine>;
using type_result3 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four>;
using type_result4 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five>;
using type_result5 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five,one>;
using type_result6 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five,one,seven>;
using type_result7 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five,one,seven,eight>;
using type_result8 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five,one,seven,eight,nine>;
using type_result9 = typename min_element<wrap<is_greater>>::template type<seven,nine,five,four,five,one,seven,eight,nine,three>;

static_assert( type_result1::value == 7   , "types should be the same");
static_assert( type_result2::value == 5   , "types should be the same");
static_assert( type_result3::value == 4   , "types should be the same");
static_assert( type_result4::value == 4   , "types should be the same");
static_assert( type_result5::value == 1   , "types should be the same");
static_assert( type_result6::value == 1   , "types should be the same");
static_assert( type_result7::value == 1   , "types should be the same");
static_assert( type_result8::value == 1   , "types should be the same");
static_assert( type_result9::value == 1   , "types should be the same");

// if the test compiles, this will never fail
TEST(MPL, MinElement) {
    ASSERT_EQ(type_result1::value , 7);
    ASSERT_EQ(type_result2::value , 5);
    ASSERT_EQ(type_result3::value , 4);
    ASSERT_EQ(type_result4::value , 4);
    ASSERT_EQ(type_result5::value , 1);
    ASSERT_EQ(type_result6::value , 1);
    ASSERT_EQ(type_result7::value , 1);
    ASSERT_EQ(type_result8::value , 1);
    ASSERT_EQ(type_result9::value , 1);
}
