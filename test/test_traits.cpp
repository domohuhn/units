/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/units/traits.hpp"
#include "dh/units/si_units.hpp"
#include "gtest/gtest.h"

// Compilation test
using namespace dh::mpl;
using namespace dh::units;
using namespace si;

using list0 = list<>;
using list1 = list<unit_meter>;
using list2 = list<unit_kelvin>;
using list3 = list<unit_millimeter>;
using list4 = list<unit_square_meter>;
using list5 = list<unit_meter, unit_kilogram>;
using list6 = list<unit_milligram, unit_kilometer>;
using list7 = list<unit_kilogram, unit_meter>;

static_assert( lists_contain_same_dimensions<list0,list0>::value          , "empty lists should be the same");
static_assert( lists_contain_same_dimensions<list1,list1>::value          , "lists are the same");
static_assert( lists_contain_same_dimensions<list1,list3>::value          , "lists only differ in prefixes");
static_assert( lists_contain_same_dimensions<list5,list6>::value          , "lists only differ in prefixes");
static_assert( lists_contain_same_dimensions<list1,list6>::value == false , "lists have different sizes");
static_assert( lists_contain_same_dimensions<list1,list4>::value == false , "lists have different power");
static_assert( lists_contain_same_dimensions<list1,list2>::value == false , "lists have different dimensions");
static_assert( lists_contain_same_types<list0,list0>::value               , "empty lists should be the same");
static_assert( lists_contain_same_types<list1,list1>::value               , "lists are the same");
static_assert( lists_contain_same_types<list5,list7>::value               , "lists are the same");
static_assert( lists_contain_same_types<list1,list3>::value == false      , "lists only differ in prefixes");
static_assert( lists_contain_same_types<list5,list6>::value == false      , "lists only differ in prefixes");
static_assert( lists_contain_same_types<list1,list6>::value == false      , "lists have different sizes");
static_assert( lists_contain_same_types<list1,list4>::value == false      , "lists have different power");
static_assert( lists_contain_same_types<list1,list2>::value == false      , "lists have different dimensions");

// if the test compiles, this will never fail
TEST(Units, Traits) {
    ASSERT_TRUE(( lists_contain_same_dimensions<list0,list0>::value          ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list1,list1>::value          ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list1,list3>::value          ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list5,list6>::value          ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list1,list6>::value == false ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list1,list4>::value == false ));
    ASSERT_TRUE(( lists_contain_same_dimensions<list1,list2>::value == false ));
    ASSERT_TRUE(( lists_contain_same_types<list0,list0>::value               ));
    ASSERT_TRUE(( lists_contain_same_types<list1,list1>::value               ));
    ASSERT_TRUE(( lists_contain_same_types<list5,list7>::value               ));
    ASSERT_TRUE(( lists_contain_same_types<list1,list3>::value == false      ));
    ASSERT_TRUE(( lists_contain_same_types<list5,list6>::value == false      ));
    ASSERT_TRUE(( lists_contain_same_types<list1,list6>::value == false      ));
    ASSERT_TRUE(( lists_contain_same_types<list1,list4>::value == false      ));
    ASSERT_TRUE(( lists_contain_same_types<list1,list2>::value == false      ));
}

