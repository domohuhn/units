/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_INVOKE_IMPL_INCLUDED
#define DH_MPL_INVOKE_IMPL_INCLUDED

#include <cstdint>
#include "dh/mpl/comparisons.hpp"

namespace dh {
namespace mpl {

namespace detail {

template<typename list, typename func>
using invoke_helper_t = typename list::template then<func>;

template <bool b>
struct invoker {
    template<typename list, typename func, typename... rest>
    using type = typename invoker<is_less(1,sizeof...(rest))>::template type<dh::mpl::detail::invoke_helper_t<list,func> , rest...>;
};

template <>
struct invoker<false> {
    template<typename list, typename func>
    using type = dh::mpl::detail::invoke_helper_t<list,func>;
};

}
}
}

#endif /* DH_MPL_INVOKE_IMPL_INCLUDED */

