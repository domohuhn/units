/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_VOID_INCLUDED
#define DH_MPL_VOID_INCLUDED

namespace dh {
namespace mpl {

template<typename... Ts> 
struct make_void { 
    using type = void;
};

template<typename... Ts> 
using void_t = typename make_void<Ts...>::type;

}
}

#endif /* DH_MPL_VOID_INCLUDED */
