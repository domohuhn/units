#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#ifdef DH_UNITS_ENABLE_LIBFMT
#include <fmt/format.h>
#endif
#include <iosfwd>
#include <locale>
#include <ratio>
#include <string>
#include <type_traits>
/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_DECLARATION_MACROS_INCLUDED
#define DH_UNITS_DECLARATION_MACROS_INCLUDED

#define DH_DECLARE_QUANTITY( NAME, ... ) \
template <typename T = double> \
class NAME : public  \
::dh::units::quantity<T, __VA_ARGS__ > \
{ \
public: \
    using base_type = ::dh::units::quantity<T, __VA_ARGS__ >; \
    using base_type::base_type; \
    using value_type = T; \
    NAME(const base_type& q) : base_type(q) {} \
    NAME(base_type&& q) : base_type(std::move(q)) {} \
    NAME() = default; \
    NAME(const NAME&) = default; \
    NAME(NAME&&) = default; \
    NAME& operator=(const NAME&) = default; \
    NAME& operator=(NAME&&) = default; \
    ~NAME() = default; \
};

#define DH_DECLARE_UNITS_ALL_PREFIXES( PREFIX , NAME, DIMENSION, POW ) \
using unit_ ## PREFIX ## atto  ## NAME = dh::units::unit<DIMENSION, std::atto, POW >; \
using unit_ ## PREFIX ## femto ## NAME = dh::units::unit<DIMENSION, std::femto, POW >; \
using unit_ ## PREFIX ## pico  ## NAME = dh::units::unit<DIMENSION, std::pico, POW >; \
using unit_ ## PREFIX ## nano  ## NAME = dh::units::unit<DIMENSION, std::nano, POW >; \
using unit_ ## PREFIX ## micro ## NAME = dh::units::unit<DIMENSION, std::micro, POW >; \
using unit_ ## PREFIX ## milli ## NAME = dh::units::unit<DIMENSION, std::milli, POW >; \
using unit_ ## PREFIX ## centi ## NAME = dh::units::unit<DIMENSION, std::centi, POW >; \
using unit_ ## PREFIX ## deci  ## NAME = dh::units::unit<DIMENSION, std::deci, POW >; \
using unit_ ## PREFIX ##          NAME = dh::units::unit<DIMENSION, std::ratio<1,1>, POW >; \
using unit_ ## PREFIX ## deca  ## NAME = dh::units::unit<DIMENSION, std::deca, POW >; \
using unit_ ## PREFIX ## hecto ## NAME = dh::units::unit<DIMENSION, std::hecto, POW >; \
using unit_ ## PREFIX ## kilo  ## NAME = dh::units::unit<DIMENSION, std::kilo, POW >; \
using unit_ ## PREFIX ## mega  ## NAME = dh::units::unit<DIMENSION, std::mega, POW >; \
using unit_ ## PREFIX ## giga  ## NAME = dh::units::unit<DIMENSION, std::giga, POW >; \
using unit_ ## PREFIX ## tera  ## NAME = dh::units::unit<DIMENSION, std::tera, POW >; \
using unit_ ## PREFIX ## peta  ## NAME = dh::units::unit<DIMENSION, std::peta, POW >; \
using unit_ ## PREFIX ## exa   ## NAME = dh::units::unit<DIMENSION, std::exa, POW >;

#define DH_DECLARE_QUANTITY_ALL_PREFIXES( PREFIX , NAME, DIMENSION, POW ) \
DH_DECLARE_UNITS_ALL_PREFIXES( PREFIX , NAME, DIMENSION, POW ) \
DH_DECLARE_QUANTITY( PREFIX ## atto  ## NAME , unit_ ## PREFIX ## atto   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## femto ## NAME , unit_ ## PREFIX ## femto  ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## pico  ## NAME , unit_ ## PREFIX ## pico   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## nano  ## NAME , unit_ ## PREFIX ## nano   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## micro ## NAME , unit_ ## PREFIX ## micro  ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## milli ## NAME , unit_ ## PREFIX ## milli  ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## centi ## NAME , unit_ ## PREFIX ## centi  ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## deci  ## NAME , unit_ ## PREFIX ## deci   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ##          NAME , unit_ ## PREFIX           ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## deca  ## NAME , unit_ ## PREFIX ## deca   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## hecto ## NAME , unit_ ## PREFIX ## hecto  ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## kilo  ## NAME , unit_ ## PREFIX ## kilo   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## mega  ## NAME , unit_ ## PREFIX ## mega   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## giga  ## NAME , unit_ ## PREFIX ## giga   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## tera  ## NAME , unit_ ## PREFIX ## tera   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## peta  ## NAME , unit_ ## PREFIX ## peta   ## NAME ) \
DH_DECLARE_QUANTITY( PREFIX ## exa   ## NAME , unit_ ## PREFIX ## exa    ## NAME )

#define DH_DECLARE_DERIVED_DIMENSION( NAME , TEXT , ... ) \
struct derived_ ## NAME { \
    static std::string name() { \
        return TEXT ; \
    } \
    using unit_list = dh::mpl::list< __VA_ARGS__ >; \
};

#define DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( NAME , TEXT , ... ) \
DH_DECLARE_DERIVED_DIMENSION( NAME , TEXT , __VA_ARGS__ ) \
using unit_ ## NAME = dh::units::unit< derived_ ## NAME , std::ratio<1,1>, 1 >;

#define DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( NAME , TEXT , ... ) \
DH_DECLARE_DERIVED_DIMENSION( NAME , TEXT , __VA_ARGS__ ) \
using unit_nano  ## NAME = dh::units::unit< derived_ ## NAME , std::nano, 1 >; \
using unit_micro ## NAME = dh::units::unit< derived_ ## NAME , std::micro, 1 >; \
using unit_milli ## NAME = dh::units::unit< derived_ ## NAME , std::milli, 1 >; \
using unit_      ## NAME = dh::units::unit< derived_ ## NAME , std::ratio<1,1>, 1 >; \
using unit_kilo  ## NAME = dh::units::unit< derived_ ## NAME , std::kilo, 1 >; \
using unit_mega  ## NAME = dh::units::unit< derived_ ## NAME , std::mega, 1 >; \
using unit_giga  ## NAME = dh::units::unit< derived_ ## NAME , std::giga, 1 >; \
DH_DECLARE_QUANTITY( nano  ## NAME , unit_ ## nano   ## NAME ) \
DH_DECLARE_QUANTITY( micro ## NAME , unit_ ## micro  ## NAME ) \
DH_DECLARE_QUANTITY( milli ## NAME , unit_ ## milli  ## NAME ) \
DH_DECLARE_QUANTITY(          NAME , unit_           ## NAME ) \
DH_DECLARE_QUANTITY( kilo  ## NAME , unit_ ## kilo   ## NAME ) \
DH_DECLARE_QUANTITY( mega  ## NAME , unit_ ## mega   ## NAME ) \
DH_DECLARE_QUANTITY( giga  ## NAME , unit_ ## giga   ## NAME ) 

#endif /* DH_UNITS_DECLARATION_MACROS_INCLUDED */

/** @file
 * Contains the basic dimensions for the units. 
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_DIMENSIONS_INCLUDED
#define DH_UNITS_DIMENSIONS_INCLUDED

namespace dh {
namespace units {
namespace dimensions {

struct length {
    static std::string name() {
        return "m";
    }
};

struct time {
    static std::string name() {
        return "s";
    }
};

// basic unit in si is kilogram, but using gram fits better with the library implementation
struct mass {
    static std::string name() {
        return "g";
    }
};

struct electric_current {
    static std::string name() {
        return "A";
    }
};

struct thermodynamic_temperature {
    static std::string name() {
        return "K";
    }
};

struct amount_of_substance {
    static std::string name() {
        return "mol";
    }
};

struct luminous_intensity {
    static std::string name() {
        return "cd";
    }
};

// Non si basic units that should exist as well
struct angle {
    static std::string name() {
        return "rad";
    }
};

struct angle_degree {
    static std::string name() {
        return "°";
    }
};

struct degree_celsius {
    static std::string name() {
        return "°C";
    }
};

struct degree_fahrenheit {
    static std::string name() {
        return "°F";
    }
};

}
}
}

#endif /* DH_UNITS_DIMENSIONS_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_UNIT_INCLUDED
#define DH_UNITS_UNIT_INCLUDED

namespace dh {
namespace units {

template<typename dimension, typename ratio, intmax_t power =1>
class unit {
public:
    using dimension_type = dimension;
    using prefix_type = typename ratio::type;
    static constexpr intmax_t power_value = power;
};

}
}

#endif /* DH_UNITS_UNIT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_CONDITIONAL_INCLUDED
#define DH_MPL_CONDITIONAL_INCLUDED

namespace dh {
namespace mpl {

/** @brief Structure for conditionals.
 * The contained type is the first template value for true
 * and the second one if the conditional is false.
 */
template<bool b>
struct conditional {
    template<typename success, typename other>
    using type = success;
};

template<>
struct conditional<false> {
    template<typename success, typename other>
    using type = other;
};

}
}

#endif /* DH_MPL_CONDITIONAL_INCLUDED */

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_ACCUMULATE_DETAIL_INCLUDED
#define DH_MPL_ACCUMULATE_DETAIL_INCLUDED

namespace dh {
namespace mpl {

namespace detail {

constexpr size_t selectTypeAccumulation(size_t value) {
    return  value>8?3 :value>2?2 : value==2 ? 1 : 0;
}

template <class binary_operation, size_t b>
struct accumulate_type {
    template<typename t1,typename t2,typename t3,typename t4,typename t5,typename t6,typename t7,typename t8, typename... rest>
    using type = typename accumulate_type<binary_operation,selectTypeAccumulation( sizeof...(rest)+1)>:: template type
        <typename binary_operation::template type<
            typename binary_operation::template type<
                typename binary_operation::template type<
                    typename binary_operation::template type<
                        typename binary_operation::template type<
                            typename binary_operation::template type<
                                typename binary_operation::template type<t1,t2>,
                            t3>,
                        t4>,
                    t5>,
                t6>,
            t7>,
        t8>,
    rest...>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,2> {
    template<typename current,typename next, typename... rest>
    using type = typename accumulate_type<binary_operation,selectTypeAccumulation( sizeof...(rest)+1)>:: template type
        <typename binary_operation::template type<current,next>, rest...>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,1> {
    template<typename current,typename last>
    using type = typename binary_operation::template type<current,last>;
};

template <class binary_operation>
struct accumulate_type<binary_operation,0> {
    template<typename current>
    using type = current;
};

// value recursion

template<typename binary_operation, typename ... pack>
struct accumulate_value;

template<typename binary_operation, typename current>
struct accumulate_value<binary_operation,current> {
    constexpr static typename binary_operation::value_type value = current::value;
};

template<typename binary_operation, typename current, typename next>
struct accumulate_value<binary_operation,current,next> {
    constexpr static typename binary_operation::value_type 
    value = binary_operation::call(current::value, next::value);
};

template<typename binary_operation, typename current1, typename current2, typename current3>
struct accumulate_value<binary_operation,current1,current2,current3> {
    constexpr static typename binary_operation::value_type 
    value = binary_operation::call(current1::value, binary_operation::call(current2::value, current3::value ));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4>
struct accumulate_value<binary_operation,current1,current2,current3,current4> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,current4::value)));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4, typename... rest>
struct accumulate_value<binary_operation,current1,current2,current3,current4,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,current1,current2,current3,current4>::value , accumulate_value<binary_operation,rest...>::value );
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8>
struct accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,
                binary_operation::call(current4::value,
                    binary_operation::call(current5::value, 
                        binary_operation::call(current6::value, 
                            binary_operation::call(current7::value,current8::value)))))));
};

template<typename binary_operation, typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, typename... rest>
struct accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,current1,current2,current3,current4,current5,current6,current7,current8>::value , accumulate_value<binary_operation,rest...>::value );
};

template<typename binary_operation, 
 typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, 
 typename current9, typename current10, typename current11, typename current12,
 typename current13, typename current14, typename current15, typename current16>
struct accumulate_value<binary_operation,
  current1,current2,current3,current4,current5,current6,current7,current8,
  current9,current10,current11,current12,current13,current14,current15,current16> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(current1::value, 
        binary_operation::call(current2::value, 
            binary_operation::call(current3::value,
                binary_operation::call(current4::value,
                    binary_operation::call(current5::value, 
                        binary_operation::call(current6::value, 
                            binary_operation::call(current7::value,
                                binary_operation::call(current8::value, 
                                    binary_operation::call(current9::value, 
                                        binary_operation::call(current10::value,
                                            binary_operation::call(current11::value,
                                                binary_operation::call(current12::value, 
                                                    binary_operation::call(current13::value, 
                                                        binary_operation::call(current14::value,
                                                            binary_operation::call(current15::value,current16::value)))))))))))))));
};

template<typename binary_operation, 
 typename current1, typename current2, typename current3, typename current4,
 typename current5, typename current6, typename current7, typename current8, 
 typename current9, typename current10, typename current11, typename current12,
 typename current13, typename current14, typename current15, typename current16, typename... rest>
struct accumulate_value<binary_operation,
  current1,current2,current3,current4,current5,current6,current7,current8,
  current9,current10,current11,current12,current13,current14,current15,current16,rest...> {
    constexpr static typename binary_operation::value_type value = 
    binary_operation::call(accumulate_value<binary_operation,
            current1,current2,current3,current4,current5,current6,current7,current8,
            current9,current10,current11,current12,current13,current14,current15,current16>::value ,
        accumulate_value<binary_operation,rest...>::value );
};

struct no_accumulate_implementation {};

template <typename T, typename = void>
struct can_accumulate_value : std::false_type {};
template <typename T>
struct can_accumulate_value<T, 
    ::dh::mpl::void_t<typename T::value_type,
        decltype(T::call( std::declval<typename T::value_type>(), std::declval<typename T::value_type>() ))>>
    : std::true_type {};

}

}
}

