cmake_minimum_required(VERSION 3.8)
project(kterm)
set(CMAKE_CXX_STANDARD 14)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(kterm main.cpp Clock.cpp Clock.h)
target_link_libraries(kterm ${GTKMM_LIBRARIES})