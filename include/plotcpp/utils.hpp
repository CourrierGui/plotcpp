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
		static Color next(int);
	};

	struct Range {
		double xmin, xmax, ymin, ymax;
		Range(double, double, double, double);
	};

	enum class Style {
		none,
		dot,
		cross,
		plus,
		circle,
		disc,
		square,
		diamond,
		star,
		triangle,
		triangle_inverted,
		cross_square,
		plus_square,
		cross_circle,
		plus_circle,
		peace,
		pixmap,
		custom,
	};

	enum class Format {
		png, jpg, pdf, bmp, rastered,
	};

	class Hist {
		private:
			QCPBars* _data;
		public:
			Hist(QCPBars* data);
			void color(const Color&);
			void color(int,int,int);
			auto get_color() -> Color;
	};

	class Graph {
		private:
			QCPGraph* _data;
		public:
			Graph(QCPGraph* data);

			void color(const Color&);
			void color(int,int,int);
			auto get_color() -> Color;

			void style(const Style&);
	};

	class Text {
		private:
			QCPItemText* _data;
		public:
			Text(QCPItemText* data);
			void font(const std::string&, int);
	};

} /* end of namespace pcpp */