#endif /* DH_MPL_ACCUMULATE_DETAIL_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_ACCUMULATE_INCLUDED
#define DH_MPL_ACCUMULATE_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_BIND_INCLUDED
#define DH_MPL_BIND_INCLUDED

namespace dh {
namespace mpl {

/** @brief Bind the args as the first arguments of functors type. */
template<class functor, typename... args>
struct bind {
    template<typename... pack>
    using type = typename functor::template type<args...,pack...>;
};

}
}

#endif /* DH_MPL_BIND_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_LIST_INCLUDED
#define DH_MPL_LIST_INCLUDED

namespace dh {
namespace mpl {
    
/** The list type used to transport the variadic template packs from one funciton to the next */
template<typename... pack>
struct list {
    template<typename next>
    using then = typename next::template type<pack...>;

    template<template<typename...> class wrapper, typename... firstargs>
    using wrap = wrapper<firstargs...,pack...>;
    
    static constexpr size_t size = sizeof...(pack);
    static constexpr bool empty = size==0;

    template<class next, typename... firstargs>
    using type = typename next::template type<firstargs...,pack...>;
};

template<typename functor,typename... pack>
auto call( mpl::list<pack...> ) -> typename std::decay<decltype(functor::call(pack::value...))>::type {
    return functor::call(pack::value...);
}

template<typename... pack>
constexpr size_t list<pack...>::size;

template<typename... pack>
constexpr bool list<pack...>::empty;

using empty_list = list<>;

}
}

#endif /* DH_MPL_LIST_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_WRAP_INCLUDED
#define DH_MPL_WRAP_INCLUDED

namespace dh {
namespace mpl {

/** @brief Wrapper for other templates. Can be used to wrap a template for usage with e.g. min element or to extract the list at the end.
 * 
 * @note is this is added with any other type than mpl::list, then the mpl sequence terminates.
 */
template<template<typename...> class container>
struct wrap {
    template<typename... pack>
    using type = container<pack...>;
};

}
}

#endif /* DH_MPL_WRAP_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_JOIN_INL_INCLUDED
#define DH_MPL_JOIN_INL_INCLUDED

namespace dh {
namespace mpl {

namespace detail {

template<bool b>
struct join {
    template<typename list, typename... args>
    using type = typename list::template type<args...,wrap<mpl::list>>;
};

template<>
struct join<false> {
    template<typename... pack>
    using type = list<>;
};

} /* namespace detail */

} /* namespace mpl */
} /* namespace dh */

#endif /* DH_MPL_JOIN_INL_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_COMPARISONS_INCLUDED
#define DH_MPL_COMPARISONS_INCLUDED

namespace dh {
namespace mpl {

// comparisons for use in template args

constexpr bool is_less(size_t a, size_t b) noexcept {
    return a<b;
}

constexpr bool is_greater(size_t a, size_t b) noexcept {
    return a>b;
}

template<typename T>
constexpr bool larger_than_one(T a) noexcept {
    return a>T(1);
}

}
}

#endif /* DH_MPL_COMPARISONS_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_JOIN_INCLUDED
#define DH_MPL_JOIN_INCLUDED

namespace dh {
namespace mpl {

/** @brief Joins the packs given in the lists provided as template arguments to a single list */
struct join {
    template<typename... pack>
    using type = typename detail::join<is_greater(sizeof...(pack),0)>::template type<pack...>;
};

}
}

#endif /* DH_MPL_JOIN_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_TRANSFORM_INCLUDED
#define DH_MPL_TRANSFORM_INCLUDED

namespace dh {
namespace mpl {

/** @brief Apply the contained type template from the functor to the template pack of the list. */
template<typename functor>  
struct transform {

    template<typename... pack>
    using type = dh::mpl::list< typename functor::template type<pack>... >;
    
    template<template<typename...> class wrapper, typename... pack>
    using wrap = wrapper< typename functor::template type<pack>... >;

};

}
}

#endif /* DH_MPL_TRANSFORM_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FILTER_INCLUDED
#define DH_MPL_FILTER_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_COUNT_IF_INCLUDED
#define DH_MPL_COUNT_IF_INCLUDED

namespace dh {
namespace mpl {

/** @brief Count the number of elements where the predicate is true. 
 * Result is stored in the static data member size.
 */
template<class predicate>
using count_if = filter<predicate>;

}
}

#endif /* DH_MPL_COUNT_IF_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_FIND_IF_INCLUDED
#define DH_MPL_DETAIL_FIND_IF_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FIND_IF_INCLUDED
#define DH_MPL_FIND_IF_INCLUDED

namespace dh {
namespace mpl {

/** @brief Find the first element for which the predicate is true.
 * 
 * @note Since c++11 does not have variable templates, this filter cannot use a nested
 * value template. Instead, a class predicate with a nested type containing a value has to be provided as argument.
 */
template<class predicate>
struct find_if {
    template<typename... pack>
    using type = typename detail::find_if_impl<predicate, is_less(1,sizeof...(pack)) >::template type<pack...>;
};

}
}

#endif /* DH_MPL_FIND_IF_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FRONT_INCLUDED
#define DH_MPL_FRONT_INCLUDED

namespace dh {
namespace mpl {

/** @brief Get the first element of the template list.
 * Compilation will only work if there is an element.
 */
struct front {
    template<typename first, typename... pack>
    using type = first;
};

template<typename in>
using front_t = typename in::template then<front>;

}
}

#endif /* DH_MPL_FRONT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_FUNCTORS_INCLUDED
#define DH_MPL_FUNCTORS_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_INVOKE_IMPL_INCLUDED
#define DH_MPL_INVOKE_IMPL_INCLUDED

