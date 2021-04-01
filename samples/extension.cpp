/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/units.hpp"
#include <iostream>

struct pixel_dimension {
    static std::string name() {
        return "pix";
    }
};

// template arguments are dimension, scale factor, power
using unit_pixel = dh::units::unit<pixel_dimension, std::ratio<1,1>, 1>;
// define an alias for the new unit
// using this method will cause long compilation errors
// because the compiler "forgets" aliases
using pixel = dh::units::quantity<int,unit_pixel>;

// if you want nice error messages, you will have to use inheritance:
template <typename T = double>
class pixel2 : public
::dh::units::quantity<T, unit_pixel >
{
public:
    using base_type = ::dh::units::quantity<T, unit_pixel >;
    using base_type::base_type;
    pixel2(const base_type& q) : base_type(q) {}
    pixel2(base_type&& q) : base_type(std::move(q)) {}
    pixel2() = default;
    pixel2(const pixel2&) = default;
    pixel2(pixel2&&) = default;
    pixel2& operator=(const pixel2&) = default;
    pixel2& operator=(pixel2&&) = default;
    ~pixel2() = default;
};

// define a derived unit
struct derived_pixel_per_squaremeter {
    static std::string name() {
        return "pxm" ;
    }
    // for derived units the first unit in the unit list has to have power 1!
    using unit_list = dh::mpl::list< unit_pixel, si::unit_per_square_meter >;
};

// for derived units the power has to be one!
using unit_pixel_per_squaremeter = dh::units::unit<derived_pixel_per_squaremeter, std::ratio<1,1>, 1>;
// define an alias for the new unit
using pixel_per_squaremeter = dh::units::quantity<double,unit_pixel_per_squaremeter>;
/* or do
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT(pixel_per_squaremeter, "pxm" , unit_pixel, si::unit_per_square_meter )
or
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES(pixel_per_squaremeter, "pxm" , unit_pixel, si::unit_per_square_meter )
*/

int main() {
    pixel px(32);
    pixel2<int> px2(10);
    auto sum = px +px2;
    pixel_per_squaremeter pxm = sum/si::square_centimeter<>(2.0);
    std::cout<<sum<<"\n";
    std::cout<<px*px2<<"\n";
    std::cout<<pxm<<"\n";
    return 0;
}
