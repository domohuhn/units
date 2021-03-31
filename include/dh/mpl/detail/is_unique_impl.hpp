/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_IS_UNIQUE_INCLUDED
#define DH_MPL_DETAIL_IS_UNIQUE_INCLUDED

#include "dh/mpl/conditional.hpp"
#include "dh/mpl/list.hpp"
#include "dh/mpl/find_if.hpp"
#include "dh/mpl/bind.hpp"
#include "dh/mpl/comparisons.hpp"
#include <type_traits>

namespace dh {
namespace mpl {

namespace detail {


template <class predicate, bool b>
struct is_unique_impl {
    template<typename current, typename... pack>
    using type = typename conditional< 
        dh::mpl::find_if< bind<predicate,current> >::template type<pack...>::empty  
    >:: template type < 
        typename is_unique_impl< predicate, is_less(1,sizeof...(pack)) >::template type<pack...> ,
        std::false_type
    >;
};
template <class predicate>
struct is_unique_impl<predicate,false> {
    template<typename current>
    using type = std::true_type;
};

}

}
}

#endif /* DH_MPL_DETAIL_IS_UNIQUE_INCLUDED */
