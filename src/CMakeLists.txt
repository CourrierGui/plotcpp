add_library(plotcpp
	plotcpp.cpp
)
target_include_directories(plotcpp
	PUBLIC
		../include
)
target_link_libraries(plotcpp
	PRIVATE
		Qt5::Widgets qcustomplot
		target-flags
)

add_library(plotcpp::plotcpp ALIAS plotcpp)
