/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#pragma once

#ifndef DH_UNITS_FORMAT_QUANTITY_INCLUDED
#define DH_UNITS_FORMAT_QUANTITY_INCLUDED

#include <string>
#include <ratio>
#include "dh/units/si_units.hpp"
#include "dh/units/imperial_units.hpp"
#include <iosfwd>
#include <algorithm> 
#include <cctype>
#include <locale>

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
