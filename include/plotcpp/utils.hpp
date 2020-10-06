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

	class Color {
		public:
			unsigned char r,g,b;
			Color(unsigned char,unsigned char,unsigned char);
	};

	class ColorGen {
		private:
			double _h;
		public:
			ColorGen();
			auto color() -> Color;
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

	enum class Align : uint {
		bottom  = 1 << 0,
		hcenter = 1 << 1,
		top     = 1 << 2,
		left    = 1 << 3,
		center  = 1 << 4,
		right   = 1 << 5,
	};
	using AlignFlags = std::underlying_type_t<Align>;

	inline AlignFlags operator|(Align lhs, Align rhs) {
		using T = std::underlying_type_t<Align>;
		return static_cast<T>(lhs) | static_cast<T>(rhs);
	}

	inline AlignFlags operator|(Align lhs, AlignFlags rhs) {
		using T = std::underlying_type_t<Align>;
		return static_cast<T>(lhs) | rhs;
	}

	inline AlignFlags operator|(AlignFlags lhs, Align rhs) {
		using T = std::underlying_type_t<Align>;
		return lhs | static_cast<T>(rhs);
	}

	inline bool operator& (AlignFlags lhs, Align rhs) {
		using T = std::underlying_type_t<Align>;
		return lhs & static_cast<T>(rhs);
	}

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
			auto color(const Color&)  -> Text&;
			auto color(int,int,int)   -> Text&;
			auto border(const Color&) -> Text&;
			auto border(int,int,int)  -> Text&;
			auto rotate(double) -> Text&;
			auto width() -> double;
			auto height() -> double;
			auto align(const AlignFlags&) -> Text&;
	};

} /* end of namespace pcpp */
