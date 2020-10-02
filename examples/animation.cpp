#include <plotcpp/animation.hpp>

#include <cmath>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	double pi = std::atan(1)*4;
	double f0 = 2.0;
	double delta = 0.05;
	int N = pi/delta;

	auto setup = [pi, N, delta](pcpp::PlotWrapper& f) -> void {
		std::vector<double> x, y;
		x.reserve(N);
		y.reserve(N);
		for (double i=0.0; i<=pi; i+=0.05) {
			x.push_back(i);
			y.push_back(std::sin(i));
		}

		f.title("Sinus animation");
		f.plot(x, y, "sin");
		f.xlabel("time");
		f.ylabel("amplitude");
		f.range({0, pi, -1, 1});
	};

	// TODO: why can't the lambda capture variables by value ?
	auto action = [](int time, pcpp::PlotWrapper& f)
		-> bool
	{
		double f0 = 0.5;
		double pi = std::atan(1)*4;
		double delta = 0.05;
		int N = 4*pi/delta+2;

		std::vector<double> x, y;
		x.reserve(N);
		y.reserve(N);
		double t = time / 1000.0;
		double factor = std::cos(2*pi*f0*t);
		for (int i=0; i<N; ++i) {
			double s = i*delta;
			x.push_back(s);
			y.push_back(std::sin(s) * factor);
		}

		f.clear();
		auto plot = f.plot(x, y, "sin");
		plot.color(30, 30, 30);
		f.range({x.front(), x.back(), -1, 1});
		f.update();
		return true;
	};

	pcpp::Animation anim{argc, argv, 1, 1};
	anim.init(setup);
	anim.add(50, action);

	return anim.start();
}
