#
# file: CMakeLists.txt
#
# This is the main CMakeLists.txt for mbed-TLS integration with distortos
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.8)
project(mbed-TLS-integration)

if(NOT DEFINED MBED_TLS_DIRECTORY)
	message(SEND_ERROR "Variable with path to mbed TLS directory - MBED_TLS_DIRECTORY - is not defined")
endif()
if(NOT IS_DIRECTORY "${MBED_TLS_DIRECTORY}")
	message(SEND_ERROR "Path to mbed TLS directory - MBED_TLS_DIRECTORY = ${MBED_TLS_DIRECTORY} - is not valid")
endif()
if(NOT EXISTS "${MBED_TLS_DIRECTORY}/CMakeLists.txt")
	message(SEND_ERROR "Path to mbed TLS directory - MBED_TLS_DIRECTORY = ${MBED_TLS_DIRECTORY} - does not contain "
			"CMakeLists.txt")
endif()

if(NOT DEFINED MBED_TLS_CONFIGURATION_H_DIRECTORY)
	message(SEND_ERROR "Variable with path to mbed-TLS-configuration.h - MBED_TLS_CONFIGURATION_H_DIRECTORY - is not "
			"defined")
endif()
if(NOT IS_DIRECTORY "${MBED_TLS_CONFIGURATION_H_DIRECTORY}")
	message(SEND_ERROR "Path to mbed-TLS-configuration.h - MBED_TLS_CONFIGURATION_H_DIRECTORY = "
			"${MBED_TLS_CONFIGURATION_H_DIRECTORY} - is not valid")
endif()
if(NOT EXISTS "${MBED_TLS_CONFIGURATION_H_DIRECTORY}/mbed-TLS-configuration.h")
	message(SEND_ERROR "Path to mbed-TLS-configuration.h - MBED_TLS_CONFIGURATION_H_DIRECTORY = "
			"${MBED_TLS_CONFIGURATION_H_DIRECTORY} - does not contain mbed-TLS-configuration.h")
endif()

add_library(mbed-TLS-interface-library INTERFACE)
target_compile_definitions(mbed-TLS-interface-library INTERFACE
		MBEDTLS_CONFIG_FILE="mbed-TLS-configuration-0.h")
target_include_directories(mbed-TLS-interface-library INTERFACE
		${CMAKE_CURRENT_LIST_DIR}/include
		${MBED_TLS_CONFIGURATION_H_DIRECTORY})
target_link_libraries(mbed-TLS-interface-library INTERFACE
		distortos::distortos)

set(libs mbed-TLS-interface-library)
add_subdirectory("${MBED_TLS_DIRECTORY}" mbed-TLS EXCLUDE_FROM_ALL)

add_library(mbed-TLS-object-library OBJECT
		${CMAKE_CURRENT_LIST_DIR}/mbedTlsThreading.cpp)
target_include_directories(mbed-TLS-object-library PRIVATE
		$<TARGET_PROPERTY:mbedtls,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(mbed-TLS-object-library PRIVATE
		mbed-TLS-interface-library)

target_sources(mbedtls PRIVATE
		$<TARGET_OBJECTS:mbed-TLS-object-library>)
