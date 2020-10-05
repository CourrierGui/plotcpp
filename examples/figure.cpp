#include <figure.hpp>

#include <vector>
#include <cmath>
#include <algorithm>

int main(int argc, char** argv) {

	std::vector<double> x, y, b;
	std::vector<int> t;
	const double pi = std::atan(1)*4;
	const double f0 = 3;
	const double delta = 1.0/1000;

	for (double t=0; t<=1; t+=delta) {
		x.push_back(t);
		y.push_back(std::sin(2*pi*f0*t));
	}
	for (int i=0; i<10; ++i) {
		t.push_back(i);
		b.push_back((i-5)*(i-5)/2);
	}

	pcpp::Figure figure{argc, argv, 1, 2};

	//TODO Problem when displaying too long titles
	figure.title("Sin function");
	figure.xlabel("x-axis");
	figure.ylabel("y-axis");
	figure.legend();
	figure.range(-0.2, 1.2, -1.2, 1.2);
	figure.noaxis();

	auto text = figure.text(0.2, 0.5, "Hello!");
	text.font("Source Code Pro", 15);
	figure.plot(x, y, "Plot")
		.color(127, 54, 32)
		.style(pcpp::Style::cross);

	figure.at(0, 1);
	figure.title("Quadratic histogram");
	auto hist = figure.hist({t.begin(), t.end()}, b, "Histogram");
	hist.color(127, 54, 32);
	figure.legend();
	figure.range(-0.5, 9.5, 0, *std::max_element(b.begin(), b.end())+1);
	figure.save("images/double-figure.png", pcpp::Format::png);

	return figure.show();
}
