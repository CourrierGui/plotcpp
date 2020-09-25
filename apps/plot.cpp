#include <plotcpp/plotwidget.hpp>

#include <vector>
#include <cmath>

#include <QApplication>

int main(int argc, char** argv) {
	QApplication app{argc, argv};

	std::vector<double> x, y;
	double pi = std::atan(1)*4;
	double f0 = 3;
	double delta = 1.0/1000;
	for (double t=0; t<=1; t+=delta) {
		x.push_back(t);
		y.push_back(std::sin(2*pi*f0*t));
	}

	pcpp::PlotWidget window{1, 1};

	window.title("Title");
	window.xlabel("x 1");
	window.ylabel("y 1");
	window.range({0, 1, -1.1, 1.1});
	window.legend();

	auto plot = window.plot(x, y, "Plot");
	plot.color(127, 54, 32);
	/* plot.line_style(pcpp::Style::cross); */
	/* auto hist = window.hist(x, y, "Histogram"); */

	window.show();
	return app.exec();
}


	/* pcpp::figure f{argc, argv, 2, 2}; */


	/* return f.show(); */
