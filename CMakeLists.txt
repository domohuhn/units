# Copyright (C) 2021 by domohuhn
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.14)

project(units VERSION 1.0.0)

option(DH_UNITS_BUILD_TESTS "Build the tests for the hashes module" ON)
option(DH_UNITS_BUILD_BENCHMAKRS "Build the benchmarks for the hashes module" ON)

include(FetchContent)

add_library(mpl INTERFACE)


add_library(mpl_files
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/accumulate.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/bind.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/comparisons.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/conditional.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/core.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/count_if.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/filter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/find_if.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/front.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/functors.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/invoke.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/is_unique.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/join.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/list.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/min_element.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/pop_front.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/push_back.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/push_front.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/transform.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/unwrap.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/void_t.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/wrap.hpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/accumulate_impl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/find_if_impl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/invoke_impl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/is_unique_impl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/join_impl.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/mpl/detail/pop_front_impl.hpp
)

target_include_directories(mpl INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(mpl INTERFACE cxx_std_11)
add_library(dh::mpl ALIAS mpl)
target_link_libraries(mpl_files PUBLIC dh::mpl)
set_target_properties(mpl_files PROPERTIES LINKER_LANGUAGE CXX)


add_library(units INTERFACE)

add_library(units_files
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units.hpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/declaration_macros.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/dimensions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/format_quantity.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/imperial_units.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/math.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/quantity_conversion.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/quantity.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/si_units.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/traits.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/dh/units/unit.hpp
)

target_link_libraries(units INTERFACE dh::mpl)
set_target_properties(units_files PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(units_files PUBLIC dh::mpl)
add_library(dh::units ALIAS units)

#
# Tests
#

include(CTest)

if(BUILD_TESTING AND DH_UNITS_BUILD_TESTS)

	FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.10.x
	)

	FetchContent_GetProperties(googletest)
	if(NOT ${googletest_POPULATED})
		message(STATUS "Populating googletest...")
		FetchContent_Populate(googletest)
	endif()
	set(BUILD_GMOCK OFF)
	set(INSTALL_GTEST OFF)
  	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

	if(TARGET gtest AND TARGET gtest_main)
		add_executable(test_dh_units 
			test/test_accumulate_type.cpp 
			test/test_accumulate_value.cpp 
			test/test_conditional.cpp 
			test/test_join.cpp 
			test/test_filter.cpp 
			test/test_find_if.cpp 
			test/test_is_unique.cpp 
			test/test_min_element.cpp 
			test/test_quantity_conversion.cpp 
			test/test_quantity.cpp 
			test/test_traits.cpp 
			test/test_transform.cpp 
		)
		target_include_directories(test_dh_units PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		)
		if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			target_compile_options(test_dh_units PRIVATE -Wall -Wextra -pedantic)
		elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
			# fix for msvc - otherwises tests wont link
			set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
			set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		endif()

		target_link_libraries(test_dh_units PRIVATE gtest gtest_main dh::units)
		include(GoogleTest)
		gtest_discover_tests(test_dh_units)
	endif()

endif()


#
# Samples
#

add_executable(dh_samples samples/extension.cpp samples/mpl.cpp)
target_include_directories(dh_samples PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

#
# Benchmarks
#

if(DH_UNITS_BUILD_BENCHMAKRS)
	FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.5.2
	)

	FetchContent_GetProperties(googlebenchmark)
	if(NOT ${googlebenchmark_POPULATED})
		message(STATUS "Populating googlebenchmark...")
		FetchContent_Populate(googlebenchmark)
	endif()
	set(BENCHMARK_ENABLE_TESTING OFF)
  	add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})

	if(TARGET benchmark)
		add_executable(bench_dh_units 
			benchmark/bench_baseline.cpp
			benchmark/bench_main.cpp
			benchmark/bench_units.cpp
		)
		target_link_libraries(bench_dh_units PRIVATE benchmark dh::units)
	endif()

endif()


#
# Install
#

install(TARGETS units mpl
        DESTINATION lib
        EXPORT unitsTargets)
install(DIRECTORY include/ DESTINATION include)

install(EXPORT unitsTargets
  FILE dh_units-targets.cmake
  NAMESPACE dh::
  DESTINATION lib/cmake/dh_units
)

include(CMakePackageConfigHelpers)
configure_file(dh_unitsConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/dh_unitsConfig.cmake @ONLY)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/dh_unitsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/dh_unitsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/dh_unitsConfigVersion.cmake
        DESTINATION lib/cmake/dh_units )
