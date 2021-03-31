/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "benchmark/benchmark.h"
#include "dh/units.hpp"
#include <random>
#include <array>
#include "init_arrays.hpp"


void units_addition(benchmark::State& state) {
    std::array<si::meter<double>,16> values_a;
    std::array<si::meter<double>,16> values_b;
    init_arrays<si::meter<double>,si::meter<double>>(values_a,values_b);
    for (auto _ : state){
        si::meter<double> tmp(0);
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] + values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(units_addition);

void units_multiplication(benchmark::State& state) {
    std::array<si::meter_per_second<double>,16> values_a;
    std::array<si::second<double>,16> values_b;
    init_arrays<si::meter_per_second<double>,si::second<double>>(values_a,values_b);

    for (auto _ : state){
        si::meter<double> tmp(0);
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] * values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(units_multiplication);

void units_division(benchmark::State& state) {
    std::array<si::meter<double>,16> values_a;
    std::array<si::second<double>,16> values_b;
    init_arrays<si::meter<double>,si::second<double>>(values_a,values_b);

    for (auto _ : state){
        si::meter_per_second<double> tmp(0);
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] / values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(units_division);
