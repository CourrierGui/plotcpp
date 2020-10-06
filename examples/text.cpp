#include <figure.hpp>
#include <shapes.hpp>

int main(int argc, char* argv[]) {
	pcpp::Figure f{argc, argv, 1, 1};

	auto text = f.text(0.5, 0.5, "Hello World!");

	text.font("Source Code Pro", 15);
	text.rotate(25);
	text.align(pcpp::Align::bottom|pcpp::Align::center);
	text.color(0, 0, 0);

	auto rect = f.rect({0.5, 0.5}, {0.6, 0.6});
	rect.pen(0, 0, 0);
	rect.brush(120, 120, 120);

	return f.show();
}