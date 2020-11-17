#include <figure.hpp>

int main(int argc, char* argv[]) {
  pcpp::Figure f{argc, argv, 1, 1};

  auto text = f.text(1.5, 1.5, "Hello World!");

  text.font("Source Code Pro", 15);
  text.rotate(25);
  text.align(pcpp::Align::bottom|pcpp::Align::center);
  text.color(0, 0, 0);

  auto rect = f.rect({0.0, 0.0}, {1.0, 1.0});
  rect.pen(0, 0, 0);
  rect.brush(120, 120, 120);

  auto line = f.line({1.0, 1.0}, {2.0, 2.0});
  line.head(pcpp::LineEnd::SpikeArrow);

  auto curve = f.curve({2.0, 2.0}, {1.0, 1.0}, {1.5, 2.0}, {1.0, 1.5});
  curve.head(pcpp::LineEnd::SpikeArrow);
  curve.pen(120, 120, 120);

  f.range(0.0, 3.0, 0.0, 3.0);

  return f.show();
}
