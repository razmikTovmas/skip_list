cmake_minimum_required(VERSION 3.8)
project(skip_list VERSION 1.0.0 LANGUAGES CXX)
option(console_BUILD_TESTS OFF)
option(EXAMPLES "Build Examples" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(STATUS "GCC")
  add_compile_options(
    -finstrument-functions -fpermissive -fverbose-asm -pedantic -Waddress
    -Wall -Warray-bounds=1 -Wbool-compare -Wbool-operation -Wc++11-compat
    -Wc++14-compat -Wc++17-compat -Wcast-align -Wcast-qual -Wconversion
    -Wfloat-equal -Werror -Wextra -Wformat -Wformat-nonliteral -Wformat=2
    -Wmain -Wparentheses -Winvalid-pch -Wmissing-declarations
    -Wmissing-format-attribute -Wmissing-include-dirs -Wredundant-decls
    -Wredundant-decls -Wswitch-default -Wswitch-enum -Wreturn-type -Wshadow
    -Wunreachable-code -Wunused-function -Wunused-label -Wunused-value
    -Wunused-variable -Wnoexcept
  )

endif()

add_library(skip_list INTERFACE)
add_library(skip_list::skip_list ALIAS skip_list)

if (CMAKE_CXX_STANDARD EQUAL 17)
    target_compile_features(skip_list INTERFACE cxx_std_17)
    message(STATUS "Using C++17")
endif()



target_include_directories(skip_list INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if (EXAMPLES)
  add_subdirectory(examples)
endif()

