qt5_wrap_cpp(moc_sources
	${CMAKE_SOURCE_DIR}/include/plotcpp/plotwidget.hpp
	${CMAKE_SOURCE_DIR}/include/plotcpp/animation_widget.hpp
)

# qt5_wrap_ui(ui_wrap
# 	ui/figure.ui OPTIONS --output "include/plotcpp/ui_figure.hpp"
# )

add_library(plotcpp SHARED
	plotwidget.cpp
	plotwrapper.cpp
	animation_widget.cpp

	utils.cpp
	shapes.cpp
	plotables.cpp
	figure.cpp
	animation.cpp
	${moc_sources}
	# ${ui_wrap}
)
target_include_directories(plotcpp
	PUBLIC
		$<INSTALL_INTERFACE:include/plotcpp>
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/plotcpp>
)
target_link_libraries(plotcpp
	PRIVATE
		Qt5::Widgets
		qcustomplot
		target-flags
)

add_library(plotcpp::plotcpp ALIAS plotcpp)

install(
	TARGETS plotcpp
	EXPORT plotcpp-targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include/plotcpp
)
install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include/plotcpp
	DESTINATION include
)
