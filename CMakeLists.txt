cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.17)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.17)
endif()

project(plotcpp
  VERSION 0.1
	DESCRIPTION "Simple plot library"
  LANGUAGES CXX
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CPPCHECK "cppcheck")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

###########################
#### Compilation flags ####
###########################

add_library(target-flags INTERFACE)
target_compile_options(target-flags
  INTERFACE
	-Wall -Wextra -Wpedantic -Wreturn-type -Weffc++ -Wuninitialized
)
target_compile_features(target-flags INTERFACE cxx_std_20)

#################
##### BUILD #####
#################

add_subdirectory(src)
add_subdirectory(apps)
