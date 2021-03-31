/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_ACCUMULATE_INCLUDED
#define DH_MPL_ACCUMULATE_INCLUDED

#include "dh/mpl/conditional.hpp"
#include "dh/mpl/detail/accumulate_impl.hpp"

namespace dh {
namespace mpl {

template<typename binary_operation>
struct accumulate
{
   template<typename... pack>
   using type = typename detail::accumulate_type<binary_operation,detail::selectTypeAccumulation(sizeof...(pack))>::template type<pack...>;


    template<typename... pack>
    using value_wrapper = typename conditional< detail::can_accumulate_value<binary_operation>::value >::
        template type<detail::accumulate_value<binary_operation,pack...> , detail::no_accumulate_implementation>;

};

template<typename binary_operation>
struct accumulate_value
{
    template<typename... pack>
    using type = typename accumulate<binary_operation>::template value_wrapper<pack...>;

};

}
}

#endif /* DH_MPL_ACCUMULATE_INCLUDED */
