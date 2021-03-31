/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/mpl/join.hpp"
#include <cstdint>
#include <type_traits>

using namespace dh::mpl;

// Compilation test

using joined_type1 = typename join::template type<>;
using joined_type2 = typename join::template type<list<bool>>;
using joined_type3 = typename join::template type<list<bool>,list<char>>;
using joined_type4 = typename join::template type<list<bool>,list<char>,list<int32_t>>;
using joined_type5 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>>;
using joined_type6 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>>;
using joined_type7 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>,list<int16_t>>;
using joined_type8 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>,list<int16_t>,list<uint16_t>>;
using joined_type9 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>,list<int16_t>,list<uint16_t>,list<>>;
using joined_type10 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>,list<int16_t>,list<uint16_t>,list<>,list<uint32_t,uint64_t>>;
using joined_type11 = typename join::template type<list<bool>,list<char>,list<int32_t>,list<int64_t>,list<>,list<int16_t>,list<uint16_t>,list<>,list<uint32_t,uint64_t>,list<float,double>>;

using result_type1  = list<>;
using result_type2  = list<bool>;
using result_type3  = list<bool,char>;
using result_type4  = list<bool,char,int32_t>;
using result_type5  = list<bool,char,int32_t,int64_t>;
using result_type6  = list<bool,char,int32_t,int64_t>;
using result_type7  = list<bool,char,int32_t,int64_t,int16_t>;
using result_type8  = list<bool,char,int32_t,int64_t,int16_t,uint16_t>;
using result_type9  = list<bool,char,int32_t,int64_t,int16_t,uint16_t>;
using result_type10 = list<bool,char,int32_t,int64_t,int16_t,uint16_t,uint32_t,uint64_t>;
using result_type11 = list<bool,char,int32_t,int64_t,int16_t,uint16_t,uint32_t,uint64_t,float,double>;


static_assert(std::is_same<joined_type1 ,result_type1>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type2 ,result_type2>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type3 ,result_type3>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type4 ,result_type4>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type5 ,result_type5>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type6 ,result_type6>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type7 ,result_type7>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type8 ,result_type8>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type9 ,result_type9>::value  , "These types should be the same.");
static_assert(std::is_same<joined_type10,result_type10>::value , "These types should be the same.");
static_assert(std::is_same<joined_type11,result_type11>::value , "These types should be the same.");

// if the test compiles, this will never fail
TEST(MPL, Join) {
    ASSERT_TRUE((std::is_same<joined_type1 ,result_type1>::value ));
    ASSERT_TRUE((std::is_same<joined_type2 ,result_type2>::value ));
    ASSERT_TRUE((std::is_same<joined_type3 ,result_type3>::value ));
    ASSERT_TRUE((std::is_same<joined_type4 ,result_type4>::value ));
    ASSERT_TRUE((std::is_same<joined_type5 ,result_type5>::value ));
    ASSERT_TRUE((std::is_same<joined_type6 ,result_type6>::value ));
    ASSERT_TRUE((std::is_same<joined_type7 ,result_type7>::value ));
    ASSERT_TRUE((std::is_same<joined_type8 ,result_type8>::value ));
    ASSERT_TRUE((std::is_same<joined_type9 ,result_type9>::value ));
    ASSERT_TRUE((std::is_same<joined_type10,result_type10>::value));
    ASSERT_TRUE((std::is_same<joined_type11,result_type11>::value));
}
