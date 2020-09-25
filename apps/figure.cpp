#include <plotcpp/figure.hpp>

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include <QApplication>

int main(int argc, char** argv) {

	std::vector<double> x, y, b;
	std::vector<int> t;
	double pi = std::atan(1)*4;
	double f0 = 3;
	double delta = 1.0/1000;

	for (double t=0; t<=1; t+=delta) {
		x.push_back(t);
		y.push_back(std::sin(2*pi*f0*t));
	}
	for (int i=0; i<10; ++i) {
		t.push_back(i);
		b.push_back((i-5)*(i-5)/2);
	}

	pcpp::Figure figure{argc, argv, 1, 2};

	figure.title("Title");
	figure.xlabel("x 1");
	figure.ylabel("y 1");
	/* figure.range({0, 1, -1.1, 1.1}); */
	figure.legend();

	auto plot = figure.plot(x, y, "Plot");
	plot.color(127, 54, 32);
	plot.style(pcpp::Style::cross);

	figure.at(0, 1);
	auto hist = figure.hist({t.begin(), t.end()}, b, "Histogram");
	hist.color(127, 54, 32);
	figure.legend();
	figure.range(-0.5, 9.5, 0, *std::max_element(b.begin(), b.end())+1);

	return figure.show();
}
