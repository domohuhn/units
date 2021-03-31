
/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FUNCTORS_INCLUDED
#define DH_MPL_FUNCTORS_INCLUDED

#include <array>



namespace dh {
namespace mpl {

template<typename rep>
struct add {
    using value_type = rep;

    static constexpr value_type call(value_type a, value_type b) noexcept {
        return a+b;
    }
};

template<typename rep>
struct subtract {
    using value_type = rep;

    static constexpr value_type call(value_type a, value_type b) noexcept {
        return a-b;
    }
};

template<typename rep>
struct multiply {
    using value_type = rep;

    static constexpr value_type call(value_type a, value_type b) noexcept {
        return a*b;
    }
};


template<typename rep>
struct multiply_single_instance {
    using value_type = rep;

    // cannot be constexpr in c++11 :(
    template<typename... ARGS>
    std::array<value_type,sizeof...(ARGS)+1> call_impl(value_type i,ARGS... args){
        return {(i*=args)...};
    }

    // cannot be constexpr in c++11 :(
    template<typename... ARGS>
    value_type call(ARGS... args) {
        return sizeof...(ARGS) >= 2 ? call_impl(args...)[sizeof...(ARGS)-2] : call_impl_small(args...);
    }

    static constexpr value_type call_impl_small(value_type a, value_type b) noexcept {
        return a*b;
    }
    
    static constexpr value_type call_impl_small(value_type a) noexcept {
        return a;
    }
        
    static constexpr value_type call_impl_small() noexcept {
        return 1;
    }
};

template<typename rep>
struct logical_and {
    using value_type = rep;

    static constexpr value_type call(value_type a, value_type b) noexcept {
        return a&&b;
    }
};

template<typename rep>
struct logical_or {
    using value_type = rep;
    
    static constexpr value_type call(value_type a, value_type b) noexcept {
        return a||b;
    }
};

}
}

#endif /* DH_MPL_FUNCTORS_INCLUDED */