namespace dh {
namespace mpl {

namespace detail {

template<typename list, typename func>
using invoke_helper_t = typename list::template then<func>;

#if !defined(_MSC_VER) && !defined(__clang__)
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

#else

// visual studio workaround 
template <typename... >
struct invoker;

template <typename list, typename func, typename... rest>
struct invoker<list,func,rest...>{
     using type = typename invoker<dh::mpl::detail::invoke_helper_t<list,func> , rest...>::type;
};

template <typename list, typename func>
struct invoker<list,func> {
    using type = dh::mpl::detail::invoke_helper_t<list,func>;
};

#endif

}
}
}

#endif /* DH_MPL_INVOKE_IMPL_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_INVOKE_INCLUDED
#define DH_MPL_INVOKE_INCLUDED

namespace dh {
namespace mpl {

#if !defined(_MSC_VER) && !defined(__clang__)
template<typename list, typename... funcs>
using invoke_t = typename detail::invoker<is_less(1,sizeof...(funcs))>::template type<list,funcs...>;

#else
// visual studio workaround
template<typename... funcs>
using invoke_t = typename detail::invoker<funcs...>::type;
#endif

}
}

#endif /* DH_MPL_INVOKE_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_IS_UNIQUE_INCLUDED
#define DH_MPL_DETAIL_IS_UNIQUE_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_IS_UNIQUE_INCLUDED
#define DH_MPL_IS_UNIQUE_INCLUDED

namespace dh {
namespace mpl {

/** @brief Check if the binary predicate holds true if applied to any pair of arguments.
 * Instantiates O(n) types for the predicate and does O(n^2) comparisions. 
 * @return Contains either std::true_type or std::false_type
 **/
template<class binary_predicate>
struct is_unique {

    template<typename... pack>
    using type = typename detail::is_unique_impl<binary_predicate, is_less(1,sizeof...(pack)) >::template type<pack...>;
};

}
}

#endif /* DH_MPL_IS_UNIQUE_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_MIN_ELEMENT_INCLUDED
#define DH_MPL_MIN_ELEMENT_INCLUDED

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

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_DETAIL_POP_FRONT_INCLUDED
#define DH_MPL_DETAIL_POP_FRONT_INCLUDED

namespace dh {
namespace mpl {
namespace detail {

template<bool b>
struct pop_front_impl {
    template<template <typename...> class container, typename first ,typename... pack>
    using type = container<pack...>;
};

template<>
struct pop_front_impl<false> {
    template<template <typename...> class container>
    using type = container<>;
};

}
}
}

#endif /* DH_MPL_DETAIL_POP_FRONT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_POP_FRONT_INCLUDED
#define DH_MPL_POP_FRONT_INCLUDED

namespace dh {
namespace mpl {

/** @brief Remove first element of list, then wrap into container.
 */
template<template <typename...> class container = dh::mpl::list >
struct pop_front {

    template<typename... pack>
    using type = typename detail::pop_front_impl< is_greater(sizeof...(pack),0) >::template type<container,pack...>;
};

}
}

#endif /* DH_MPL_POP_FRONT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_PUSH_BACK_INCLUDED
#define DH_MPL_PUSH_BACK_INCLUDED

namespace dh {
namespace mpl {

/** @brief Add an element at the end of list, then wrap list into container.
 */
template<typename to_add, template <typename...> class container = dh::mpl::list >
struct push_back {
    template<typename... pack>
    using type = container< pack... , to_add >;
};

}
}

#endif /* DH_MPL_PUSH_BACK_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_PUSH_FRONT_INCLUDED
#define DH_MPL_PUSH_FRONT_INCLUDED

namespace dh {
namespace mpl {

/** @brief Add element in front of list
 */
template<typename to_add, template <typename...> class container = dh::mpl::list >
struct push_front {
    template<typename... pack>
    using type = container< to_add, pack... >;
};

}
}

#endif /* DH_MPL_PUSH_FRONT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_UNWRAP_INCLUDED
#define DH_MPL_UNWRAP_INCLUDED

namespace dh {
namespace mpl {

/** Unwrap a template pack and put it in a continuation. Can only be nested once! */
template<typename T>
struct unwrap;

template<template<typename...> class container, typename... pack>
struct unwrap<container<pack...>> {
    template<typename next>
    using then = typename next::template type<pack...>;
};

}
}

#endif /* DH_MPL_UNWRAP_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_MPL_CORE_INCLUDED
#define DH_MPL_CORE_INCLUDED

#endif /* DH_MPL_CORE_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_TRAITS_INCLUDED
#define DH_UNITS_TRAITS_INCLUDED

namespace dh {
namespace units {

namespace mpl = ::dh::mpl;

template<typename U1, typename U2>
struct units_have_same_dimension_and_power {
    using type =  typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;
    constexpr static bool value = type::value && U1::power_value == U2::power_value;
};

template<typename U1, typename U2>
using units_have_same_dimension =  typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;

template<typename L1, typename L2>
struct lists_contain_same_dimensions {
    static constexpr bool value = false;
};

template<typename... pack1, typename... pack2>
struct lists_contain_same_dimensions<mpl::list<pack1...>, mpl::list<pack2...>> 
{
    static constexpr bool checkPackSizes() {
        return sizeof...(pack1) == sizeof...(pack2) && sizeof...(pack1)>0;
    }

    using combined_list = typename mpl::conditional<checkPackSizes()>::template type<
        mpl::invoke_t<mpl::list< typename mpl::find_if< mpl::bind<mpl::wrap<units_have_same_dimension_and_power> ,pack1> >:: template type<pack2...>... > ,
                        mpl::join>, mpl::list<>>;
    static constexpr bool value = sizeof...(pack1) == sizeof...(pack2) && combined_list::size == sizeof...(pack1);
};

template<typename... pack1>
struct lists_contain_same_dimensions<mpl::list<pack1...>, mpl::list<>> 
{
    static constexpr bool value = false;
};

template<typename... pack1>
struct lists_contain_same_dimensions<mpl::list<>, mpl::list<pack1...>> 
{
    static constexpr bool value = false;
};

template<>
struct lists_contain_same_dimensions<mpl::list<>, mpl::list<>> 
{
    static constexpr bool value = true;
};

template<typename L1, typename L2>
constexpr bool lists_contain_same_dimensions<L1,L2>::value;

template<typename... pack1,typename... pack2>
constexpr bool lists_contain_same_dimensions<mpl::list<pack1...>, mpl::list<pack2...>>::value;

template<typename L1, typename L2>
struct lists_contain_same_types {
    static constexpr bool value = false;
};

template<typename... pack1, typename... pack2>
struct lists_contain_same_types<dh::mpl::list<pack1...>, dh::mpl::list<pack2...>> 
{
    using combined_list = mpl::invoke_t<
        mpl::list< typename mpl::find_if< mpl::bind<mpl::wrap<std::is_same> ,pack1> >:: template type<pack2...>... > ,
        mpl::join>;

    static constexpr bool value = sizeof...(pack1) == sizeof...(pack2) && combined_list::size == sizeof...(pack1);
};

template<typename L1, typename L2>
constexpr bool lists_contain_same_types<L1,L2>::value;

template<typename... pack1,typename... pack2>
constexpr bool lists_contain_same_types<mpl::list<pack1...>, mpl::list<pack2...>>::value;

template <typename T, typename = void>
struct is_dh_quantity : std::false_type {};
template <typename T>
struct is_dh_quantity<T, dh::mpl::void_t<typename T::value_type,
    typename T::quantity_type, typename T::unit_list, decltype(std::declval<T>().count()) >>
    : std::true_type {};

template <typename T, typename = void>
struct is_dh_unit : std::false_type {};
template <typename T>
struct is_dh_unit<T, dh::mpl::void_t<typename T::dimension_type,
    typename T::prefix_type, decltype(std::declval<intmax_t>() == T::power_value) >>
    : std::true_type {};

template <typename T, typename = void>
struct is_derived_unit : std::false_type {
    using unit_list = mpl::list<T>;
};

template<typename Ratio>
struct multiply_first_prefix_in_list {
    template<typename first, typename... rest>
    using type = mpl::list< unit<typename first::dimension_type, std::ratio_multiply<Ratio, typename first::prefix_type>  ,first::power_value>, rest...>;
};

template <typename T>
struct is_derived_unit<T, dh::mpl::void_t<typename T::dimension_type::unit_list> >
{
    constexpr static bool value = is_dh_unit<T>::value && !T::dimension_type::unit_list::empty;
    static_assert( T::power_value == 1 ,"Derived units cannot have a power different than 1!");
    static_assert( mpl::invoke_t<typename T::dimension_type::unit_list,mpl::front>::power_value == 1 ,"The power of the first unit in a derived list has to be 1!");
    using unit_list = mpl::invoke_t<typename T::dimension_type::unit_list, multiply_first_prefix_in_list<typename T::prefix_type> >;
};

template<typename U1, typename U2>
struct units_have_same_dimension_and_different_prefixes {
    using type1 =  typename std::is_same<typename U1::dimension_type, typename U2::dimension_type>::type;
    using type2 =  typename std::is_same<typename U1::prefix_type, typename U2::prefix_type>::type;
    constexpr static bool value = type1::value && !type2::value;
};

template <typename T,typename Unit, typename = void>
struct quantity_convertible_to_unit : std::false_type {};
template <typename T,typename Unit>
struct quantity_convertible_to_unit<T,Unit, dh::mpl::void_t<typename T::value_type,
    typename T::quantity_type, typename T::unit_list, decltype(std::declval<T>().count())> >
{
    constexpr static bool value = lists_contain_same_dimensions< typename T::unit_list, dh::mpl::list<Unit>>::value;
};

template<typename ratio, typename U1>
struct unit_power_is_divisible {
    constexpr static bool value = ((U1::power_value * ratio::num) % ratio::den)==0;
};

template <typename quantity, typename ratio >
struct quantity_is_exponentiable
{
    constexpr static bool value =  mpl::invoke_t< typename quantity::unit_list, 
        mpl::transform<mpl::bind<mpl::wrap<unit_power_is_divisible>,ratio> >,
        mpl::accumulate_value<mpl::logical_and<bool>>
        >::value;
};

}
}

