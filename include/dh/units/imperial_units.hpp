/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_IMPERIAL_UNITS_INCLUDED
#define DH_UNITS_IMPERIAL_UNITS_INCLUDED

#include "dh/units/si_units.hpp"

namespace imperial {
    
template<typename T>
using scalar = ::dh::units::scalar<T>;

using ratio_mile = std::ratio<1609344,1000>;
using ratio_yard = std::ratio<9144,10000>;
using ratio_foot = std::ratio<3048,10000>;
using ratio_inch = std::ratio<254,10000>;
using ratio_pound = std::ratio<45359237, 100000>;
using ratio_ounce = std::ratio<28349523125 , 1000000000>;
using ratio_nautical_mile = std::ratio<1852,1>;
using ratio_acre = std::ratio<6361490723407525334,100000000000000000>;



using base_unit_nautical_mile = dh::units::unit<dh::units::dimensions::length, ratio_nautical_mile, 1 >;
using base_unit_mile = dh::units::unit<dh::units::dimensions::length, ratio_mile, 1 >;
using base_unit_yard = dh::units::unit<dh::units::dimensions::length, ratio_yard, 1 >;
using base_unit_foot = dh::units::unit<dh::units::dimensions::length, ratio_foot, 1 >;
using base_unit_inch = dh::units::unit<dh::units::dimensions::length, ratio_inch, 1 >;

using unit_acre = dh::units::unit<dh::units::dimensions::length, ratio_acre, 2 >;
using unit_square_mile = dh::units::unit<dh::units::dimensions::length, ratio_mile, 2 >;
using unit_square_yard = dh::units::unit<dh::units::dimensions::length, ratio_yard, 2 >;
using unit_square_foot = dh::units::unit<dh::units::dimensions::length, ratio_foot, 2 >;
using unit_square_inch = dh::units::unit<dh::units::dimensions::length, ratio_inch, 2 >;

using base_unit_pound = dh::units::unit<dh::units::dimensions::mass, ratio_pound, 1 >;
using base_unit_ounce = dh::units::unit<dh::units::dimensions::mass, ratio_ounce, 1 >;
using unit_fahrentheit = dh::units::unit<dh::units::dimensions::degree_fahrenheit, std::ratio<1,1>, 1 >;

DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( nauticalmile , "nmi" , base_unit_nautical_mile )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( mile , "mi" , base_unit_mile )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( yard , "yd" , base_unit_yard )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( foot , "ft" , base_unit_foot )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( inch , "in" , base_unit_inch )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( pound , "lb" , base_unit_pound )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( ounce , "oz" , base_unit_ounce )

DH_DECLARE_QUANTITY( nautical_mile, unit_nauticalmile )
DH_DECLARE_QUANTITY( mile, unit_mile )
DH_DECLARE_QUANTITY( yard, unit_yard )
DH_DECLARE_QUANTITY( foot, unit_foot )
DH_DECLARE_QUANTITY( inch, unit_inch )



DH_DECLARE_QUANTITY( acre, unit_acre )
DH_DECLARE_QUANTITY( square_mile, unit_square_mile )
DH_DECLARE_QUANTITY( square_yard, unit_square_yard )
DH_DECLARE_QUANTITY( square_feet, unit_square_foot )
DH_DECLARE_QUANTITY( square_inch, unit_square_inch )

DH_DECLARE_QUANTITY( pound, unit_pound )
DH_DECLARE_QUANTITY( ounce, unit_ounce )

DH_DECLARE_QUANTITY( miles_per_hour, unit_mile, si::unit_per_hour )
DH_DECLARE_QUANTITY( feet_per_second, unit_foot, si::unit_per_second )
DH_DECLARE_QUANTITY( fahrenheit, unit_fahrentheit )

}

#endif /* DH_UNITS_IMPERIAL_UNITS_INCLUDED */
