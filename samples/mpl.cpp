/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "dh/mpl/core.hpp"
#include <tuple>
#include <vector>
#include <string>

// meta programming example
// say we have an incoming vector of tuples
// we want to filter the types, and create a tuple of vectors
// functions

// This is a predicate. We cannot use variable templates in C++11, so a type with a value is used. Has to be wrapped in wrap<>
template<typename input>
struct check_size {
    static constexpr bool value = sizeof(input)>=4;
};

// Conditional transformation of input
struct replace_char_with_string {
    template<typename input>
    using type = typename dh::mpl::conditional< std::is_same<char,input>::value >:: template type< std::string , input >;
};

// Transformation of input
struct wrap_in_vector {
    template<typename input>
    using type = std::vector<input>;
};

using namespace dh::mpl;
using input = std::vector<std::tuple<char,bool,double,char,float>>;

// call syntax
using output = invoke_t< unwrap<invoke_t<unwrap<input>,front>>,
    transform<replace_char_with_string>,
    filter<wrap<check_size>>,
    transform<wrap_in_vector>,
    wrap<std::tuple>>;

// check output
using expected = std::tuple<std::vector<std::string>,std::vector<double>,std::vector<std::string>,std::vector<float>>;
static_assert(std::is_same<output ,expected>::value, "types should be the same");

