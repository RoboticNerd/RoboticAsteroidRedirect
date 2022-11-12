cmake_minimum_required(VERSION 3.0.0)
project(RoboticAsteroidRedirect VERSION 0.1.0)

# setting "This"
set(This RoboticAsteroidRedirect)

include(CTest)
enable_testing()

add_executable(RoboticAsteroidRedirect main.cpp)

add_subdirectory(external/Catch2)

target_include_directories(${PROJECT_NAME} PUBLIC external/Catch2/)

project(${This} C CXX)

# stuff for C++ per youtube.
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
