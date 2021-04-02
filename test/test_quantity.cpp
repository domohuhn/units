/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "gtest/gtest.h"
#include "dh/units.hpp"

using namespace si;

// tests that should cause a compilation error
static_assert( !std::is_convertible<meter<double>,kelvin<double> >::value , "you should not be able to convert these values!");
static_assert( !std::is_convertible<kelvin<double>,ampere<double> >::value , "you should not be able to convert these values!");
static_assert( !std::is_convertible<meter<double>,ampere<double> >::value , "you should not be able to convert these values!");
static_assert( !std::is_convertible<kilogram<double>,kelvin<double> >::value , "you should not be able to convert these values!");
static_assert( !std::is_convertible<kilogram<double>,meter<double> >::value , "you should not be able to convert these values!");

TEST(Units, ConvertQuantity) {
    kilometer<double> km(2.0);
    meter<double> m(km);

    ASSERT_EQ( 1000*km.count() , m.count() );

    meter<double> m2(5000);
    kilometer<double> km2(m2);
    ASSERT_EQ( 1000*km2.count() , m2.count() );

    kilometer<double> km3 = m2;
    ASSERT_EQ( 1000*km3.count() , m2.count() );

    kilometer<double> km4{};
    km4 = 2*m2;
    ASSERT_EQ( km4.count() , 10.0 );

    kilometer<double> km5(2*m2);
    ASSERT_EQ( km5.count() , 10.0 );
}


TEST(Units, ConvertSpeeds) {
    
    imperial::miles_per_hour<double> mph{1.0};
    kilometer_per_hour<double> kmh{mph};
    ASSERT_EQ( kmh.count() , 1.609344);

    kmh = kilometer_per_hour<double>(36.0);
    meter_per_second<double> mps(kmh);
    ASSERT_EQ( mps.count() , 10);
    
    meter_per_second<double> mps2(100);
    kilometer_per_hour<double> kmh2(mps2);
    ASSERT_EQ( kmh2.count() , 360);

}

TEST(Units, ScaleQuantityWithScalar) {
    meter<double> m(2.0);
    m *= 3.0;
    ASSERT_EQ( m.count() , 6.0 );
    m /= 4;
    ASSERT_EQ( m.count() , 1.5 );

    auto cpy = 8*m;
    auto cpy2 = m*6;
    ASSERT_EQ( cpy.count() , 12 );
    ASSERT_EQ( cpy2.count() , 9 );

    auto cpy3 = cpy2/9;
    ASSERT_EQ( cpy3.count() , 1 );

    auto cpy4 = -m;
    auto cpy5 = +m;
    ASSERT_EQ( cpy4.count() , -1.5 );
    ASSERT_EQ( cpy5.count() , 1.5 );

}

TEST(Units, InvertQuantity) {
    second<> s(2.0);
    hertz<> h = 1.0/s;
    ASSERT_EQ( h.count() , 0.5 );
}

TEST(Units, TrigonometricFunctions) {
    degree<> deg (90.0);
    auto x = sin(deg);
    ASSERT_NEAR(x,1.0,1.0e-15);

    auto x2 = cos(deg);
    ASSERT_NEAR(x2,0.0,1.0e-15);

    auto x3 = tan(deg/2);
    ASSERT_NEAR(x3,1.0,1.0e-15);

}

TEST(Units, ConvertImperial) {
    imperial::acre<double> acr{1.0};
    imperial::square_feet<double> sqrft(acr);
    
    ASSERT_EQ( sqrft.count() , 43560.0 );

    imperial::mile<double> mile{1.0};
    kilometer<double> km{mile};
    
    ASSERT_EQ( km.count() , 1.609344);

}

TEST(Units, AddQuantities) {
    kilometer<> km(1.0);
    meter<> m(1.0);
    auto add1 = km+m;
    auto add2 = m+km;
    m += km;
    km += m;
    
    ASSERT_NEAR( add1.count() , 1001.0 , 1e-15F );
    ASSERT_NEAR( add2.count() , 1001.0 , 1e-15F );
    ASSERT_EQ( m.count() , 1001.0 );
    ASSERT_NEAR( km.count() , 2.001 , 1e-15F );
}


