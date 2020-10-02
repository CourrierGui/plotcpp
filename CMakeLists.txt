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
# set(CMAKE_CXX_CPPCHECK "cppcheck")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

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

qt5_wrap_cpp(moc_sources
	include/plotcpp/plotwidget.hpp
	include/plotcpp/animation_widget.hpp
)
# qt5_wrap_ui(ui_wrap
# 	ui/figure.ui OPTIONS --output "include/plotcpp/ui_figure.hpp"
# )

add_library(plotcpp SHARED
	src/plotwidget.cpp
	src/plotwrapper.cpp
	src/animation_widget.cpp

	src/utils.cpp
	src/figure.cpp
	src/animation.cpp
	${moc_sources}
	# ${ui_wrap}
)
target_include_directories(plotcpp
	PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(plotcpp
	PRIVATE
		Qt5::Widgets
		qcustomplot
		target-flags
)

add_library(plotcpp::plotcpp ALIAS plotcpp)

file(GLOB
	qt_examples
	examples/plot_widget.cpp
	examples/animation_widget.cpp
)

file(GLOB
	examples
	examples/sin.cpp
	examples/figure.cpp
	examples/animation.cpp
)

foreach(app_name ${qt_examples})
	get_filename_component(bin_name ${app_name} NAME_WE)

	add_executable(${bin_name} ${app_name})
	target_link_libraries(${bin_name} Qt5::Widgets plotcpp::plotcpp)
endforeach(app_name)

foreach(app_name ${examples})
	get_filename_component(bin_name ${app_name} NAME_WE)

	add_executable(${bin_name} ${app_name})
	target_link_libraries(${bin_name} plotcpp::plotcpp)
endforeach(app_name)

add_subdirectory(doc)

# execute_process(COMMAND "ln -sf $(pwd)/compile_commands.json ..")

#############################
#### Configuration files ####
#############################

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/plotcpp)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/plotcppConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/plotcppConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/plotcppConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#####################
####   INSTALL   ####
#####################

#Install the config, configversion and custom find modules
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/plotcppConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/plotcppConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

install(EXPORT plotcpp-targets
  FILE
    plotcppTargets.cmake
  NAMESPACE
    plotcpp::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/plotcpp
)

install(
  TARGETS plotcpp
  EXPORT plotcpp-targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(
  DIRECTORY include/plotcpp
  DESTINATION include
)
