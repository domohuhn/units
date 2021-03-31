/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/mpl/transform.hpp"
#include <cstdint>
#include <type_traits>
#include <tuple>

using namespace dh::mpl;

// Compilation test

template<intmax_t A, intmax_t B, intmax_t C>
struct transform_tester {
    static constexpr intmax_t a = A;
    static constexpr intmax_t b = B;
    static constexpr intmax_t c = C;
};

template<typename A>
struct add_shift_impl;
template<intmax_t A, intmax_t B, intmax_t C>
struct add_shift_impl<transform_tester<A,B,C>> {
    using type = transform_tester<A+1,A+1,C>;
};
struct add_shift {
    template<typename T>
    using type = typename add_shift_impl<T>::type;
};


template<typename A>
struct add_shift_impl2;
template<intmax_t A, intmax_t B, intmax_t C>
struct add_shift_impl2<transform_tester<A,B,C>> {
    using type = transform_tester<A+1,B,A+1>;
};
struct add_shift2 {
    template<typename T>
    using type = typename add_shift_impl2<T>::type;
};

using input_list = list<transform_tester<0,0,0>, transform_tester<1,0,0>, transform_tester<5,0,0>, transform_tester<10,0,0>>;
using middle_list = list<transform_tester<1,1,0>, transform_tester<2,2,0>, transform_tester<6,6,0>, transform_tester<11,11,0>>;
using final_list = list<transform_tester<2,1,2>, transform_tester<3,2,3>, transform_tester<7,6,7>, transform_tester<12,11,12>>;
using final_tuple = std::tuple<transform_tester<2,1,2>, transform_tester<3,2,3>, transform_tester<7,6,7>, transform_tester<12,11,12>>;

using middle_result = typename input_list::template then< transform<add_shift> >; 
using end_result = typename input_list::template then< transform<add_shift> >
::template then<transform<add_shift2>>;

using repacked_result = typename input_list::template then< transform<add_shift> >
::template then<transform<add_shift2>>::template wrap<std::tuple>;


static_assert(std::is_same<middle_list,middle_result>::value , "First step");
static_assert(std::is_same<final_list,end_result>::value , "Second step");
static_assert(std::is_same<final_tuple,repacked_result>::value , "wrapped in tuple");

// if the test compiles, this will never fail
TEST(MPL, Transform) {
    ASSERT_TRUE((std::is_same<middle_list,middle_result>::value));
    ASSERT_TRUE((std::is_same<final_list,end_result>::value));
    ASSERT_TRUE((std::is_same<final_tuple,repacked_result>::value));
}
