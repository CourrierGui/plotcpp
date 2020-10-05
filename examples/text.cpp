#include <figure.hpp>

int main(int argc, char* argv[]) {
	pcpp::Figure f{argc, argv, 1, 1};

	f.text(0.5, 0.5, "Hello World!")
		.font("Source Code Pro", 15)
		.color(0, 0, 0)
		.rotate(25)
		.align(pcpp::Align::bottom|pcpp::Align::center);

	return f.show();
}
