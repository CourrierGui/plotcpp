#include <figure.hpp>

#include <iostream>

#include <vector>
#include <cmath>
#include <algorithm>

int main(int argc, char* argv[]) {
	std::vector<double> x, y;
	const double pi = std::atan(1)*4;
	const double f0 = 3;
	const double delta = 1.0/1000;

	for (double t=0; t<=1; t+=delta) {
		x.push_back(t);
		y.push_back(std::sin(2*pi*f0*t));
	}

	pcpp::Figure figure{argc, argv, 1, 1};

	figure.title("Sin function");
	figure.xlabel("x-axis");
	figure.ylabel("y-axis");
	figure.legend();
	figure.range(-0.1, 1.1, -1.1, 1.1);

	auto plot = figure.plot(x, y, "Plot");
	plot.color(127, 54, 32);
	plot.style(pcpp::Style::cross);
	figure.save("images/sin.png", pcpp::Format::png, 700, 450);
	return figure.show();
}
