/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/units.hpp"

// Several print tests - will not fail

using namespace si;

TEST(FormatUnits, Cout) {
    std::cout<<"milliseconds : \""<<     millisecond<>(42.0) <<"\"\n";
    std::cout<<"seconds      : \""<<     second<>(42.0) <<"\"\n";
    std::cout<<"min          : \""<<     minute<>(42.0) <<"\"\n";
    std::cout<<"hour         : \""<<     hour<>(42.0) <<"\"\n";
    std::cout<<"day          : \""<<     day<>(42.0) <<"\"\n";
    std::cout<<"week         : \""<<     week<>(42.0) <<"\"\n";
    std::cout<<"month        : \""<<     month<>(42.0) <<"\"\n";
    std::cout<<"year         : \""<<     year<>(42.0) <<"\"\n";
    std::cout<<"fahrenheit   : \""<<     imperial::fahrenheit<>(42.0) <<"\"\n";
    std::cout<<"celsius      : \""<<     celsius<>(42.0) <<"\"\n";
    std::cout<<"arcsecond    : \""<<     arcsecond<>(42.0) <<"\"\n";
    std::cout<<"arcminute    : \""<<     arcminute<>(42.0) <<"\"\n"; 
    std::cout<<"degree       : \""<<     degree<>(42.0) <<"\"\n";
    std::cout<<"radian       : \""<<     radian<>(42.0) <<"\"\n"; 
    std::cout<<"mps          : \""<<     meter_per_second<>(42.0) <<"\"\n";
    std::cout<<"kph          : \""<<     kilometer_per_hour<>(42.0) <<"\"\n";
    std::cout<<"colomb       : \""<<     coulomb<int>(43) <<"\"\n";
    std::cout<<"kilovolt     : \""<<     kilovolt<int>(47) <<"\"\n";
    std::cout<<"hz           : \""<<     hertz<int>(44) <<"\"\n";
    std::cout<<"nautical     : \""<<     imperial::nautical_mile<int>{} <<"\"\n";
}

TEST(FormatUnits, ToString) {
    std::cout<<"milliseconds : \""<<     to_string(millisecond<>(42.0)) <<"\"\n";
    std::cout<<"seconds      : \""<<     to_string(second<>(42.0)) <<"\"\n";
    std::cout<<"min          : \""<<     to_string(minute<>(42.0)) <<"\"\n";
    std::cout<<"hour         : \""<<     to_string(hour<>(42.0)) <<"\"\n";
    std::cout<<"day          : \""<<     to_string(day<>(42.0)) <<"\"\n";
    std::cout<<"week         : \""<<     to_string(week<>(42.0)) <<"\"\n";
    std::cout<<"month        : \""<<     to_string(month<>(42.0)) <<"\"\n";
    std::cout<<"year         : \""<<     to_string(year<>(42.0)) <<"\"\n";
    std::cout<<"fahrenheit   : \""<<     to_string(imperial::fahrenheit<>(42.0)) <<"\"\n";
    std::cout<<"celsius      : \""<<     to_string(celsius<>(42.0)) <<"\"\n";
    std::cout<<"arcsecond    : \""<<     to_string(arcsecond<>(42.0)) <<"\"\n";
    std::cout<<"arcminute    : \""<<     to_string(arcminute<>(42.0)) <<"\"\n"; 
    std::cout<<"degree       : \""<<     to_string(degree<>(42.0)) <<"\"\n";
    std::cout<<"radian       : \""<<     to_string(radian<>(42.0)) <<"\"\n"; 
    std::cout<<"mps          : \""<<     to_string(meter_per_second<>(42.0)) <<"\"\n";
    std::cout<<"kph          : \""<<     to_string(kilometer_per_hour<>(42.0)) <<"\"\n";
    std::cout<<"colomb       : \""<<     to_string(coulomb<int>(43)) <<"\"\n";
    std::cout<<"kilovolt     : \""<<     to_string(kilovolt<int>(47)) <<"\"\n";
    std::cout<<"hz           : \""<<     to_string(hertz<int>(44)) <<"\"\n";
    std::cout<<"nautical     : \""<<     to_string(imperial::nautical_mile<int>{}) <<"\"\n";
}

#ifndef DH_UNITS_DISABLE_LIBFMT
TEST(FormatUnits, Libfmt) {
    fmt::print("milliseconds : \"{}\"\n", millisecond<>(42.0));
    fmt::print("seconds      : \"{}\"\n",     second<>(42.0) );
    fmt::print("min          : \"{}\"\n",     minute<>(42.0) );
    fmt::print("hour         : \"{}\"\n",     hour<>(42.0) );
    fmt::print("day          : \"{:.3f}\"\n",     day<>(42.0) );
    fmt::print("week         : \"{}\"\n",     week<>(42.0) );
    fmt::print("month        : \"{}\"\n",     month<>(42.0) );
    fmt::print("year         : \"{}\"\n",     year<>(42.0) );
    fmt::print("fahrenheit   : \"{}\"\n",     imperial::fahrenheit<>(42.0) );
    fmt::print("celsius      : \"{}\"\n",     celsius<>(42.0) );
    fmt::print("arcsecond    : \"{}\"\n",     arcsecond<>(42.0) );
    fmt::print("arcminute    : \"{}\"\n",     arcminute<>(42.0) ); 
    fmt::print("degree       : \"{}\"\n",     degree<>(42.0) );
    fmt::print("radian       : \"{}\"\n",     radian<>(42.0) ); 
    fmt::print("mps          : \"{}\"\n",     meter_per_second<>(42.0) );
    fmt::print("kph          : \"{}\"\n",     kilometer_per_hour<>(42.0) );
    fmt::print("energy       : \"{}\"\n",     kilogram<>(80.0)*meter_per_second<>(2.0)*meter_per_second<>(2.0) );
    fmt::print("colomb       : \"{}\"\n",     coulomb<int>(43) );
    fmt::print("kilovolt     : \"{}\"\n",     kilovolt<int>(47) );
    fmt::print("hz           : \"{:>10}\"\n",     hertz<int>(44) );
    fmt::print("nautical     : \"{}\"\n",     imperial::nautical_mile<int>{} );
}
#endif


