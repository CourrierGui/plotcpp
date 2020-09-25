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

	pcpp::PlotWidget plot_widget{1, 2};

	plot_widget.title("Title");
	plot_widget.xlabel("x 1");
	plot_widget.ylabel("y 1");
	plot_widget.range({0, 1, -1.1, 1.1});
	plot_widget.legend();

	auto plot = plot_widget.plot(x, y, "Plot");
	plot.color(127, 54, 32);
	plot.style(pcpp::Style::cross);
	plot_widget.at(0, 1);
	auto hist = plot_widget.hist(x, y, "Histogram");
	hist.color(127, 54, 32);

	plot_widget.show();
	return app.exec();
}
