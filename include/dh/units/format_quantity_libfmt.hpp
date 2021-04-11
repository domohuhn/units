/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED
#define DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED



#ifndef DH_UNITS_DISABLE_LIBFMT
#include <fmt/format.h>
#include "dh/units/format_quantity.hpp"

template <typename quantity>
struct fmt::formatter<quantity, typename std::enable_if<dh::units::is_dh_quantity<quantity>::value, char>::type> 
{
    std::string value_format;

    constexpr auto parse(format_parse_context& ctx)
    {
        value_format= "{:";        
        for (auto it= std::begin(ctx); it != std::end(ctx); ++it) {
            char c= *it;
            value_format+= c;
            if (c == '}')
                return it;
        }
        value_format+= "}";
        return std::end(ctx);
    }

  template <typename FormatContext>
  auto format(const quantity& q, FormatContext& ctx) {
    return format_to(
        ctx.out(),
        value_format+" {}",
        q.count(), dh::units::unit_list_to_string(typename quantity::original_unit_list{}));
  }
};



#endif /* DH_UNITS_DISABLE_LIBFMT */

#endif /* DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED */
