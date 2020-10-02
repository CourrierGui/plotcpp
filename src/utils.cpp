#include <plotcpp/utils.hpp>

#include <qcustomplot.h>

namespace pcpp {

	static const std::array<QCPScatterStyle::ScatterShape,18> qcp_styles = {
		QCPScatterStyle::ssNone,              QCPScatterStyle::ssDot,	
		QCPScatterStyle::ssCross,	            QCPScatterStyle::ssPlus,	
		QCPScatterStyle::ssCircle,	          QCPScatterStyle::ssDisc,	
		QCPScatterStyle::ssSquare,	          QCPScatterStyle::ssDiamond,	
		QCPScatterStyle::ssStar,	            QCPScatterStyle::ssTriangle,	
		QCPScatterStyle::ssTriangleInverted,	QCPScatterStyle::ssCrossSquare,	
		QCPScatterStyle::ssPlusSquare,	      QCPScatterStyle::ssCrossCircle,	
		QCPScatterStyle::ssPlusCircle,	      QCPScatterStyle::ssPeace,
		QCPScatterStyle::ssPixmap,            QCPScatterStyle::ssCustom,
	};

	Range::Range(double xmin, double xmax, double ymin, double ymax)
		: xmin{xmin},xmax{xmax},ymin{ymin},ymax{ymax}
	{

	}

	Color::Color(unsigned char r,unsigned char g,unsigned char b)
		: r{r}, g{g}, b{b}
	{

	}

	//TODO improve this function
	auto Color::next(std::size_t n) -> Color {
		double h = 1.0/5.0*n;
		double s = 0.5;
		double v = 0.95;

		int h_i = static_cast<int>(6*h);
		double f{h*6 - h_i};
		double p{v * (1 - s)};
		double q{v * (1 - f*s)};
		double t{v * (1 - (1 - f) * s)};

		double r=0;
		double g=0;
		double b=0;
		switch (h_i) {
			case 0:  r=v, g=t, b=p; break;
			case 1:  r=q, g=v, b=p; break;
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

	Hist::Hist(QCPBars* data) : _data(data) {  }

	void Hist::color(const Color& c) {
		_data->setPen(QPen(QColor(c.r, c.g, c.b)));
	}

	void Hist::color(int r, int g, int b) {
		_data->setPen(QPen(QColor(r, g, b)));
		_data->setBrush(QBrush(QColor(r, g, b)));
	}

	auto Hist::get_color() -> Color {
		auto c = _data->brush().color();
		return {
			static_cast<unsigned char>(c.red()),
			static_cast<unsigned char>(c.green()),
			static_cast<unsigned char>(c.blue())
		};
	}

	Graph::Graph(QCPGraph* data) : _data(data) {  }

	void Graph::color(const Color& c) {
		_data->setPen(QPen(QColor(c.r, c.g, c.b)));
	}

	void Graph::color(int r, int g, int b) {
		_data->setPen(QPen(QColor(r, g, b)));
	}

	auto Graph::get_color() -> Color {
		auto c = _data->pen().color();
		return {
			static_cast<unsigned char>(c.red()),
			static_cast<unsigned char>(c.green()),
			static_cast<unsigned char>(c.blue())
		};
	}

	void Graph::style(const Style& st) {
		_data->setScatterStyle(qcp_styles[static_cast<int>(st)]);
	}

	Text::Text(QCPItemText* data) : _data{data} {  }

	void Text::font(const std::string& font_name, int size) {
		_data->setFont(QFont(font_name.c_str(), size));
	}

} /* end of namespace pcpp */
