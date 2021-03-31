/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "benchmark/benchmark.h"
#include "init_arrays.hpp"


void baseline_addition(benchmark::State& state) {
    std::array<double,16> values_a;
    std::array<double,16> values_b;
    init_arrays<double,double>(values_a,values_b);
    for (auto _ : state){
        double tmp = 0;
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] + values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(baseline_addition);

void baseline_multiplication(benchmark::State& state) {
    std::array<double,16> values_a;
    std::array<double,16> values_b;
    init_arrays<double,double>(values_a,values_b);

    for (auto _ : state){
        double tmp = 0;
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] * values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(baseline_multiplication);

void baseline_division(benchmark::State& state) {
    std::array<double,16> values_a;
    std::array<double,16> values_b;
    init_arrays<double,double>(values_a,values_b);

    for (auto _ : state){
        double tmp = 0;
        for ( size_t i=0; i<16; ++i ){
            tmp += values_a[i] / values_b[i];
        }
        benchmark::DoNotOptimize(tmp);
    }
}
BENCHMARK(baseline_division);
