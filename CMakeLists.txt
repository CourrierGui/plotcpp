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
	-Wshadow # warn the user if a variable declaration shadows one from a parent context
	-Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
	# catch hard to track down memory errors
	-Wold-style-cast # warn for c-style casts
	-Wcast-align # warn for potential performance problem casts
	-Wunused # warn on anything being unused
	-Woverloaded-virtual # warn if you overload (not override) a virtual function
	-Wconversion # warn on type conversions that may lose data
	-Wsign-conversion # warn on sign conversions
	-Wnull-dereference # warn if a null dereference is detected
	-Wdouble-promotion # warn if float is implicit promoted to double
	-Wformat=2 # warn on security issues around functions that format output (ie printf)
	-Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
	-Wduplicated-cond # warn if if / else chain has duplicated conditions
	-Wduplicated-branches # warn if if / else branches have duplicated code
	-Wlogical-op # warn about logical operations being used where bitwise were probably wanted
	-Wuseless-cast # warn if you perform a cast to the same type
)
target_compile_features(target-flags INTERFACE cxx_std_20)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)

# execute_process(COMMAND "ln -sf ${CMAKE_BUILD_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}")

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

# Install the config, configversion and custom find modules
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