TEST(Units, SubtractQuantities) {
    kilometer<double> km(1.0);
    meter<double> m(1.0);
    auto sub1 = km-m;
    auto sub2 = m-km;
    m -= km;
    km -= m;
    
    ASSERT_NEAR( sub1.count() , 999.0 , 1e-15F );
    ASSERT_NEAR( sub2.count() , -999.0 , 1e-15F );
    ASSERT_EQ( m.count() , -999.0 );
    ASSERT_NEAR( km.count() , 1.999 , 1e-15F );
}

TEST(Units, MultiplySameQuantities) {
    meter<double> m1(2.0);
    meter<double> m2(3.0);
    auto sqr_m1 = m1*m2;
    ASSERT_EQ( sqr_m1.count() , 6.0 );
}

TEST(Units, MultiplyDifferentQuantities) {
    meter<double> m1(2.0);
    millimeter<double> mm2(3.0);
    auto sqr_m1 = m1*mm2;
    ASSERT_EQ( sqr_m1.count() , 6000.0 );

    meter_per_second<double> mps(5.0);
    second<double> t(3.5);
    meter<double> m = mps*t;
    meter<double> m2 = t*mps;
    ASSERT_EQ( m.count() , 17.5 );
    ASSERT_EQ( m2.count() , 17.5 );
}

// compile time tests

template <typename T,typename A,typename B, typename = void>
struct is_multiply_assignable : std::false_type {};
template <typename T,typename A,typename B>
struct is_multiply_assignable<T,A,B, dh::mpl::void_t<decltype(std::declval<T>() = std::declval<A>()*std::declval<B>())>>
    : std::true_type {};


static_assert( is_multiply_assignable<square_meter<double>,meter<double>,meter<double> >::value , "this is correct");
static_assert( !is_multiply_assignable<kelvin<double>,meter<double>,meter<double> >::value , "you should not be able to convert these values!");
static_assert( !is_multiply_assignable<meter_per_second<double>,meter<double>,second<double> >::value , "you should not be able to convert these values!");
static_assert( !is_multiply_assignable<meter<double>,meter<double>,meter<double> >::value , "you should not be able to convert these values!");


TEST(Units, DivideSameQuantities) {
    meter<double> m1(10.0);
    meter<double> m2(2.0);
    auto d_m1 = m1/m2;
    ASSERT_EQ( d_m1.count() , 5.0 );
}

TEST(Units, DivideDifferentQuantities) {
    meter<double> m1(6.0);
    millimeter<double> m2(3.0);
    auto d_m1 = m1/m2;
    ASSERT_EQ( d_m1.count() , 2000.0 );

    meter<double> m(15.0);
    second<double> t(3.0);
    meter_per_second<double> mps = m/t;
    ASSERT_EQ( mps.count() , 5.0 );
}


TEST(Units, Scalar) {
    dh::units::quantity<double> s1{10.0};
    dh::units::quantity<double> s2{15.0};
    auto s3 = s1+s2;
    ASSERT_EQ( s3.count() , 25.0 );
    auto s4 = s3*s1;
    ASSERT_EQ( s4.count() , 250.0 );
    auto s5 = s4/s3;
    ASSERT_EQ( s5.count() , 10.0 );
}

// compile time tests

template <typename T,typename A,typename B, typename = void>
struct is_division_assignable : std::false_type {};
template <typename T,typename A,typename B>
struct is_division_assignable<T,A,B, dh::mpl::void_t<decltype(std::declval<T>() = std::declval<A>()/std::declval<B>())>>
    : std::true_type {};

static_assert( !is_division_assignable<square_meter<double>,meter<double>,meter<double> >::value , "you should not be able to convert these values!");
static_assert( !is_division_assignable<kelvin<double>,meter<double>,meter<double> >::value , "you should not be able to convert these values!");
static_assert( is_division_assignable<meter_per_second<double>,meter<double>,second<double> >::value , "this should work");
static_assert( !is_division_assignable<meter<double>,meter<double>,meter<double> >::value , "you should not be able to convert these values!");


TEST(Units, OperationChain) {
    kilogram<double> m1(50);
    kilogram<double> m2(150);
    meter_per_second<double> v1(40);
    meter_per_second<double> v2(-40);

    meter_per_second<double> result = (m1*v1 + m2*v2)/( m1+m2 );
    ASSERT_EQ( result.count() , -20.0 );
}


