cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)

include_directories(headers)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

#FetchContent_Declare(
#        Boost
#        URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.7z # downloading a zip release speeds up the download
#        USES_TERMINAL_DOWNLOAD TRUE
#        GIT_PROGRESS TRUE
#        DOWNLOAD_NO_EXTRACT FALSE
#)
#FetchContent_MakeAvailable(Boost)

set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)
set(BUILD_SANDBOX OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        cereal
        URL https://github.com/USCiLab/cereal/archive/refs/tags/v1.3.2.zip
)
FetchContent_MakeAvailable(cereal)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


#enable_testing()

add_executable(
        my_project
#        hello_test
#        hello_test.cc
        src/virtualfs.cc
        headers/virtualfs.h
        main.cc

)
target_link_libraries(
        my_project PUBLIC cereal::cereal
)

#include(GoogleTest)
#gtest_discover_tests(hello_test)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()