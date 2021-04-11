# C++11 physical units library

[![linux-gcc](https://github.com/domohuhn/units/actions/workflows/linux-gcc.yml/badge.svg?branch=main)](https://github.com/domohuhn/units/actions/workflows/linux-gcc.yml)
[![windows-msvc](https://github.com/domohuhn/units/actions/workflows/windows-msvc.yml/badge.svg)](https://github.com/domohuhn/units/actions/workflows/windows-msvc.yml)
[![macos-clang](https://github.com/domohuhn/units/actions/workflows/macos-clang.yml/badge.svg)](https://github.com/domohuhn/units/actions/workflows/macos-clang.yml)

This project is a physical units library for C++11. It defines strong types for quantities like meter or kilogram, and checks for correctness of your calculations are performed at compile time.
The reasoning to check the units at compile time is to prevent errors in the interface usage. If your function takes 4 double, then it is easy to mix up the expected units.
This happend for example to the Mars Climate Orbirter, which crashed due to wrong interface usage (https://en.wikipedia.org/wiki/Mars_Climate_Orbiter). Preventing these kinds of errors is the main idea behind this library.
A major design goal was to create a similar interface and user experience as std::chrono, while providing good error messages and to be reasonable fast to compile.

Here is a code sample:

```c++
#include "dh/units.hpp"
using namespace si;
ampere<> I(3.0); // template argument defaults to double
volt<> U(2.0);
watt<> P = U*I;
ohm<> R = U/I;
ohm<> R_wrong = I/U; // compilation error

imperial::mile<float> mile(1.0);
kilometer<float> km = mile; // ok, km is now 1.609344
```
The library is a header only library, so you can simply include it in your project and you are done!

[Try it on compiler explorer](https://godbolt.org/z/rorvYEao8)

## Features

The following features are supported:
* Creating types with arbitrary units
* The underlying type for the numerical values is a template parameter, so it can be exchanged
* Compile-time checking of compability and creation of conversion functions
* Creating arbitrary math expressions using +, -, * and /
* Types are always promoted to the more accurate type (both the value representation and the prefixes)
* Math functions: 
    * min, max, abs, clamp
    * sin, cos, tan for angles
    * exp, log for dimensionless quantities
* Printing of the types and units
* Seamless integration with std::chrono
* Fully functional in C++11
* [High quality error messages!](https://godbolt.org/z/1hdo1954h)

Note: If you can use C++20, you should have a look at https://github.com/mpusz/units

## Defined units
### SI Base units
| Dimension                 | Unit        | Defined prefixes  | Powers      |
| :---                      | :----       | :---------------: |       :---: |
| Length                    | meter       | atto - exa        |      1,2,3  |
| Time                      | second      | atto - exa        |      1,-1*  |
| Thermodynamic temperature | kelvin      | atto - exa        |          1  |
| Mass                      | kilogram    | atto - exa        |          1  |
| Electric current          | ampere      | atto - exa        |          1  |
| Amount of substance       | mol         | atto - exa        |          1  |
| Luminous intensity        | candela     | atto - exa        |          1  |

(*) Only some of the inverse times have units. Additionally, special units for minute,hour,day,week,month and yaer are defined.

### SI Derived units

| Dimension              | Unit                                   | Defined prefixes  | 
| :---                   | :----                                  | :---------------: |
| Angle                  | radian                                 |                   |
| Angle                  | degree                                 |                   |
| Angle                  | arcmin                                 |                   |
| Angle                  | arcsec                                 |                   |
| Speed                  | meter_per_second, kilometer_per_hour   |                   |
| Force                  | newton                                 | nano - giga       |
| Energy                 | joule, kilowatthour                    | nano - giga       |
| Power                  | watt                                   | nano - giga       |
| Volume                 | liter,milliter                         |                   |
| Frequency              | hertz                                  |                   |
| Pressure               | pascal                                 | nano - giga       |
| Pressure               | millibar                               |                   |
| Pressure               | bar                                    |                   |
| Resistance             | ohm                                    | nano - giga       |
| Charge                 | coulomb                                | nano - giga       |
| Capacitance            | farad                                  |                   |
| magenteic flux         | weber                                  | nano - giga       |
| magnetic flux density  | tesla                                  | nano - giga       |
| Inductivity            | henry                                  | nano - giga       |


### Imperial units
| Dimension                 | Unit        | Powers      |
| :---                      | :----       |       :---: |
| Length                    | mile        |      1,2    |
| Length                    | yard        |      1,2    |
| Length                    | foot        |      1,2    |
| Length                    | inch        |      1,2    |
| Length                    | nautical_mile |      1    |
| Area                      | acre          |      1    |
| Mass                      | pound          |      1    |
| Mass                      | ounce          |      1    |
| Speed                     | miles_per_hour |      1    |
| Speed                     | feet_per_second|      1    |
| Temperature               | fahrenheit     |      1    |

### Conversions between units

Quantities of different units can be converted to each other. Lossless conversions are performed implictly, but you have to specifically ask for a lossy conversions
by using quantity_cast<>. Here is an example:

```c++
si::millimeter<int> mm(1200);
si::meter<int> m = mm; // This conversion would lose precision. You will get a compilation error:
// no match for 'operator=' (operand types are 'si::meter<int>' and 'si::millimeter<int>')

auto m = si::quantity_cast<si::meter<int>>(mm); // ok, m is 1
```
Lossless conversions are either conversions between two quantities with floating point representations or if the conversion factor is larger than 1.
These are the same requirements for conversions as in std::chrono.

A special case are the different temperatures Celsius, Fahrenheit and Kelvin. These units can only be converted using quantity_cast<>.

## Extending the library types
If you want to add your own units to extend the types provided by the library, here is an example how to do it:

```c++
#include "dh/units.hpp"

struct pixel_dimension {
    static std::string name() {
        return "pixel";
    }
};

// template arguments are dimension, scale factor, power
using unit_pixel = dh::units::unit<pixel_dimension, std::ratio<1,1>, 1>;
// define an alias for the new unit
using pixel = dh::units::quantity<int,unit_pixel>;
```
That's it! You can now use all functionality provided by the library. For example, multipling the pixel with another quantity will change the unit list accordingly. You actually only need the struct with the static name() function, both aliases are only for convinience. All units defined in this library use the quantity template, which uses the underlying representation and a variadic list of units as template arguments.

There is a slight problem with this method howerever: The error messages for wrong assignments will be very long, because you will see all the template arguments and instantiations.
The only method to get good error messages in many cases is to use inheritance. The base class has no virtual functions, so neiter the size of the type or the runtime behaviour should change.

```c++
// if you want nice error messages, you will have to use inheritance:
template <typename T = double>
class pixel2 : public
::dh::units::quantity<T, unit_pixel >
{
public:
    using base_type = ::dh::units::quantity<T, unit_pixel >;
    using base_type::base_type;
    pixel2(const base_type& q) : base_type(q) {}
    pixel2(base_type&& q) : base_type(std::move(q)) {}
    pixel2() = default;
    pixel2(const pixel2&) = default;
    pixel2(pixel2&&) = default;
    pixel2& operator=(const pixel2&) = default;
    pixel2& operator=(pixel2&&) = default;
    ~pixel2() = default;
};

// You can also use the macro DH_DECLARE_QUANTITY( NAME, ... )
// e.g. writing:
// DH_DECLARE_QUANTITY( pixel2 , unit_pixel )
// creates the same class as above.
// If you want to create a unit with all SI prefixes,
// you can use the following macro:
// DH_DECLARE_UNITS_ALL_PREFIXES( PREFIX , NAME, DIMENSION, POW )
// For example
// DH_DECLARE_UNITS_ALL_PREFIXES( square_ , pixel, unit_pixel, 2 )
// creates the types square_attopixel to square_exapixel

```

Sometimes, it is useful to create a derived unit, especially for printing the quantities in a human readable way. This can be done in the following ways:

```c++
// define a derived unit
struct derived_pixel_per_squaremeter {
    static std::string name() {
        return "pxm" ;
    }
    // for derived units the first unit in the unit list has to have power 1!
    using unit_list = dh::mpl::list< unit_pixel, si::unit_per_square_meter >;
};

// for derived units the power has to be one!
using unit_pixel_per_squaremeter = dh::units::unit<derived_pixel_per_squaremeter, std::ratio<1,1>, 1>;
// define an alias for the new unit
using pixel_per_squaremeter = dh::units::quantity<double,unit_pixel_per_squaremeter>;
/* or do
DH_DECLARE_DERIVED_DIMENSION_AND_ONE_UNIT(pixel_per_squaremeter, "pxm" , unit_pixel, si::unit_per_square_meter )
or
DH_DECLARE_DERIVED_DIMENSION_ALL_PREFIXES(pixel_per_squaremeter, "pxm" , unit_pixel, si::unit_per_square_meter )
*/
```

# Template metaprogramming

The unit conversion is done via template meta programming. A library providing the features required for the units functionality can be found in the directory mpl. 


As an example of what you can do, consider the following case: You recieve a type as template parameter and you know that it will be a vector with a tuple.
You want to remove certain elements from the tuple, change types matching a predicate to another type and turn it into a tuple with vectors of the remaining types.
First, we will have to define the functors to use:

```c++
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

```
Now, all we have to do is call the defined functions with the algorithms:
```c++
using namespace dh::mpl;
using input = std::vector<std::tuple<char,bool,double,char,float>>;

// call syntax
using output = invoke_t<unwrap<invoke_t<unwrap<input>,front>,
    transform<replace_char_with_string>,
    filter<wrap<check_size>>,
    transform<wrap_in_vector>,
    wrap<std::tuple>>;

// check output
using expected = std::tuple<std::vector<std::string>,std::vector<double>,std::vector<std::string>,std::vector<float>>;
static_assert(std::is_same<output ,expected>::value, "types should be the same");
```

# Compiling

You will need CMake and a C++11 compatible compiler. Compilation should be as simple as executing the following two commands:

```bash
cmake source_directory
make
make install
```

Currently, the library compiles at least with gcc 7.4 and Visual Studio 19.

## Using the library

All you have to is add the following lines to your CMakeLists.txt:
```cmake
find_package(dh_units)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC dh::units)
```

# Examples

Usage examples for the library can be found in the samples directory.


# Tests

Unit tests are done with googletest. Sources for the tests are in the directory test.


# Benchmarks

There are basic benchmarks in the benchmark directory. Running the benchmarks on my machine with gcc 7 gives:

| Benchmark       | Baseline     | Strong units |
| :---            | :----        | :----        |
| addition        | 6.44 ns      | 6.49 ns      |
| multiplication  | 6.48 ns      | 6.48 ns      |
| division        | 17.6 ns      |  17.7 ns     |

As you can see, there is no difference between using raw doubles as baseline or the units library.

# License
This project is licensed under the Mozilla Public Lencse 2.0. Therefore, you should be able to use it in pretty much any other project for any purpose.
See the LICENSE.md for details.
