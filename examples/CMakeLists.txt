file(GLOB
	qt_examples
	plot_widget.cpp
	animation_widget.cpp
)

file(GLOB
	examples
	sin.cpp
	figure.cpp
	animation.cpp
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
