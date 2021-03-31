/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FILTER_INCLUDED
#define DH_MPL_FILTER_INCLUDED

#include "dh/mpl/list.hpp"
#include "dh/mpl/conditional.hpp"
#include "dh/mpl/join.hpp"
#include "dh/mpl/transform.hpp"

namespace dh {
namespace mpl {

/** @brief Remove all elements for which the predicate does not hold true.
 * 
 * @note Since c++11 does not have variable templates, this filter cannot use a nested
 * value template. Instead, a class predicate with a nested type containing a value has to be provided as argument.
 */
template<class predicate>
struct filter {
    struct conditional_wrap {
        template<typename check>
        using type = typename conditional< predicate::template type<check>::value >::template type<list<check>,list<>>;
    };

    template<typename... pack>
    using type = typename transform<conditional_wrap>::template type<pack...>::template then<join>;

};

}
}

#endif /* DH_MPL_FILTER_INCLUDED */