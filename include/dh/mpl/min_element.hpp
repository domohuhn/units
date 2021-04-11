/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_MPL_MIN_ELEMENT_INCLUDED
#define DH_MPL_MIN_ELEMENT_INCLUDED

#include "dh/mpl/conditional.hpp"
#include "dh/mpl/accumulate.hpp"

namespace dh {
namespace mpl {

template<typename binary_predicate>
struct min_element
{
    struct binary_operation {
        template<typename lhs, typename rhs>
        using type = typename conditional<binary_predicate::template type<lhs,rhs>::value>::template type<lhs,rhs>;
    };

    template<typename... pack>
    using type = typename accumulate<binary_operation>::template type<pack...>;

};

}
}

#endif /* DH_MPL_MIN_ELEMENT_INCLUDED */
