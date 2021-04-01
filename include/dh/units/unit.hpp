/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_UNIT_INCLUDED
#define DH_UNITS_UNIT_INCLUDED

#include <cstdint>
#include <string>

namespace dh {
namespace units {

template<typename dimension, typename ratio, intmax_t power =1>
class unit {
public:
    using dimension_type = dimension;
    using prefix_type = typename ratio::type;
    static constexpr intmax_t power_value = power;
};


}
}

#endif /* DH_UNITS_UNIT_INCLUDED */
