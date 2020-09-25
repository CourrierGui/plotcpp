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

qt5_wrap_cpp(moc_sources include/plotcpp/plotwidget.hpp)

add_library(plotcpp SHARED
	src/plotwidget.cpp
	src/utils.cpp
	# src/figure.cpp
	# src/animation.cpp
	${moc_sources}
)
target_include_directories(plotcpp
	PUBLIC
		include
)
target_link_libraries(plotcpp
	PRIVATE
		Qt5::Widgets
		qcustomplot
		target-flags
)

add_library(plotcpp::plotcpp ALIAS plotcpp)

foreach(app_name apps/plot.cpp) # apps/animation.cpp)
	get_filename_component(bin_name ${app_name} NAME_WE)

	add_executable(${bin_name} ${app_name})
	target_link_libraries(${bin_name} Qt5::Widgets plotcpp::plotcpp )
endforeach(app_name)