#endif /* DH_UNITS_TRAITS_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_CONVERSION_INCLUDED
#define DH_UNITS_QUANTITY_CONVERSION_INCLUDED

namespace dh {
namespace units {

namespace mpl = ::dh::mpl;

template<typename REP, typename RATIO_TO, typename RATIO_FROM>
constexpr REP ratio_conversion_factor() noexcept {
    return ((REP)(RATIO_FROM::num)*(REP)(RATIO_TO::den))/((REP)(RATIO_TO::num)*(REP)(RATIO_FROM::den));
}

template<typename REP, intmax_t POWER , typename RATIO_TO, typename RATIO_FROM>
struct conversion_factor_holder_type {

    static constexpr REP conversion_factor_power(intmax_t index) {
        return index>0 ? ratio_conversion_factor<REP,RATIO_TO,RATIO_FROM>()*conversion_factor_power(index-1) : 
        (index<0? ratio_conversion_factor<REP,RATIO_FROM,RATIO_TO>()*conversion_factor_power(index+1) : 1);
    };

    static constexpr REP value = conversion_factor_power(POWER);
};

template<typename REP, typename UNIT_TO>
struct compute_conversion_factor {
    template<typename UNIT_FROM>
    using type = typename mpl::conditional< units_have_same_dimension_and_power<UNIT_TO,UNIT_FROM>::value >::template type<
        conversion_factor_holder_type<REP, UNIT_TO::power_value ,typename UNIT_TO::prefix_type ,typename UNIT_FROM::prefix_type>,
        conversion_factor_holder_type<REP,0,std::ratio<1,1>,std::ratio<1,1> > >;
};

template<typename REP, typename LIST_TO,  typename LIST_FROM>
struct unit_list_conversion_factor;

template<typename REP, typename... pack, typename LIST_FROM>
struct unit_list_conversion_factor<REP,mpl::list<pack...>, LIST_FROM > {
    using factor_list = mpl::list< typename LIST_FROM::template then< mpl::transform< compute_conversion_factor<REP,pack> > >::template then< mpl::accumulate_value<mpl::multiply<REP>> >... >;

    static constexpr bool needsComputation() noexcept {
        return !LIST_FROM::empty && sizeof...(pack)>0 && !std::is_same< mpl::list<pack...>, LIST_FROM>::value;
    }

    static constexpr REP value = mpl::conditional<needsComputation()>::template type<
     mpl::invoke_t<factor_list , mpl::accumulate_value<mpl::multiply<REP>> >,
     unit_list_conversion_factor<REP, mpl::empty_list,  mpl::empty_list> >::value;
};

template<typename REP>
struct unit_list_conversion_factor<REP, mpl::empty_list,  mpl::empty_list > {
    static constexpr REP value = static_cast<REP>(1);
};

template<typename REP, typename... pack, typename LIST_FROM> 
constexpr REP unit_list_conversion_factor<REP,mpl::list<pack...>,LIST_FROM>::value;

template<typename REP> 
constexpr REP unit_list_conversion_factor<REP,mpl::empty_list, mpl::empty_list>::value;

struct unit_has_higher_accuracy {
    template<typename current,typename other>
    using use_more_accurate_prefix_t = typename mpl::conditional<std::ratio_less<typename current::prefix_type, typename other::prefix_type>::value>::template type<
        current,dh::units::unit<typename current::dimension_type ,typename other::prefix_type ,current::power_value>
        >;

    template<typename minimum, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<minimum,compare>::value >::template type<
        use_more_accurate_prefix_t<minimum,compare>,
        minimum>;
};

struct select_highest_accuracy_for_first_dimension_in_list {
    template<typename... pack>
    using type = mpl::invoke_t<mpl::list<pack...>, mpl::accumulate<unit_has_higher_accuracy>>;
};

template<typename l1,typename l2>
struct combine_unit_lists_selecting_higher_accuracy;

template<typename... pack1,typename... pack2>
struct combine_unit_lists_selecting_higher_accuracy<mpl::list<pack1...>,mpl::list<pack2...>> {
    
    using unit_list = mpl::list< typename select_highest_accuracy_for_first_dimension_in_list::template type<pack1,pack2...>... >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;
};

template <typename UnitTo,typename UnitFrom, typename = void>
struct quantity_conversion_is_lossless : std::false_type {};

template <typename UnitTo,typename UnitFrom>
struct quantity_conversion_is_lossless<UnitTo,UnitFrom, typename std::enable_if< is_dh_quantity<UnitTo>::value && is_dh_quantity<UnitFrom>::value >::type >
{
    constexpr static bool value = 
    unit_list_conversion_factor<typename UnitTo::value_type,typename UnitTo::unit_list, typename UnitFrom::unit_list>::value >= 1 ||
    std::is_floating_point<typename std::decay<UnitTo>::type::value_type>::value;
};

// ===========================================================================================================================

template<typename operation>
struct combine_unit_power {
    template<typename Unit1, typename Unit2>
    using type = unit<typename Unit1::dimension_type, 
        typename mpl::conditional< std::ratio_less<typename Unit1::prefix_type, typename Unit2::prefix_type >::value  >::
            template type< typename Unit1::prefix_type, typename Unit2::prefix_type  > ,
        operation::call(Unit1::power_value,Unit2::power_value)>;
};

template<typename operation>
struct unit_accumulator {
    template< typename combined, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<combined,compare>::value >::
        template type < typename combine_unit_power<operation>::template type<combined,compare> , combined >;
};

struct unit_accumulator_backpropagate {

    template<typename other>
    using set_power_to_zero = unit<typename other::dimension_type,std::ratio<1,1>,0>;

    template< typename combined, typename compare>
    using type = typename mpl::conditional< units_have_same_dimension<combined,compare>::value >::
        template type < set_power_to_zero<combined> , combined >;
};

struct unit_power_not_zero {
    template< typename unit >
    using type =  typename mpl::conditional< unit::power_value!=0 >:: template type< std::true_type , std::false_type >;
};

template<typename l1,typename l2>
struct multiplication_result;

template<typename... pack1,typename... pack2>
struct multiplication_result <mpl::list<pack1...>,mpl::list<pack2...>> {

    using unfiltered_list = mpl::list<typename mpl::accumulate<unit_accumulator<mpl::add<intmax_t>>>::template type<pack1,pack2...>...,
        typename mpl::accumulate<unit_accumulator_backpropagate>::template type<pack2,pack1...>...>;

    using unit_list = mpl::invoke_t<unfiltered_list, mpl::filter<unit_power_not_zero> >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;

};

template<typename l1,typename l2>
struct division_result;

template<typename... pack1,typename... pack2>
struct division_result <mpl::list<pack1...>,mpl::list<pack2...>> {

    template<typename other>
    using invert_power = unit<typename other::dimension_type,typename other::prefix_type, -other::power_value >;

    using unfiltered_list = mpl::list<typename mpl::accumulate<unit_accumulator<mpl::subtract<intmax_t>>>::template type<pack1,pack2...>...,
        invert_power<typename mpl::accumulate<unit_accumulator_backpropagate>::template type<pack2,pack1...>>...>;

    using unit_list = mpl::invoke_t<unfiltered_list, mpl::filter<unit_power_not_zero> >;

    template<template<typename...> class container,typename first>
    using type = mpl::invoke_t<unit_list,mpl::push_front<first,container>>;

};

template<typename RV,typename... UNITS1,typename... UNITS2>
constexpr RV compute_multiply_conversion_factor(const mpl::list<UNITS1...>& /*a*/,const mpl::list<UNITS2...>& /*b*/) 
{
    return unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS1,UNITS2...>...>,
        mpl::list<UNITS1...>>::value *
    unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS2,UNITS1...>...>,
        mpl::list<UNITS2...>>::value;
}

template<typename RV,typename... UNITS1,typename... UNITS2>
constexpr RV compute_division_conversion_factor(const mpl::list<UNITS1...>& /*a*/,const mpl::list<UNITS2...>& /*b*/) 
{
    return unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS1,UNITS2...>...>,
        mpl::list<UNITS1...>>::value /
    unit_list_conversion_factor<RV,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<UNITS2,UNITS1...>...>,
        mpl::list<UNITS2...>>::value;
}

template<typename Scalar, typename Quantity>
using common_value_type_t = typename std::common_type<Scalar, typename Quantity::value_type>::type;

template<typename LHS, typename RHS>
using common_quantity_representation_t =  typename std::common_type<typename LHS::value_type, typename RHS::value_type>::type;

template<typename LHS, typename RHS>
using can_be_added_t = typename std::enable_if< 
            is_dh_quantity<LHS>::value &&
            is_dh_quantity<RHS>::value &&
            lists_contain_same_dimensions<typename LHS::unit_list, typename RHS::unit_list>::value 
        >::type;

template <typename unit>
using contained_unit_list_t = typename is_derived_unit<unit>::unit_list;

template<typename l1,typename l2>
struct multiplication_result_assert_same_prefixes;

template<typename... pack1,typename... pack2>
struct multiplication_result_assert_same_prefixes <mpl::list<pack1...>,mpl::list<pack2...>> {
    using check = mpl::invoke_t< 
        mpl::list< mpl::invoke_t<mpl::list<pack2...>,
            mpl::find_if<mpl::bind< mpl::wrap<units_have_same_dimension_and_different_prefixes>,pack1>> >... 
        >,
        mpl::join>;
    static_assert( check::empty , "A list of units for a quantity cannot have the same unit with different prefixes! Check derived units!");
    using type = typename multiplication_result<mpl::list<pack1...>,mpl::list<pack2...>>::unit_list;
};

struct unit_extraction_accumulator {
    template< typename accumulated, typename current>
    using type = typename multiplication_result_assert_same_prefixes<accumulated,current>::type;
};

template<bool b>
struct extract_base_units_impl {
    template <typename... pack>
    using type = mpl::invoke_t<mpl::list< contained_unit_list_t<pack>...  >,mpl::accumulate<unit_extraction_accumulator>>;
};

template<>
struct extract_base_units_impl<false> {
    template <typename... pack>
    using type = mpl::list<>;
};

template <typename... pack>
using extract_base_units_t = typename extract_base_units_impl<mpl::is_greater(sizeof...(pack),0)>::template type<pack...>;

template<typename ratio>
struct modifiy_unit_power {
    template<typename Unit>
    using type = unit<typename Unit::dimension_type, 
        typename Unit::prefix_type,
        Unit::power_value*ratio::num/ratio::den>;
};

struct exponentiation_result {

