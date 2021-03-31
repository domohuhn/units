/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/mpl/is_unique.hpp"
#include "dh/mpl/wrap.hpp"
#include "numbered_structs.hpp"
#include <type_traits>

using namespace dh::mpl;

// Compilation test

using type_result1 = typename is_unique<wrap<std::is_same>>::template type<seven>;
using type_result2 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five>;
using type_result3 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four>;
using type_result4 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five>;
using type_result5 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five,one>;
using type_result6 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five,one,seven>;
using type_result7 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five,one,seven,eight>;
using type_result8 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five,one,seven,eight,nine>;
using type_result9 = typename is_unique<wrap<std::is_same>>::template type<seven,nine,five,four,five,one,seven,eight,nine,three>;

static_assert( type_result1::value            , "should not find anything");
static_assert( type_result2::value            , "should not find anything");
static_assert( type_result3::value            , "should not find anything");
static_assert( !type_result4::value            , "finds one");
static_assert( !type_result5::value            , "finds one");
static_assert( !type_result6::value            , "finds one");
static_assert( !type_result7::value            , "finds one");
static_assert( !type_result8::value            , "finds one");
static_assert( !type_result9::value            , "finds one");

// if the test compiles, this will never fail
TEST(MPL, IsUnique) {
    ASSERT_TRUE( type_result1::value ); 
    ASSERT_TRUE( type_result2::value ); 
    ASSERT_TRUE( type_result3::value ); 
    ASSERT_TRUE( !type_result4::value); 
    ASSERT_TRUE( !type_result5::value); 
    ASSERT_TRUE( !type_result6::value); 
    ASSERT_TRUE( !type_result7::value); 
    ASSERT_TRUE( !type_result8::value); 
    ASSERT_TRUE( !type_result9::value); 
}

