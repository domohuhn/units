/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/units/quantity_conversion.hpp"
#include "dh/units/si_units.hpp"
#include "gtest/gtest.h"

// Compilation test
using namespace dh::mpl;
using namespace dh::units;
using namespace si;

using list0 = list<>;
using list1 = list<unit_meter>;
using list2 = list<unit_kelvin>;
using list3 = list<unit_nanometer>;
using list4 = list<unit_square_meter>;
using list5 = list<unit_meter, unit_kilogram>; // kg m -> 1000
using list6 = list<unit_milligram, unit_kilometer>; // mg km -> 1
using list7 = list<unit_kilogram, unit_meter>;

using result_type1 = unit_list_conversion_factor<double,list0,list0>;
using result_type2 = unit_list_conversion_factor<double,list1,list0>;
using result_type3 = unit_list_conversion_factor<double,list0,list1>;
using result_type4 = unit_list_conversion_factor<double,list1,list1>;
using result_type5 = unit_list_conversion_factor<double,list5,list7>;
using result_type6 = unit_list_conversion_factor<double,list5,list6>; 
using result_type7 = unit_list_conversion_factor<double,list6,list5>; 
using result_type8 = unit_list_conversion_factor<double,list1,list3>; 
using result_type9 = unit_list_conversion_factor<double,list3,list1>; 



static_assert( result_type1::value == 1.0          , "empty lists need no conversion");
static_assert( result_type2::value == 1.0          , "empty lists need no conversion");
static_assert( result_type3::value == 1.0          , "empty lists need no conversion");
static_assert( result_type4::value == 1.0          , "same lists need no conversion");
static_assert( result_type5::value == 1.0          , "same lists need no conversion");
static_assert( result_type6::value == 0.001        , "conversion needed");
static_assert( result_type7::value == 1000.0       , "conversion needed");
static_assert( result_type8::value == 1.0e-9       , "conversion needed");
static_assert( result_type9::value == 1000000000.0 , "conversion needed");

// if the test compiles, this will never fail
TEST(Units, QuantityConversion) {
    ASSERT_EQ( result_type1::value , 1.0          );
    ASSERT_EQ( result_type2::value , 1.0          );
    ASSERT_EQ( result_type3::value , 1.0          );
    ASSERT_EQ( result_type4::value , 1.0          );
    ASSERT_EQ( result_type5::value , 1.0          );
    ASSERT_EQ( result_type6::value , 0.001        );
    ASSERT_EQ( result_type7::value , 1000.0       );
    ASSERT_EQ( result_type8::value , 1.0e-9       );
    ASSERT_EQ( result_type9::value , 1000000000.0 );
}


using add_combine_result = typename combine_unit_power<mpl::add<intmax_t>>::template type<::si::unit_meter,::si::unit_millimeter>;
static_assert(std::is_same<add_combine_result, unit<dimensions::length,std::ratio<1,1000>,2> >::value, "should be the same");


using comb_list1 = mpl::list<unit_meter, unit_kilogram, unit_second>;
using comb_list2 = mpl::list<unit_kelvin, unit_per_second, unit_millimeter>;

using multiplication_result_type_test = typename multiplication_result<comb_list1,comb_list2>::template type<dh::units::quantity,double>;

static_assert(std::is_same<multiplication_result_type_test, dh::units::quantity<double,unit_square_millimeter,unit_kilogram, unit_kelvin > >::value, "should be the same");

using division_result_type_test = typename division_result<comb_list1,comb_list2>::template type<dh::units::quantity,double>;

static_assert(std::is_same<division_result_type_test, dh::units::quantity<double,unit_kilogram, dh::units::unit<dh::units::dimensions::time, std::ratio<1LL, 1LL>, 2LL> , dh::units::unit<dh::units::dimensions::thermodynamic_temperature, std::ratio<1LL, 1LL>, -1LL> > >::value, "should be the same");

// test impulse addition

using impulse_list = mpl::list<unit_kilogram, unit_meter, unit_per_second>;
using add_result_units = typename combine_unit_lists_selecting_higher_accuracy<impulse_list,impulse_list>::unit_list;
static_assert(std::is_same<impulse_list, add_result_units >::value, "should be the same");

using impulse_list2 = mpl::list<unit_gram, unit_meter, unit_per_second>;

using add_result_units2 = typename combine_unit_lists_selecting_higher_accuracy<impulse_list,impulse_list2>::unit_list;
using add_result_units3 = typename combine_unit_lists_selecting_higher_accuracy<impulse_list2,impulse_list>::unit_list;
static_assert(std::is_same<impulse_list2, add_result_units2 >::value, "should be the same");
static_assert(std::is_same<impulse_list2, add_result_units3 >::value, "should be the same");