TEST(Units, DerivedUnits) {
    volt<double> U(5.0);
    ampere<double> I(4.0);

    auto r1 = U*I;
    watt<double> P = U*I;
    ASSERT_EQ( P.count() , 20.0 );
    ASSERT_EQ( r1.count() , 20.0 );

    ohm<double> R = U/I;
    ASSERT_EQ( R.count() , 1.25 );

    kilogram<double> kg(2.0);
    meter<double> m(4.0);
    second<double> s(2.0);
    joule<double> E = 0.5*kg*m*m/(s*s);
    ASSERT_EQ( E.count() , 4.0 );
    watt<double> P2 = E/second<double>(2.0);
    ASSERT_EQ( P2.count() , 2.0 );

    newton<double> N = kg*m/(s*s);
    kilonewton<double> kN = N;
    kilonewton<double> kN2 = kg*m/(s*s);
    ASSERT_EQ( N.count() , 2.0 );
    ASSERT_EQ( kN.count() , 0.002 );
    ASSERT_EQ( kN2.count() , 0.002 );
}

TEST(Units, Degree) {
    const auto correct_value = 57.295779513082320876798154814105170332405472466564321549160243861L;
    const auto precision = 2.22e-16L;
    radian<double> rad(1.0);
    degree<double> deg(rad);
    ASSERT_NEAR( deg.count() , correct_value, precision*correct_value );
}


TEST(Units, MinMax) {
    meter<double> m1(-2.5);
    meter<double> m2(7.5);
    auto a = min(m1,m2);
    auto b = max(m1,m2);
    static_assert(std::is_same<meter<double>,decltype(a)>::value,"types should stay the same!");
    static_assert(std::is_same<meter<double>,decltype(b)>::value,"types should stay the same!");

    ASSERT_EQ( a.count() , -2.5 );
    ASSERT_EQ( b.count() , 7.5 );
}

TEST(Units, Abs) {
    meter<double> m1(-2.5);
    meter<double> m2(7.5);
    auto a = abs(m1);
    auto b = abs(m2);
    static_assert(std::is_same<meter<double>,decltype(a)>::value,"types should stay the same!");
    static_assert(std::is_same<meter<double>,decltype(b)>::value,"types should stay the same!");

    ASSERT_EQ( a.count() , 2.5 );
    ASSERT_EQ( b.count() , 7.5 );
}


TEST(Units, Clamp) {
    meter<double> m1(-4.23424);
    meter<double> m2(3.25);
    meter<double> low(2.5);
    meter<double> up(7.5);
    auto a = clamp(m1,low,up);
    auto b = clamp(m2,low,up);
    static_assert(std::is_same<meter<double>,decltype(a)>::value,"types should stay the same!");
    static_assert(std::is_same<meter<double>,decltype(b)>::value,"types should stay the same!");

    ASSERT_EQ( a.count() , 2.5 );
    ASSERT_EQ( b.count() , 3.25 );
}

TEST(Units, Exp) {
    meter<double> m1(0.0);
    meter<double> m2(1.0);
    auto result = exp(m1/m2);
    ASSERT_EQ(result,1.0);
}

TEST(Units, Log) {
    meter<double> m1(5.0);
    meter<double> m2(5.0);
    auto result = log(m1/m2);
    ASSERT_EQ(result,0.0);
}

TEST(Units, Comparisions) {
    meter<double> m(1000);
    kilometer<double> km(1);
    ASSERT_EQ(m,m);
    ASSERT_EQ(km,km);
    ASSERT_EQ(m,km);
    kilometer<double> km_bigger(1000);
    ASSERT_NE(m,km_bigger);
    ASSERT_GT(km_bigger,m);
    ASSERT_GE(km,m);
    ASSERT_LT(m,km_bigger);
    ASSERT_LE(km,m);
}

