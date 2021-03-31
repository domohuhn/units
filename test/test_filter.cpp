/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/mpl/filter.hpp"
#include "dh/mpl/wrap.hpp"
#include <cstdint>
#include <type_traits>
#include <tuple>
#include "gtest/gtest.h"

using namespace dh::mpl;

// Compilation test

template<intmax_t A>
struct filter_input {
    static constexpr intmax_t value = A;
};

template<typename A>
struct check_value_zero {
    static constexpr bool value = A::value!=0;
};

using result_empty_input = typename filter<wrap<check_value_zero>>::template type<>;
using result_empty_output = typename filter<wrap<check_value_zero>>::template type<filter_input<0>,filter_input<0>,filter_input<0>,filter_input<0>>;
using result_partial_output = typename filter<wrap<check_value_zero>>::template type<filter_input<1>,filter_input<0>,filter_input<3>,filter_input<0>,filter_input<-1>>;
using result_all_output = typename filter<wrap<check_value_zero>>::template type<filter_input<1>,filter_input<3>,filter_input<-1>>;

using expected_output = list<filter_input<1>,filter_input<3>,filter_input<-1>>;

static_assert(std::is_same<result_empty_input,list<>>::value,"should be the same");
static_assert(std::is_same<result_empty_output,list<>>::value,"should be the same");
static_assert(std::is_same<result_partial_output,expected_output>::value,"should be the same");
static_assert(std::is_same<result_all_output,expected_output>::value,"should be the same");

// if the test compiles, this will never fail
TEST(MPL, Filter) {
    ASSERT_TRUE((std::is_same<result_empty_input,list<>>::value));
    ASSERT_TRUE((std::is_same<result_empty_output,list<>>::value));
    ASSERT_TRUE((std::is_same<result_partial_output,expected_output>::value));
    ASSERT_TRUE((std::is_same<result_all_output,expected_output>::value));
}
