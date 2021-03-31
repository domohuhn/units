/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_INVOKE_INCLUDED
#define DH_MPL_INVOKE_INCLUDED

#include "dh/mpl/detail/invoke_impl.hpp"

namespace dh {
namespace mpl {

template<typename list, typename... funcs>
using invoke_t = typename detail::invoker<is_less(1,sizeof...(funcs))>::template type<list,funcs...>;

}
}

#endif /* DH_MPL_INVOKE_INCLUDED */

