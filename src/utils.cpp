#include <utils.hpp>
#include <numbers>

#include <qcustomplot.h>

namespace pcpp {

	static const std::array<QCPScatterStyle::ScatterShape,18> qcp_styles = {
		QCPScatterStyle::ssNone,              QCPScatterStyle::ssDot,	
		QCPScatterStyle::ssCross,	            QCPScatterStyle::ssPlus,
		QCPScatterStyle::ssCircle,            QCPScatterStyle::ssDisc,
		QCPScatterStyle::ssSquare,            QCPScatterStyle::ssDiamond,	
		QCPScatterStyle::ssStar,              QCPScatterStyle::ssTriangle,
		QCPScatterStyle::ssTriangleInverted,  QCPScatterStyle::ssCrossSquare,	
		QCPScatterStyle::ssPlusSquare,        QCPScatterStyle::ssCrossCircle,	
		QCPScatterStyle::ssPlusCircle,        QCPScatterStyle::ssPeace,
		QCPScatterStyle::ssPixmap,            QCPScatterStyle::ssCustom,
	};

	Range::Range(double _xmin, double _xmax, double _ymin, double _ymax)
		: xmin{_xmin},xmax{_xmax},ymin{_ymin},ymax{_ymax}
	{
	}

	Color::Color(
		unsigned char _r,
		unsigned char _g,
		unsigned char _b)
		: r{_r}, g{_g}, b{_b}
	{
	}

	ColorGen::ColorGen() : _h{1/std::numbers::phi} {  }

	//TODO improve this function
	auto ColorGen::color() -> Color {
		/* double h = 1.0/(size+2)*(n-1); */
		_h += 1/std::numbers::phi;
		_h = std::fmod(_h, 1.0);
		/* double s = 0.5; */
		/* double v = 0.95; */
		double s = 0.99;
		double v = 0.99;

		int h_i = static_cast<int>(6*_h);
		double f{_h*6 - h_i};
		double p{v * (1 - s)};
		double q{v * (1 - f*s)};
		double t{v * (1 - (1 - f) * s)};

		double r=0;
		double g=0;
		double b=0;
		switch (h_i) {
			case 0:  r=v,g=t,b=p; break;
			case 1:  r=q,g=v,b=p; break;
			case 2:  r=p,g=v,b=t; break;
			case 3:  r=p,g=q,b=v; break;
			case 4:  r=t,g=p,b=v; break;
			case 5:  r=v,g=p,b=q; break;
			default: r=0, g=0, b=0; break;
		}

		return Color{
			static_cast<unsigned char>(256*r),
			static_cast<unsigned char>(256*g),
			static_cast<unsigned char>(256*b)
		};
	}

} /* end of namespace pcpp */
