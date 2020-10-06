#include <figure.hpp>

int main(int argc, char* argv[]) {
	pcpp::Figure f{argc, argv, 1, 1};

	for (int i=0; i<=15; ++i) {
		f.hist({static_cast<double>(i)}, {1})
			.width(1)
			.pen(0, 0, 0);
	}
	f.range(-1, 16, 0, 1.1);

	return f.show();
}