#pragma once

#include <cstddef>
#include <string>

class QCustomPlot;
class QCPAxisRect;
class QCPAbstractPlottable;
class QCPLayoutGrid;
class QApplication;
class QCPBars;
class QCPGraph;
class QCPItemText;

namespace pcpp {

	struct Color {
		unsigned char r,g,b;
		Color(unsigned char,unsigned char,unsigned char);
		static double h;
		static auto next(int,int) -> Color;
	};

	struct Range {
		double xmin, xmax, ymin, ymax;
		Range(double, double, double, double);
	};

	enum class Style {
		none, dot, cross,
		plus, circle, disc,
		square, diamond, star,
		triangle, triangle_inverted,
		cross_square, plus_square,
		cross_circle, plus_circle,
		peace, pixmap, custom,
	};

	enum class Format {
		png, jpg, pdf, bmp, rastered,
	};

	class Hist {
		private:
			QCPBars* _data;
		public:
			Hist(QCPBars* data);

			auto get_color() -> Color;

			auto color(const Color&) -> Hist&;
			auto color(int,int,int) -> Hist&;
			auto border(const Color&) -> Hist&;
			auto border(int,int,int) -> Hist&;

			auto width(double) -> Hist&;
	};

	class Graph {
		private:
			QCPGraph* _data;
		public:
			Graph(QCPGraph* data);
			auto color(const Color&) -> Graph&;
			auto color(int,int,int) -> Graph&;
			auto get_color() -> Color;
			auto style(const Style&) -> Graph&;
	};

	class Text {
		private:
			QCPItemText* _data;
		public:
			Text(QCPItemText* data);
			auto font(const std::string&, int) -> Text&;
			auto color(const Color&) -> Text&;
			auto color(int,int,int) -> Text&;
			auto rotate(double) -> Text&;
	};

} /* end of namespace pcpp */