TEST(Units, MultiplicationConversion) {
    using namespace dh::mpl;
    using namespace dh::units;

    auto factor1 = dh::units::compute_multiply_conversion_factor<double>(
      dh::mpl::list<si::unit_meter,si::unit_per_second>{},
      dh::mpl::list<si::unit_millisecond>{});
    auto factor2 = dh::units::compute_multiply_conversion_factor<double>(
      dh::mpl::list<si::unit_millisecond>{},
      dh::mpl::list<si::unit_meter,si::unit_per_second>{}
      );
    EXPECT_EQ(factor1,factor2);
    EXPECT_EQ(factor1,0.001);
    auto factor3 = dh::units::compute_multiply_conversion_factor<double>(
    dh::mpl::list<si::unit_second>{},
      dh::mpl::list<si::unit_meter,si::unit_per_second>{}
      );
    EXPECT_EQ(factor3,1.0);
    using moo = typename select_highest_accuracy_for_first_dimension_in_list::template type<si::unit_per_second,si::unit_millisecond>;
// m/s -> /ms
    auto pf1 = unit_list_conversion_factor<double,
        mpl::list<
            typename select_highest_accuracy_for_first_dimension_in_list::template type<si::unit_meter,si::unit_millisecond>,
            moo>,
        mpl::list<si::unit_meter,si::unit_per_second>>::value;
        
// ms -> ms
    auto pf2 = unit_list_conversion_factor<double,
        mpl::list<typename select_highest_accuracy_for_first_dimension_in_list::template type<si::unit_millisecond,si::unit_meter,si::unit_per_second>>,
        mpl::list<si::unit_millisecond>>::value;
        
    EXPECT_EQ(pf1,0.001);
    EXPECT_EQ(pf2,1.0);
    meter_per_second<> mps(5.0);
    auto m1 = mps*si::millisecond<int64_t>(100);
    auto m2 = si::millisecond<int64_t>(100)*mps;

    ASSERT_EQ( m1.count() , 0.5 );
    ASSERT_EQ( m2.count() , 0.5 );
}

TEST(Units, AdditonConversion) {
    auto ts = si::second<>(2.0) + si::millisecond<>(100) ;
    auto ts2 = si::millisecond<>(100) + si::second<>(2.0) ;
    ASSERT_NEAR( ts.count() , 2100, 3e-16F );
    ASSERT_NEAR( ts2.count() , 2100, 3e-16F );
}

TEST(Units, ChronoIntegration) {
    meter<> m(11);
    meter_per_second<> mps = m/std::chrono::milliseconds(2000);
    ASSERT_EQ(mps.count(),5.5);
    meter<> m2 = mps*std::chrono::milliseconds(100);
    meter<> m3 = std::chrono::milliseconds(100)*mps;

    ASSERT_NEAR( m2.count() , 0.55, 3e-16F );
    ASSERT_NEAR( m3.count() , 0.55, 3e-16F );

    auto ts = si::second<>(2.0) + std::chrono::milliseconds(100) ;
    auto ts2 = std::chrono::milliseconds(100) + si::second<>(2.0) ;
    ASSERT_NEAR( ts.count() , 2100, 3e-16F );
    ASSERT_NEAR( ts2.count() , 2100, 3e-16F );

    auto ts3 = si::second<>(2.0) - std::chrono::milliseconds(100) ;
    auto ts4 = std::chrono::milliseconds(100) - si::second<>(2.0) ;
    ASSERT_NEAR( ts3.count() , 1900, 3e-16F );
    ASSERT_NEAR( ts4.count() , -1900, 3e-16F );

#ifndef _MSC_VER
    auto spm = si::millisecond<>(2000.0)/m;
    meter<> mr = std::chrono::seconds(2)/spm;
    ASSERT_NEAR( mr.count() , 11.0, 3e-16F );
#endif

}

TEST(Units, Print) {
    std::cout<<"seconds "<< millisecond<>(42.0) <<"\n";
    std::cout<<"seconds "<< second<>(42.0) <<"\n";
    std::cout<<"min "<< minute<>(42.0) <<"\n";
    std::cout<<"hour "<< hour<>(42.0) <<"\n";
    std::cout<<"day "<< day<>(42.0) <<"\n";
    std::cout<<"week "<< week<>(42.0) <<"\n";
    std::cout<<"month "<< month<>(42.0) <<"\n";
    std::cout<<"year "<< year<>(42.0) <<"\n";
    std::cout<<"celsius "<< imperial::fahrenheit<>(42.0) <<"\n";
    std::cout<<"fahrenheit "<< celsius<>(42.0) <<"\n";
    std::cout<<"as "<< arcsecond<>(42.0) <<"\n";
    std::cout<<"am "<< arcminute<>(42.0) <<"\n";
    std::cout<<"deg "<< degree<>(42.0) <<"\n";
    std::cout<<"rad "<< radian<>(42.0) <<"\n";
    std::cout<<"mps "<< meter_per_second<>(42.0) <<"\n";
    std::cout<<"kph "<< kilometer_per_hour<>(42.0) <<"\n";
    std::cout<<"colomb "<< coulomb<>(43) <<"\n";
    std::cout<<"hz "<< hertz<>(44) <<"\n";
    std::cout<<"nautical "<<imperial::nautical_mile<>{} <<"\n";
}
