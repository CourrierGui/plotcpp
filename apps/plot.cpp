#include <plotcpp/plotcpp.hpp>

#include <vector>
#include <cmath>

int main(int argc, char** argv) {

	sch::Figure f{argc, argv, 2, 2};

	std::vector<double> x, y;
	double pi = std::atan(1)*4;
	double f0 = 3;
	double delta = 1.0/1000;
	for (double t=0; t<=1; t+=delta) {
		x.push_back(t);
		y.push_back(std::sin(2*pi*f0*t));
	}

	f.title("Title");
	f.xlabel("x 1");
	f.ylabel("y 1");
	f.plot(x, y, "sin");
	f.range({0, 1, -1.1, 1.1});
	f.legend();
	/* f.hist(x, y, "legend 1"); */

	f.at(0, 1);
	f.plot(x, y, "legend 2");
	f.title("Title 2");
	f.xlabel("x 2");
	f.ylabel("y 2");
	f.range({0, 1, -1, 1});
	f.legend();
	f.clear();

	f.at(1, 0);
	f.plot(x, y, "legend 3");
	f.title("Title 3");
	f.xlabel("x 3");
	f.ylabel("y 3");
	f.range({0, 1, -1, 1});

	f.at(1, 1);
	f.plot(x, y, "legend 4");
	f.title("Title 4");
	f.xlabel("x 4");
	f.ylabel("y 4");
	f.range({0, 1, -1, 1});

	return f.show();
}
