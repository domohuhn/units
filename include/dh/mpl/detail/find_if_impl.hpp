/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_FIND_IF_INCLUDED
#define DH_MPL_DETAIL_FIND_IF_INCLUDED

#include "dh/mpl/conditional.hpp"
#include "dh/mpl/list.hpp"
#include "dh/mpl/comparisons.hpp"

namespace dh {
namespace mpl {

namespace detail {

template <class predicate, bool b>
struct find_if_impl {
    template<typename current, typename... pack>
    using type = typename conditional<predicate::template type<current>::value >:: template type < 
        list<current> , 
        typename find_if_impl< predicate, is_less(1,sizeof...(pack)) >::template type<pack...>
    >;
};
template <class predicate>
struct find_if_impl<predicate,false> {
    template<typename current>
    using type = typename conditional<predicate::template type<current>::value >:: template type < 
        list<current> , 
        list<>
    >;
};

}

}
}

#endif /* DH_MPL_DETAIL_FIND_IF_INCLUDED */
