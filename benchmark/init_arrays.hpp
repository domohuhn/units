/** @file
 *
 * @copyright 2021 domohuhn
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BENCHMARK_INIT_ARRAYS_INCLUDED
#define BENCHMARK_INIT_ARRAYS_INCLUDED
#include <random>
#include <array>

template<typename A,typename B>
void init_arrays(std::array<A,16>& a, std::array<B,16>&b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(1, 255);

    for ( auto &x: a ){
        x = A(dis(gen));
    }
    for ( auto &x: b ){
        x = B(dis(gen));
    }
}

#endif /* BENCHMARK_INIT_ARRAYS_INCLUDED */
