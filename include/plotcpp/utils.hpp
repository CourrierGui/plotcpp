#pragma once

#include <cstddef>
#include <qcustomplot.h>

class QCustomPlot;
class QCPAxisRect;
class QCPAbstractPlottable;
class QCPLayoutGrid;
class QApplication;
class QCPBars;
class QCPGraph;

namespace pcpp {

	struct Color {
		unsigned char r,g,b;
		Color(unsigned char,unsigned char,unsigned char);
		static Color next(size_t);
	};

	struct Range {
		double xmin, xmax, ymin, ymax;
		Range(double, double, double, double);
	};

	enum class Style {
		none=QCPScatterStyle::ssNone,
		dot=QCPScatterStyle::ssDot,	
		cross=QCPScatterStyle::ssCross,	
		plus=QCPScatterStyle::ssPlus,	
		circle=QCPScatterStyle::ssCircle,	
		disc=QCPScatterStyle::ssDisc,	
		square=QCPScatterStyle::ssSquare,	
		diamond=QCPScatterStyle::ssDiamond,	
		star=QCPScatterStyle::ssStar,	
		triangle=QCPScatterStyle::ssTriangle,	
		triangleInverted=QCPScatterStyle::ssTriangleInverted,	
		crossSquare=QCPScatterStyle::ssCrossSquare,	
		plusSquare=QCPScatterStyle::ssPlusSquare,	
		crossCircle=QCPScatterStyle::ssCrossCircle,	
		plusCircle=QCPScatterStyle::ssPlusCircle,	
		peace=QCPScatterStyle::ssPeace,
		pixmap=QCPScatterStyle::ssPixmap,
		custom=QCPScatterStyle::ssCustom,
	};

	class Hist {
		private:
			QCPBars* _data;
		public:
			Hist(QCPBars* data);
	};

	class Graph {
		private:
			QCPGraph* _data;
		public:
			Graph(QCPGraph* data);
			void color(const Color&);
			void color(int,int,int);
			auto get_color() -> Color;
	};


} /* end of namespace pcpp */
