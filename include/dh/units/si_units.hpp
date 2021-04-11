/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_UNITS_SI_UNIT_INCLUDED
#define DH_UNITS_SI_UNIT_INCLUDED

#include "dh/units/declaration_macros.hpp"
#include "dh/units/dimensions.hpp"
#include "dh/units/unit.hpp"
#include "dh/units/quantity.hpp"
#include <ratio>

namespace si {

template<typename T>
using scalar = ::dh::units::scalar<T>;


DH_DECLARE_QUANTITY_ALL_PREFIXES( , meter , dh::units::dimensions::length , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( square_ , meter , dh::units::dimensions::length , 2)
DH_DECLARE_QUANTITY_ALL_PREFIXES( cubic_ , meter , dh::units::dimensions::length , 3)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , second , dh::units::dimensions::time , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , kelvin , dh::units::dimensions::thermodynamic_temperature , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , gram , dh::units::dimensions::mass , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , ampere , dh::units::dimensions::electric_current , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , mol , dh::units::dimensions::amount_of_substance , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , candela , dh::units::dimensions::luminous_intensity , 1)

using ratio_minute = std::ratio<60,1>;
using ratio_hour = std::ratio<3600,1>;
using ratio_day = std::ratio<86400,1>;
using ratio_week = std::ratio<604800,1>;
using ratio_month = std::ratio<2629800,1>;
using ratio_year = std::ratio<31557600,1>; // julian year
using ratio_astronomical_unit = std::ratio<149597870700,1>;
using ratio_lightyear = std::ratio<9460730472580800,1>;
using ratio_speed_of_light = std::ratio<299792458,1>;

using ratio_radian = std::ratio<5729577951308232087,100000000000000000>;

using ratio_degree = std::ratio<1,1>;
using ratio_arcmin = std::ratio<1,60>;
using ratio_arcsec = std::ratio<1,3600>;
using ratio_milliarcsec = std::ratio<1,3600000>;

using unit_per_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -1 >;
using unit_per_square_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -2 >;
using unit_per_cubic_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -3 >;
using unit_per_hour = dh::units::unit<dh::units::dimensions::time, ratio_hour, -1 >;

using unit_astronomical_unit = dh::units::unit<dh::units::dimensions::length, ratio_astronomical_unit, 1 >;
using unit_lightyear = dh::units::unit<dh::units::dimensions::length, ratio_lightyear, 1 >;
using unit_lightsecond = dh::units::unit<dh::units::dimensions::length, ratio_speed_of_light, 1 >;

using unit_minute = dh::units::unit<dh::units::dimensions::time, ratio_minute, 1 >;
using unit_hour = dh::units::unit<dh::units::dimensions::time, ratio_hour, 1 >;
using unit_day = dh::units::unit<dh::units::dimensions::time, ratio_day, 1 >;
using unit_week = dh::units::unit<dh::units::dimensions::time, ratio_week, 1 >;
using unit_month = dh::units::unit<dh::units::dimensions::time, ratio_month, 1 >;
using unit_year = dh::units::unit<dh::units::dimensions::time, ratio_year, 1 >;

using unit_radian = dh::units::unit<dh::units::dimensions::angle, ratio_radian, 1 >;
using unit_degree = dh::units::unit<dh::units::dimensions::angle, ratio_degree, 1 >;
using unit_arcmin = dh::units::unit<dh::units::dimensions::angle, ratio_arcmin, 1 >;
using unit_arcsec = dh::units::unit<dh::units::dimensions::angle, ratio_arcsec, 1 >;
using unit_milliarcsec = dh::units::unit<dh::units::dimensions::angle, ratio_milliarcsec, 1 >;
using unit_celsius = dh::units::unit<dh::units::dimensions::degree_celsius, std::ratio<1,1>, 1 >;



DH_DECLARE_QUANTITY( astronomical_unit, unit_astronomical_unit )
DH_DECLARE_QUANTITY( lightyear, unit_lightyear )

DH_DECLARE_QUANTITY( ton, unit_megagram )
DH_DECLARE_QUANTITY( liter, unit_cubic_decimeter )
DH_DECLARE_QUANTITY( milliliter, unit_cubic_centimeter )

DH_DECLARE_QUANTITY( minute, unit_minute )
DH_DECLARE_QUANTITY( hour, unit_hour )
DH_DECLARE_QUANTITY( day, unit_day )
DH_DECLARE_QUANTITY( week, unit_week )
DH_DECLARE_QUANTITY( month, unit_month )
DH_DECLARE_QUANTITY( year, unit_year )

DH_DECLARE_QUANTITY( meter_per_second, unit_meter, unit_per_second )
DH_DECLARE_QUANTITY( kilometer_per_hour, unit_kilometer, unit_per_hour )
DH_DECLARE_QUANTITY( lightspeed, unit_lightsecond, unit_per_second )


DH_DECLARE_QUANTITY( radian, unit_radian )
DH_DECLARE_QUANTITY( degree, unit_degree )
DH_DECLARE_QUANTITY( arcminute, unit_arcmin )
DH_DECLARE_QUANTITY( arcsecond, unit_arcsec )
DH_DECLARE_QUANTITY( milliarcsecond, unit_milliarcsec )
DH_DECLARE_QUANTITY( celsius, unit_celsius )

// derived quantities
DH_DECLARE_QUANTITY( acceleration, unit_meter, unit_per_square_second )

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( newton , "N", unit_kilogram, unit_meter, unit_per_square_second)
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( joule , "J", unit_kilogram, unit_square_meter, unit_per_square_second)
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( watt , "W", unit_kilogram, unit_square_meter, unit_per_cubic_second)

using unit_mass_wh = dh::units::unit<dh::units::dimensions::mass, std::ratio<3600000,1>, 1 >;
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( watthour , "Wh", unit_mass_wh, unit_square_meter, unit_per_square_second)


using unit_per_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, -1 >;
using unit_per_square_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, -2 >;
using unit_square_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, 2 >;
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( volt , "V", unit_kilogram, unit_square_meter, unit_per_cubic_second , unit_per_ampere)

using unit_per_meter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,1>, -1 >;
using unit_per_square_meter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,1>, -2 >;
using unit_per_centimeter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,100>, -1 >;
using unit_per_kilogram = dh::units::unit<dh::units::dimensions::mass, std::ratio<1,1>, -1 >;
using unit_up4_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, 4 >;

DH_DECLARE_QUANTITY( hertz, unit_per_second )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( pascal , "pa", unit_kilogram, unit_per_meter, unit_per_square_second )
DH_DECLARE_QUANTITY( millibar, unit_kilogram, unit_per_centimeter, unit_per_square_second )
DH_DECLARE_QUANTITY( bar, unit_megagram, unit_per_centimeter, unit_per_square_second )

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( ohm , "ohm", unit_kilogram, unit_square_meter, unit_per_cubic_second , unit_per_square_ampere )

DH_DECLARE_QUANTITY( farad, unit_square_ampere, unit_up4_second, unit_per_kilogram, unit_per_square_meter)

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( coulomb , "C",  unit_ampere, unit_second )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( weber , "Wb",  unit_kilogram, unit_square_meter, unit_per_square_second , unit_per_ampere )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( tesla , "T", unit_kilogram,  unit_per_square_second , unit_per_ampere )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( henry , "H", unit_kilogram, unit_square_meter, unit_per_square_second , unit_per_square_ampere )



}

#endif /* DH_UNITS_SI_UNIT_INCLUDED */