    template<typename unit_list, typename ratio>
    using transformed_list = mpl::invoke_t<unit_list, mpl::transform<modifiy_unit_power<ratio>> >;

    template<template<typename...> class container,typename first,typename unit_list, typename ratio>
    using type = mpl::invoke_t<transformed_list<unit_list,ratio>,mpl::push_front<first,container>>;

};

}
}

#endif /* DH_UNITS_QUANTITY_CONVERSION_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_INCLUDED
#define DH_UNITS_QUANTITY_INCLUDED

namespace dh {
namespace units {

template<typename REP, typename... UNITS>
class quantity {
public:
    using value_type = REP;

    using quantity_type = quantity;
    
    using original_unit_list = mpl::list<UNITS...>;
    
    using unit_list = extract_base_units_t<UNITS...>;

    template<typename,typename...> friend class quantity;

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity(const other& in) : 
    value_{in.count() * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value} 
    {
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity(other&& in) : 
    value_{std::move(in.value_) * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value} 
    {
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity& operator=(const other& in) {
        value_ = in.count() * unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity_type,other>::value>::type >
    quantity& operator=(other&& in) {
        value_ = std::move(in.value_);
        value_ *= unit_list_conversion_factor<REP,unit_list, typename other::unit_list>::value;
        return *this;
    }

    template<typename REP2,
        typename = typename std::enable_if< std::is_arithmetic<REP2>::value >::type >
    quantity& operator*=(const REP2& in) {
        value_ *= in;
        return *this;
    }

    template<typename REP2,
        typename = typename std::enable_if< std::is_arithmetic<REP2>::value >::type >
    quantity& operator/=(const REP2& in) {
        value_ /= in;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity<REP,UNITS...>,other>::value>::type >
    quantity& operator+=(const other& in) {
        value_ += in.count()* unit_list_conversion_factor<REP,unit_list, typename other::unit_list >::value;
        return *this;
    }

    template<typename other, typename = typename std::enable_if< is_dh_quantity<other>::value 
            && lists_contain_same_dimensions<unit_list, typename other::unit_list>::value
            && quantity_conversion_is_lossless<quantity<REP,UNITS...>,other>::value>::type >
    quantity& operator-=(const other& in) {
        value_ -= in.count()* unit_list_conversion_factor<REP,unit_list, typename other::unit_list >::value;
        return *this;
    }

    explicit constexpr quantity(const REP& in) : value_{in} 
    {}

    explicit constexpr quantity(REP&& in) : value_{std::move(in)} 
    {}

    constexpr quantity()
    {}

    REP& count() {
        return value_;
    }

    const REP& count() const {
        return value_;
    }

    template<typename A, typename = typename std::enable_if<std::is_convertible<REP,A>::value>::type>
    explicit operator A() const {
        return value_;
    }

private:
    REP value_{};
};

// Add/subtract two quantities

template<typename Scalar, typename Quantity>
using promote_quantity_t = typename mpl::conditional< std::is_same<typename Quantity::value_type, common_value_type_t<Scalar,Quantity> >::value >:: template type<
    Quantity,
    typename Quantity::unit_list:: template wrap< ::dh::units::quantity , common_value_type_t<Scalar,Quantity> >>;

template<typename LHS, typename RHS>
using addition_return_t = typename mpl::conditional< 
        mpl::larger_than_one( unit_list_conversion_factor<common_quantity_representation_t<LHS,RHS>, typename LHS::unit_list, typename RHS::unit_list>::value ) >::
        template type<
            promote_quantity_t<common_quantity_representation_t<LHS,RHS> ,LHS>,
            promote_quantity_t<common_quantity_representation_t<LHS,RHS> ,RHS>
        >;

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
auto operator+ (const LHS& a, const RHS& b ) 
-> addition_return_t<LHS,RHS>
{
    addition_return_t<LHS,RHS> a_conv(a);
    a_conv += b;
    return a_conv;
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
auto operator- (const LHS& a, const RHS& b ) 
-> addition_return_t<LHS,RHS>
{
    addition_return_t<LHS,RHS> a_conv(a);
    a_conv -= b;
    return a_conv;
}

// multiply by scalar
template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator* (const Scalar& a, const T& b ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(a*b.count());
}

template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator* ( const T& b, const Scalar& a ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(a*b.count());
}

// division with scalar
template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator/ ( const T& b, const Scalar& a ) 
-> promote_quantity_t<Scalar,T> {
    return promote_quantity_t<Scalar,T>(b.count()/a);
}

template<typename Scalar,typename T, typename = typename std::enable_if<std::is_arithmetic<Scalar>::value && is_dh_quantity<T>::value>::type >
auto operator/ (const Scalar& a, const T& b ) 
-> typename std::decay<decltype(std::declval<::dh::units::quantity<Scalar>>()/std::declval<T>())>::type {
    return ::dh::units::quantity<Scalar>(a)/b;
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T operator-(const T &a) {
    return  T{-a.count()};
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T operator+(const T &a) {
    return a;
}

// multiply two quantities

template<typename LHS, typename RHS>
using multiplication_result_t = typename multiplication_result<typename LHS::unit_list,typename RHS::unit_list>::
    template type<dh::units::quantity,typename std::common_type<typename LHS::value_type,typename RHS::value_type>::type>;

template<typename LHS, typename RHS>
using division_result_t = typename division_result<typename LHS::unit_list,typename RHS::unit_list>::
    template type<dh::units::quantity,typename std::common_type<typename LHS::value_type,typename RHS::value_type>::type>;

template<typename LHS, typename RHS, typename = typename std::enable_if<is_dh_quantity<LHS>::value && is_dh_quantity<RHS>::value>::type >
auto operator* (const LHS& a, const RHS& b ) 
-> multiplication_result_t<LHS,RHS> {
    using rv_t = multiplication_result_t<LHS,RHS>;
    const auto factor = compute_multiply_conversion_factor<typename rv_t::value_type>(typename LHS::unit_list{},typename RHS::unit_list{});
    return rv_t{factor*a.count()*b.count()};
}

template<typename LHS, typename RHS, typename = typename std::enable_if<is_dh_quantity<LHS>::value && is_dh_quantity<RHS>::value>::type >
auto operator/ (const LHS& a, const RHS& b ) 
-> division_result_t<LHS,RHS> {
    using rv_t = division_result_t<LHS,RHS>;
    const auto factor = compute_division_conversion_factor<typename rv_t::value_type>(typename LHS::unit_list{},typename RHS::unit_list{});
    return rv_t{factor*a.count()/b.count()};
}

// integration with std::chrono
// mult

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator* (const std::chrono::duration<REP1,RATIO>& a, const Quantity& b ) 
-> multiplication_result_t<quantity<REP1,unit<dimensions::time,RATIO,1>>,Quantity > {
    return quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count())*b;
}

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator* (const Quantity& b, const std::chrono::duration<REP1,RATIO>& a ) 
-> multiplication_result_t<quantity<REP1,unit<dimensions::time,RATIO,1>>,Quantity > {
    return quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count())*b;
}

// division 

template<typename REP1,typename RATIO,typename Quantity, typename = typename std::enable_if<is_dh_quantity<Quantity>::value >::type >
auto operator/ (const Quantity& b, const std::chrono::duration<REP1,RATIO>& a ) 
-> division_result_t<Quantity,quantity<REP1,unit<dimensions::time,RATIO,1>> > {
    return b/quantity<REP1,unit<dimensions::time,RATIO,1>>(a.count());
}

// add

template <typename T, typename = void>
struct is_time_quantity : std::false_type {};
template <typename T>
struct is_time_quantity<T, dh::mpl::void_t<typename T::value_type,
    typename T::quantity_type, typename T::unit_list, decltype(std::declval<T>().count()) >>
{
    using time_type = dh::units::unit<dimensions::time,std::ratio<1,1>,1>;
    constexpr static bool value = lists_contain_same_dimensions<dh::mpl::list< time_type >, typename T::unit_list>::value;
};

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator+ (const std::chrono::duration<REP,RATIO>& a, const T& b ) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())+b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator+ (const T& b, const std::chrono::duration<REP,RATIO>& a) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())+b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator- (const std::chrono::duration<REP,RATIO>& a, const T& b ) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return quantity<REP,unit<dimensions::time,RATIO,1>>(a.count())-b;
}

template<typename REP,typename RATIO,typename T, typename = typename std::enable_if<std::is_arithmetic<REP>::value && is_time_quantity<T>::value>::type>
auto operator- (const T& b, const std::chrono::duration<REP,RATIO>& a) 
-> addition_return_t<quantity<REP,unit<dimensions::time,RATIO,1> >, T >
{
    return b-quantity<REP,unit<dimensions::time,RATIO,1>>(a.count());
}

// comparisons
// hoping that the compiler will remove useless conversions

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator ==(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() == b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator !=(const LHS &a, const RHS &b) {
    return !(a == b);
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator <(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() < b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator >(const LHS &a, const RHS &b) {
    return b<a;
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator <=(const LHS &a, const RHS &b) {
    const addition_return_t<LHS,RHS> a_conv(a);
    const addition_return_t<LHS,RHS> b_conv(b);
    return a_conv.count() <= b_conv.count();
}

template<typename LHS, typename RHS, typename = can_be_added_t<LHS,RHS> >
bool operator >=(const LHS &a, const RHS &b) {
    return b <= a;
}

template <typename T = double>
class scalar : public
::dh::units::quantity<T>
{
public:
    using base_type = ::dh::units::quantity<T>;
    using base_type::base_type;
    using value_type = T;
    scalar(const base_type& q) : base_type(q) {}
    scalar(base_type&& q) : base_type(std::move(q)) {}
    scalar() = default;
    scalar(const scalar&) = default;
    scalar(scalar&&) = default;
    scalar& operator=(const scalar&) = default;
    scalar& operator=(scalar&&) = default;
    ~scalar() = default;

    operator T() const {
        return this->count();
    }
};

}
}

#endif /* DH_UNITS_QUANTITY_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_SI_UNIT_INCLUDED
#define DH_UNITS_SI_UNIT_INCLUDED

namespace si {

template<typename T>
using scalar = ::dh::units::scalar<T>;

DH_DECLARE_QUANTITY_ALL_PREFIXES( , meter , dh::units::dimensions::length , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( square_ , meter , dh::units::dimensions::length , 2)
DH_DECLARE_QUANTITY_ALL_PREFIXES( cubic_ , meter , dh::units::dimensions::length , 3)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , second , dh::units::dimensions::time , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , kelvin , dh::units::dimensions::thermodynamic_temperature , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , gram , dh::units::dimensions::mass , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , ampere , dh::units::dimensions::electric_current , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , mol , dh::units::dimensions::amount_of_substance , 1)
DH_DECLARE_QUANTITY_ALL_PREFIXES( , candela , dh::units::dimensions::luminous_intensity , 1)

using ratio_minute = std::ratio<60,1>;
using ratio_hour = std::ratio<3600,1>;
using ratio_day = std::ratio<86400,1>;
using ratio_week = std::ratio<604800,1>;
using ratio_month = std::ratio<2629800,1>;
using ratio_year = std::ratio<31557600,1>; // julian year
using ratio_astronomical_unit = std::ratio<149597870700,1>;
using ratio_lightyear = std::ratio<9460730472580800,1>;
using ratio_speed_of_light = std::ratio<299792458,1>;

using ratio_radian = std::ratio<5729577951308232087,100000000000000000>;

using ratio_degree = std::ratio<1,1>;
using ratio_arcmin = std::ratio<1,60>;
using ratio_arcsec = std::ratio<1,3600>;
using ratio_milliarcsec = std::ratio<1,3600000>;

using unit_per_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -1 >;
using unit_per_square_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -2 >;
using unit_per_cubic_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, -3 >;
using unit_per_hour = dh::units::unit<dh::units::dimensions::time, ratio_hour, -1 >;

using unit_astronomical_unit = dh::units::unit<dh::units::dimensions::length, ratio_astronomical_unit, 1 >;
using unit_lightyear = dh::units::unit<dh::units::dimensions::length, ratio_lightyear, 1 >;
using unit_lightsecond = dh::units::unit<dh::units::dimensions::length, ratio_speed_of_light, 1 >;

using unit_minute = dh::units::unit<dh::units::dimensions::time, ratio_minute, 1 >;
using unit_hour = dh::units::unit<dh::units::dimensions::time, ratio_hour, 1 >;
using unit_day = dh::units::unit<dh::units::dimensions::time, ratio_day, 1 >;
using unit_week = dh::units::unit<dh::units::dimensions::time, ratio_week, 1 >;
using unit_month = dh::units::unit<dh::units::dimensions::time, ratio_month, 1 >;
using unit_year = dh::units::unit<dh::units::dimensions::time, ratio_year, 1 >;

using unit_radian = dh::units::unit<dh::units::dimensions::angle, ratio_radian, 1 >;
using unit_degree = dh::units::unit<dh::units::dimensions::angle, ratio_degree, 1 >;
using unit_arcmin = dh::units::unit<dh::units::dimensions::angle, ratio_arcmin, 1 >;
using unit_arcsec = dh::units::unit<dh::units::dimensions::angle, ratio_arcsec, 1 >;
using unit_milliarcsec = dh::units::unit<dh::units::dimensions::angle, ratio_milliarcsec, 1 >;
using unit_celsius = dh::units::unit<dh::units::dimensions::degree_celsius, std::ratio<1,1>, 1 >;

DH_DECLARE_QUANTITY( astronomical_unit, unit_astronomical_unit )
DH_DECLARE_QUANTITY( lightyear, unit_lightyear )

DH_DECLARE_QUANTITY( ton, unit_megagram )
DH_DECLARE_QUANTITY( liter, unit_cubic_decimeter )
DH_DECLARE_QUANTITY( milliliter, unit_cubic_centimeter )

DH_DECLARE_QUANTITY( minute, unit_minute )
DH_DECLARE_QUANTITY( hour, unit_hour )
DH_DECLARE_QUANTITY( day, unit_day )
DH_DECLARE_QUANTITY( week, unit_week )
DH_DECLARE_QUANTITY( month, unit_month )
DH_DECLARE_QUANTITY( year, unit_year )

DH_DECLARE_QUANTITY( meter_per_second, unit_meter, unit_per_second )
DH_DECLARE_QUANTITY( kilometer_per_hour, unit_kilometer, unit_per_hour )
DH_DECLARE_QUANTITY( lightspeed, unit_lightsecond, unit_per_second )

DH_DECLARE_QUANTITY( radian, unit_radian )
DH_DECLARE_QUANTITY( degree, unit_degree )
DH_DECLARE_QUANTITY( arcminute, unit_arcmin )
DH_DECLARE_QUANTITY( arcsecond, unit_arcsec )
DH_DECLARE_QUANTITY( milliarcsecond, unit_milliarcsec )
DH_DECLARE_QUANTITY( celsius, unit_celsius )

// derived quantities
DH_DECLARE_QUANTITY( acceleration, unit_meter, unit_per_square_second )

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( newton , "N", unit_kilogram, unit_meter, unit_per_square_second)
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( joule , "J", unit_kilogram, unit_square_meter, unit_per_square_second)
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( watt , "W", unit_kilogram, unit_square_meter, unit_per_cubic_second)

using unit_mass_wh = dh::units::unit<dh::units::dimensions::mass, std::ratio<3600000,1>, 1 >;
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( watthour , "Wh", unit_mass_wh, unit_square_meter, unit_per_square_second)

using unit_per_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, -1 >;
using unit_per_square_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, -2 >;
using unit_square_ampere = dh::units::unit<dh::units::dimensions::electric_current, std::ratio<1,1>, 2 >;
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( volt , "V", unit_kilogram, unit_square_meter, unit_per_cubic_second , unit_per_ampere)

using unit_per_meter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,1>, -1 >;
using unit_per_square_meter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,1>, -2 >;
using unit_per_centimeter = dh::units::unit<dh::units::dimensions::length, std::ratio<1,100>, -1 >;
using unit_per_kilogram = dh::units::unit<dh::units::dimensions::mass, std::ratio<1,1>, -1 >;
using unit_up4_second = dh::units::unit<dh::units::dimensions::time, std::ratio<1,1>, 4 >;

DH_DECLARE_QUANTITY( hertz, unit_per_second )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( pascal , "pa", unit_kilogram, unit_per_meter, unit_per_square_second )
DH_DECLARE_QUANTITY( millibar, unit_kilogram, unit_per_centimeter, unit_per_square_second )
DH_DECLARE_QUANTITY( bar, unit_megagram, unit_per_centimeter, unit_per_square_second )

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( ohm , "ohm", unit_kilogram, unit_square_meter, unit_per_cubic_second , unit_per_square_ampere )

DH_DECLARE_QUANTITY( farad, unit_square_ampere, unit_up4_second, unit_per_kilogram, unit_per_square_meter)

DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( coulomb , "C",  unit_ampere, unit_second )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( weber , "Wb",  unit_kilogram, unit_square_meter, unit_per_square_second , unit_per_ampere )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( tesla , "T", unit_kilogram,  unit_per_square_second , unit_per_ampere )
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES( henry , "H", unit_kilogram, unit_square_meter, unit_per_square_second , unit_per_square_ampere )

}

#endif /* DH_UNITS_SI_UNIT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_IMPERIAL_UNITS_INCLUDED
#define DH_UNITS_IMPERIAL_UNITS_INCLUDED

namespace imperial {
    
template<typename T>
using scalar = ::dh::units::scalar<T>;

using ratio_mile = std::ratio<1609344,1000>;
using ratio_yard = std::ratio<9144,10000>;
using ratio_foot = std::ratio<3048,10000>;
using ratio_inch = std::ratio<254,10000>;
using ratio_pound = std::ratio<45359237, 100000>;
using ratio_ounce = std::ratio<28349523125 , 1000000000>;
using ratio_nautical_mile = std::ratio<1852,1>;
using ratio_acre = std::ratio<6361490723407525334,100000000000000000>;

using base_unit_nautical_mile = dh::units::unit<dh::units::dimensions::length, ratio_nautical_mile, 1 >;
using base_unit_mile = dh::units::unit<dh::units::dimensions::length, ratio_mile, 1 >;
using base_unit_yard = dh::units::unit<dh::units::dimensions::length, ratio_yard, 1 >;
using base_unit_foot = dh::units::unit<dh::units::dimensions::length, ratio_foot, 1 >;
using base_unit_inch = dh::units::unit<dh::units::dimensions::length, ratio_inch, 1 >;

using unit_acre = dh::units::unit<dh::units::dimensions::length, ratio_acre, 2 >;
using unit_square_mile = dh::units::unit<dh::units::dimensions::length, ratio_mile, 2 >;
using unit_square_yard = dh::units::unit<dh::units::dimensions::length, ratio_yard, 2 >;
using unit_square_foot = dh::units::unit<dh::units::dimensions::length, ratio_foot, 2 >;
using unit_square_inch = dh::units::unit<dh::units::dimensions::length, ratio_inch, 2 >;

using base_unit_pound = dh::units::unit<dh::units::dimensions::mass, ratio_pound, 1 >;
using base_unit_ounce = dh::units::unit<dh::units::dimensions::mass, ratio_ounce, 1 >;
using unit_fahrentheit = dh::units::unit<dh::units::dimensions::degree_fahrenheit, std::ratio<1,1>, 1 >;

DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( nauticalmile , "nmi" , base_unit_nautical_mile )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( mile , "mi" , base_unit_mile )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( yard , "yd" , base_unit_yard )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( foot , "ft" , base_unit_foot )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( inch , "in" , base_unit_inch )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( pound , "lb" , base_unit_pound )
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT( ounce , "oz" , base_unit_ounce )

DH_DECLARE_QUANTITY( nautical_mile, unit_nauticalmile )
DH_DECLARE_QUANTITY( mile, unit_mile )
DH_DECLARE_QUANTITY( yard, unit_yard )
DH_DECLARE_QUANTITY( foot, unit_foot )
DH_DECLARE_QUANTITY( inch, unit_inch )

DH_DECLARE_QUANTITY( acre, unit_acre )
DH_DECLARE_QUANTITY( square_mile, unit_square_mile )
DH_DECLARE_QUANTITY( square_yard, unit_square_yard )
DH_DECLARE_QUANTITY( square_feet, unit_square_foot )
DH_DECLARE_QUANTITY( square_inch, unit_square_inch )

DH_DECLARE_QUANTITY( pound, unit_pound )
DH_DECLARE_QUANTITY( ounce, unit_ounce )

DH_DECLARE_QUANTITY( miles_per_hour, unit_mile, si::unit_per_hour )
DH_DECLARE_QUANTITY( feet_per_second, unit_foot, si::unit_per_second )
DH_DECLARE_QUANTITY( fahrenheit, unit_fahrentheit )

}

#endif /* DH_UNITS_IMPERIAL_UNITS_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_MATH_INCLUDED
#define DH_UNITS_MATH_INCLUDED

namespace dh {
namespace units {

template<typename T>
using math_return_t = typename dh::mpl::conditional<
    std::is_floating_point<typename std::decay<T>::type::value_type>::value>::template type<
        typename std::decay<T>::type::value_type ,
        double >;

template<typename T>
using can_be_converted_to_radian_t = typename std::enable_if< 
        dh::units::is_dh_quantity<typename std::decay<T>::type >::value &&
        std::is_convertible<typename std::decay<T>::type,si::radian<math_return_t<T>>>::value >::type;

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> sin(T&& x) {
    return std::sin(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> cos(T&& x) {
    return std::cos(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = can_be_converted_to_radian_t<T> >
math_return_t<T> tan(T&& x) {
    return std::tan(si::radian<math_return_t<T>>(std::forward<T>(x)).count() );
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> asin(T x) {
    return std::asin(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> acos(T x) {
    return std::acos(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> atan(T x) {
    return std::atan(x);
}

template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type >
si::radian<T> atan2(T y ,T x) {
    return std::atan2(y,x);
}

// abs, min, max, clamp

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T abs (const T& a) {
    using std::abs;
    return T(abs(a.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T min (const T& a, const T& b) {
    using std::min;
    return T(min(a.count(),b.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T max (const T& a, const T& b) {
    using std::max;
    return T(max(a.count(),b.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value>::type>
T clamp (const T& value, const T& minv,const T& maxv) {
    return max(minv ,min(maxv,value));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value && T::unit_list::empty >::type>
math_return_t<T> exp (const T& value) {
    return std::exp(math_return_t<T>(value.count()));
}

template<typename T, typename = typename std::enable_if<is_dh_quantity<T>::value && T::unit_list::empty >::type>
math_return_t<T> log (const T& value) {
    return std::log(math_return_t<T>(value.count()));
}

template <typename quantity, typename power>
using exponentiation_result_t = dh::units::exponentiation_result::template 
    type<dh::units::quantity, typename quantity::value_type, typename quantity::unit_list, power > ;

template<typename T,intmax_t num,intmax_t den, 
    typename = typename std::enable_if< is_dh_quantity<T>::value && quantity_is_exponentiable<T,std::ratio<num,den>>::value >::type>
exponentiation_result_t<T,std::ratio<num,den>> pow (const T& value, const std::ratio<num,den>& /*ratio*/) {
    return exponentiation_result_t<T,std::ratio<num,den>>(std::pow(math_return_t<T>(value.count()), math_return_t<T>(num)/math_return_t<T>(den)));
}

template<typename T,
    typename = typename std::enable_if< is_dh_quantity<T>::value && quantity_is_exponentiable<T,std::ratio<1,2>>::value >::type>
exponentiation_result_t<T,std::ratio<1,2>> sqrt (const T& value) {
    return exponentiation_result_t<T,std::ratio<1,2>>(std::sqrt(math_return_t<T>(value.count())));
}

}
}

#endif /* DH_UNITS_MATH_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_FORMAT_QUANTITY_INCLUDED
#define DH_UNITS_FORMAT_QUANTITY_INCLUDED

namespace dh {
namespace units {

inline std::string trimLeft(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

inline std::string trimRight(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

inline std::string trim(std::string s) {
    return trimRight(trimLeft(s));
}

template <typename Ratio>
inline std::string to_string() {
    double frac = (double)Ratio::num / (double)Ratio::den;
    std::string rv(15U,0);
    int cx = snprintf( &rv[0], 15U ,"*%.2e",frac);
    rv.resize(cx);
    return rv;
}

template <>
inline std::string to_string<std::atto>() {
    return "a";
}

template <>
inline std::string to_string<std::femto>() {
    return "f";
}

template <>
inline std::string to_string<std::pico>() {
    return "p";
}

template <>
inline std::string to_string<std::nano>() {
    return "n";
}

template <>
inline std::string to_string<std::micro>() {
    return "u";
}

template <>
inline std::string to_string<std::milli>() {
    return "m";
}

template <>
inline std::string to_string<std::centi>() {
    return "c";
}

template <>
inline std::string to_string<std::deci>() {
    return "d";
}

template <>
inline std::string to_string<std::ratio<1,1>>() {
    return "";
}

template <>
inline std::string to_string<std::deca>() {
    return "da";
}

template <>
inline std::string to_string<std::hecto>() {
    return "h";
}

template <>
inline std::string to_string<std::kilo>() {
    return "k";
}

template <>
inline std::string to_string<std::mega>() {
    return "M";
}

template <>
inline std::string to_string<std::giga>() {
    return "G";
}

template <>
inline std::string to_string<std::tera>() {
    return "T";
}

template <>
inline std::string to_string<std::peta>() {
    return "P";
}

template <>
inline std::string to_string<std::exa>() {
    return "E";
}

inline std::string print_power(intmax_t a,bool invert=true) {
    if(a<0 && invert) {
        a=-a;
    }
    if(a==1) {
        return "";
    }
    return "^"+std::to_string(a);
}

struct format_time_unit {

    static inline std::string to_string( si::ratio_minute  ) {
        return "min";
    }

    static inline std::string to_string( si::ratio_hour  ) {
        return "h";
    }

    static inline std::string to_string( si::ratio_day  ) {
        return "day";
    }

    static inline std::string to_string( si::ratio_week  ) {
        return "week";
    }

    static inline std::string to_string( si::ratio_month  ) {
        return "month";
    }

    static inline std::string to_string( si::ratio_year  ) {
        return "year";
    }

    template <typename ratio>
    static inline std::string to_string(ratio) {
        return dh::units::to_string<ratio>()+"s";
    }

};

template <typename T>
using first_unit_t = mpl::invoke_t<typename T::unit_list,mpl::front>;

template <typename T>
using first_dimension_t = typename first_unit_t<T>::dimension_type;

template <typename T,typename = typename std::enable_if< is_time_quantity<T>::value >::type >
std::string print_time_unit(const T& /*in*/) {
    using time_ratio = typename first_unit_t<T>::prefix_type;
    return " "+dh::units::format_time_unit::to_string(time_ratio{})+dh::units::print_power(first_unit_t<T>::power_value);
}

template <typename T,typename = typename std::enable_if< is_time_quantity<T>::value >::type>
std::string to_string(const T& in) {
    using std::to_string;
    return to_string(in.count())+print_time_unit(in);
}

template <typename T,typename = typename std::enable_if< is_time_quantity<T>::value >::type >
std::ostream& operator<<(std::ostream& os, const T& a)
{
    os << a.count() << dh::units::print_time_unit(a);
    return os;
}

#define DH_DECLARE_FORMAT_FUNCTIONS( TYPE, UNIT_STRING ) \
template <typename T > \
std::string to_string(const TYPE <T>& a) { \
    using std::to_string; \
    return to_string(a.count())+ UNIT_STRING; \
} \
template <typename T > \
std::ostream& operator<<(std::ostream& os, const TYPE <T>& a){ \
    os << a.count() << UNIT_STRING; \
    return os; \
}

DH_DECLARE_FORMAT_FUNCTIONS(::si::celsius , " °C")
DH_DECLARE_FORMAT_FUNCTIONS(::imperial::fahrenheit , " °F")
DH_DECLARE_FORMAT_FUNCTIONS(::si::radian , " rad")
DH_DECLARE_FORMAT_FUNCTIONS(::si::degree , " °")
DH_DECLARE_FORMAT_FUNCTIONS(::si::arcminute , " '")
DH_DECLARE_FORMAT_FUNCTIONS(::si::arcsecond , " ''")
DH_DECLARE_FORMAT_FUNCTIONS(::si::milliarcsecond , " marcsec")

// loop units, print positive, then print negative

enum class PRINT_OPTION {
    ONLY_POSTIVE_POWER,
    ONLY_NEGATIVE_POWER_INV,
    ALL_WITH_POWER
};

template<typename A,typename... T>
inline std::string unit_to_string(PRINT_OPTION opt,A first, T... args) {
    return unit_to_string(opt,first)+" "+unit_to_string(opt,args...);
}

template<typename A>
inline std::string unit_to_string(PRINT_OPTION opt,A /*first*/) {
    constexpr bool is_time = std::is_same<typename A::dimension_type,dimensions::time>::value;
    const bool invert_power_sign = !(opt == PRINT_OPTION::ALL_WITH_POWER);
    const bool print = A::power_value!=0 && ( (A::power_value>0 && opt == PRINT_OPTION::ONLY_POSTIVE_POWER) ||
                (A::power_value<0 && opt == PRINT_OPTION::ONLY_NEGATIVE_POWER_INV) ||
                 (opt == PRINT_OPTION::ALL_WITH_POWER) )  ;

    if(print) {
        if(is_time){
            return dh::units::format_time_unit::to_string(typename A::prefix_type{})+dh::units::print_power(A::power_value, invert_power_sign);
        } else {
            return ::dh::units::to_string<typename A::prefix_type>()+A::dimension_type::name()+dh::units::print_power(A::power_value, invert_power_sign);
        }
    }
  
    return "";
}

template<intmax_t i>
inline std::string unit_to_string(PRINT_OPTION opt, dh::units::unit<dh::units::dimensions::angle, si::ratio_radian, i> /*first*/) {
    const bool invert_power_sign = !(opt == PRINT_OPTION::ALL_WITH_POWER);
    const bool print = i!=0 && ( (i>0 && opt == PRINT_OPTION::ONLY_POSTIVE_POWER) ||
                (i<0 && opt == PRINT_OPTION::ONLY_NEGATIVE_POWER_INV) ||
                 (opt == PRINT_OPTION::ALL_WITH_POWER) )  ;

    if(print) {
        return "rad"+dh::units::print_power(i, invert_power_sign);
    }
  
    return "";
}

template<intmax_t i>
inline std::string unit_to_string(PRINT_OPTION opt, dh::units::unit<dh::units::dimensions::angle, si::ratio_arcmin, i> /*first*/) {
    const bool invert_power_sign = !(opt == PRINT_OPTION::ALL_WITH_POWER);
    const bool print = i!=0 && ( (i>0 && opt == PRINT_OPTION::ONLY_POSTIVE_POWER) ||
                (i<0 && opt == PRINT_OPTION::ONLY_NEGATIVE_POWER_INV) ||
                 (opt == PRINT_OPTION::ALL_WITH_POWER) )  ;

    if(print) {
        return "\'"+dh::units::print_power(i, invert_power_sign);
    }
    return "";
}

template<intmax_t i>
inline std::string unit_to_string(PRINT_OPTION opt, dh::units::unit<dh::units::dimensions::angle, si::ratio_arcsec, i> /*first*/) {
    const bool invert_power_sign = !(opt == PRINT_OPTION::ALL_WITH_POWER);
    const bool print = i!=0 && ( (i>0 && opt == PRINT_OPTION::ONLY_POSTIVE_POWER) ||
                (i<0 && opt == PRINT_OPTION::ONLY_NEGATIVE_POWER_INV) ||
                 (opt == PRINT_OPTION::ALL_WITH_POWER) )  ;

    if(print) {
        return "\'\'"+dh::units::print_power(i, invert_power_sign);
    }
    return "";
}

inline std::string unit_to_string(PRINT_OPTION  ) {
    return "";
}

template<typename T>
struct unit_power_positive {
    static constexpr bool value = T::power_value>0;
};

template<typename... T>
std::string unit_list_to_string(mpl::list<T...>) {
    if(sizeof...(T)==0) {
        return "";
    }
    constexpr size_t positive_powers = mpl::invoke_t<mpl::list<T...>,mpl::count_if<mpl::wrap<unit_power_positive>> >::size;
    if(positive_powers != mpl::list<T...>::size && positive_powers!=0) {
        return trim(unit_to_string(PRINT_OPTION::ONLY_POSTIVE_POWER, T{}...))+"/"+trim(unit_to_string(PRINT_OPTION::ONLY_NEGATIVE_POWER_INV, T{}...));
    } else {
        return trim(unit_to_string(PRINT_OPTION::ALL_WITH_POWER, T{}...));
    }
    return "";
}

template <typename T > 
typename std::enable_if< is_dh_quantity<T>::value &&  !is_time_quantity<T>::value, std::string>::type to_string(const T& a) {
    using std::to_string;
    return to_string(a.count()) +" "+ unit_list_to_string(typename T::original_unit_list{}); 
}

template <typename T,typename = typename std::enable_if< is_dh_quantity<T>::value &&  !is_time_quantity<T>::value>::type >
typename std::enable_if< is_dh_quantity<T>::value &&  !is_time_quantity<T>::value, std::ostream&>::type operator<<(std::ostream& os, const T& a)
{
    os << a.count() << ' ' << unit_list_to_string(typename T::original_unit_list{});
    return os;
}

}
}

#endif /* DH_UNITS_FORMAT_QUANTITY_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED
#define DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED

#ifdef DH_UNITS_ENABLE_LIBFMT

template <typename quantity>
struct fmt::formatter<quantity, typename std::enable_if<dh::units::is_dh_quantity<quantity>::value, char>::type> 
{
    std::string value_format;

    auto parse(format_parse_context& ctx) -> decltype(std::end(ctx))
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
  auto format(const quantity& q, FormatContext& ctx) -> decltype(format_to(ctx.out(),value_format,q.count())) 
  {
    return format_to(
        ctx.out(),
        value_format+" {}",
        q.count(), dh::units::unit_list_to_string(typename quantity::original_unit_list{}));
  }
};

#endif /* DH_UNITS_DISABLE_LIBFMT */

#endif /* DH_UNITS_FORMAT_QUANTITY_LIBFMT_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_QUANTITY_CAST_INCLUDED
#define DH_UNITS_QUANTITY_CAST_INCLUDED

namespace dh {
namespace units {

template<typename T,typename A, typename = typename std::enable_if<is_dh_quantity<A>::value && std::is_arithmetic<T>::value >::type>
T quantity_cast (const A& a) {
    return static_cast<T>(a);
}

template<typename T,typename A, 
typename std::enable_if<is_dh_quantity<A>::value && is_dh_quantity<T>::value &&
    lists_contain_same_dimensions<typename A::unit_list, typename T::unit_list>::value,bool>::type = true >
T quantity_cast (const A& a) {
    return T(static_cast<typename T::value_type>(a.count() * unit_list_conversion_factor<math_return_t<T>,typename T::unit_list, typename A::unit_list>::value));
}

template<typename T>
constexpr T constants_zero_kelvin() {
    return static_cast<T>(273.15L);
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<T,si::unit_kelvin>::value ,int>::type = 0 >
T quantity_cast (const ::si::celsius<A>& a) {
    return si::kelvin<typename T::value_type>{a.count() + constants_zero_kelvin<typename T::value_type>()};
}

template<typename T,typename A,
    typename std::enable_if< is_dh_quantity<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<A,si::unit_kelvin>::value 
        && quantity_convertible_to_unit<T,si::unit_celsius>::value 
        ,int>::type = 0 >
T quantity_cast (const A& a) {
    return si::celsius<typename T::value_type>{si::kelvin<typename T::value_type>(a).count() - constants_zero_kelvin<typename T::value_type>()};
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,imperial::unit_fahrentheit>::value
        ,int>::type = 0 >
T quantity_cast (const ::si::celsius<A>& a) {
    return ::imperial::fahrenheit<typename T::value_type>{ a.count()*1.8 + 32};
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,si::unit_celsius>::value
        ,int>::type = 0 >
T quantity_cast (const ::imperial::fahrenheit<A>& a) {
    return ::si::celsius<typename T::value_type>{ (a.count() - 32)*5.0/9.0 };
}

template<typename T,typename A,
    typename std::enable_if< std::is_arithmetic<A>::value && is_dh_quantity<T>::value
        && quantity_convertible_to_unit<T,si::unit_kelvin>::value
        ,int>::type = 0 >
T quantity_cast (const ::imperial::fahrenheit<A>& a) {
    return ::si::kelvin<typename T::value_type>{ (a.count() - 32)*5.0/9.0 + constants_zero_kelvin<typename T::value_type>() };
}

template<typename T,typename A,
    typename std::enable_if< is_dh_quantity<A>::value && is_dh_quantity<T>::value 
        && quantity_convertible_to_unit<A,si::unit_kelvin>::value 
        && quantity_convertible_to_unit<T,imperial::unit_fahrentheit>::value 
        ,int>::type = 0 >
T quantity_cast (const A& a) {
    return ::imperial::fahrenheit<typename T::value_type>{
        (si::kelvin<typename T::value_type>(a).count() - constants_zero_kelvin<typename T::value_type>())*1.8 + 32};
}

}
}

namespace si {
using dh::units::quantity_cast;
}

namespace imperial {
using dh::units::quantity_cast;
}

#endif /* DH_UNITS_QUANTITY_CAST_INCLUDED */

/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DH_UNITS_INCLUDED
#define DH_UNITS_INCLUDED

// primary include file
// includes everything from the library

#endif /* DH_UNITS_INCLUDED */

