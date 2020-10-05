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

	double Color::h = 1/std::numbers::phi;

	Color::Color(
		unsigned char _r,
		unsigned char _g,
		unsigned char _b)
		: r{_r}, g{_g}, b{_b}
	{
	}

	//TODO improve this function
	auto Color::next(int n, int size) -> Color {
		/* double h = 1.0/(size+2)*(n-1); */
		h += 1/std::numbers::phi;
		h = std::fmod(h, 1.0);
		/* double s = 0.5; */
		/* double v = 0.95; */
		double s = 0.99;
		double v = 0.99;

		int h_i = static_cast<int>(6*h);
		double f{h*6 - h_i};
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

	Hist::Hist(QCPBars* data) : _data(data) {  }

	auto Hist::color(const Color& c) -> Hist& {
		_data->setBrush(QBrush(QColor(c.r, c.g, c.b)));
		return *this;
	}

	auto Hist::color(int r, int g, int b) -> Hist& {
		_data->setBrush(QBrush(QColor(r, g, b)));
		return *this;
	}

	auto Hist::border(const Color& c) -> Hist& {
		_data->setPen(QPen(QColor(c.r, c.g, c.b)));
		return *this;
	}

	auto Hist::border(int r, int g, int b) -> Hist& {
		_data->setPen(QPen(QColor(r, g, b)));
		return *this;
	}

	auto Hist::width(double width) -> Hist& {
		_data->setWidth(width);
		return *this;
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

	auto Graph::color(const Color& c) -> Graph& {
		_data->setPen(QPen(QColor(c.r, c.g, c.b)));
		return *this;
	}

	auto Graph::color(int r, int g, int b) -> Graph& {
		_data->setPen(QPen(QColor(r, g, b)));
		return *this;
	}

	auto Graph::get_color() -> Color {
		auto c = _data->pen().color();
		return {
			static_cast<unsigned char>(c.red()),
			static_cast<unsigned char>(c.green()),
			static_cast<unsigned char>(c.blue())
		};
	}

	auto Graph::style(const Style& st) -> Graph& {
		_data->setScatterStyle(qcp_styles[static_cast<std::size_t>(st)]);
		return *this;
	}

	Text::Text(QCPItemText* data) : _data{data} {  }

	auto Text::font(const std::string& font_name, int size) -> Text& {
		_data->setFont(QFont(font_name.c_str(), size));
		return *this;
	}

	auto Text::color(const Color& c) -> Text& {
		_data->setColor(QColor{c.r, c.g, c.b});
		return *this;
	}

	auto Text::color(int r, int g, int b) -> Text& {
		_data->setColor(QColor{r, g, b});
		return *this;
	}

	auto Text::border(const Color& c) -> Text& {
		_data->setPen(QPen(QColor{c.r, c.g, c.b}));
		return *this;
	}

	auto Text::border(int r, int g, int b) -> Text& {
		_data->setPen(QPen(QColor{r, g, b}));
		return *this;
	}

	auto Text::rotate(double degrees) -> Text& {
		_data->setRotation(degrees);
		return *this;
	}

	auto Text::width() -> double {
		return (_data->topRight->pixelPosition().x()
					- _data->topLeft->pixelPosition().x());
	}

	auto Text::height() -> double {
		return (_data->bottomRight->pixelPosition().y()
					- _data->topRight->pixelPosition().y());
	}

} /* end of namespace pcpp */
