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

