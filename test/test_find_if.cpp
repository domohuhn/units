/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/mpl/find_if.hpp"
#include "dh/mpl/wrap.hpp"
#include "dh/mpl/front.hpp"
#include "numbered_structs.hpp"
#include <type_traits>

using namespace dh::mpl;

// Compilation test

template<typename current>
struct is_one {
    static constexpr bool value = current::value == 1;
};

using type_result1 = typename find_if<wrap<is_one>>::template type<seven>;
using type_result2 = typename find_if<wrap<is_one>>::template type<seven,nine,five>;
using type_result3 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four>;
using type_result4 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five>;
using type_result5 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five,one>;
using type_result6 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five,one,seven>;
using type_result7 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five,one,seven,eight>;
using type_result8 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five,one,seven,eight,nine>;
using type_result9 = typename find_if<wrap<is_one>>::template type<seven,nine,five,four,five,one,seven,eight,nine,three>;

static_assert( type_result1::empty            , "should not find anything");
static_assert( type_result2::empty            , "should not find anything");
static_assert( type_result3::empty            , "should not find anything");
static_assert( type_result4::empty            , "should not find anything");
static_assert( type_result5::empty == false   , "finds one");
static_assert( type_result6::empty == false   , "finds one");
static_assert( type_result7::empty == false   , "finds one");
static_assert( type_result8::empty == false   , "finds one");
static_assert( type_result9::empty == false   , "finds one");
static_assert( type_result5::size == 1        , "finds one");
static_assert( type_result6::size == 1        , "finds one");
static_assert( type_result7::size == 1        , "finds one");
static_assert( type_result8::size == 1        , "finds one");
static_assert( type_result9::size == 1        , "finds one");
static_assert( std::is_same< front_t<type_result5> , one >::value  , "types should be the same");
static_assert( std::is_same< front_t<type_result6> , one >::value  , "types should be the same");
static_assert( std::is_same< front_t<type_result7> , one >::value  , "types should be the same");
static_assert( std::is_same< front_t<type_result8> , one >::value  , "types should be the same");
static_assert( std::is_same< front_t<type_result9> , one >::value  , "types should be the same");

// if the test compiles, this will never fail
TEST(MPL, FindIf) {
    ASSERT_TRUE( type_result1::empty           );
    ASSERT_TRUE( type_result2::empty           );
    ASSERT_TRUE( type_result3::empty           );
    ASSERT_TRUE( type_result4::empty           );
    ASSERT_TRUE( type_result5::empty == false  );
    ASSERT_TRUE( type_result6::empty == false  );
    ASSERT_TRUE( type_result7::empty == false  );
    ASSERT_TRUE( type_result8::empty == false  );
    ASSERT_TRUE( type_result9::empty == false  );
    ASSERT_TRUE( type_result5::size == 1       );
    ASSERT_TRUE( type_result6::size == 1       );
    ASSERT_TRUE( type_result7::size == 1       );
    ASSERT_TRUE( type_result8::size == 1       );
    ASSERT_TRUE( type_result9::size == 1       );
    ASSERT_TRUE( (std::is_same< front_t<type_result5> , one >::value) );
    ASSERT_TRUE( (std::is_same< front_t<type_result6> , one >::value) );
    ASSERT_TRUE( (std::is_same< front_t<type_result7> , one >::value) );
    ASSERT_TRUE( (std::is_same< front_t<type_result8> , one >::value) );
    ASSERT_TRUE( (std::is_same< front_t<type_result9> , one >::value) );
}

