add_executable(plot plot.cpp)
target_link_libraries(plot plotcpp::plotcpp)

add_executable(animation animation.cpp)
target_link_libraries(animation plotcpp::plotcpp)
