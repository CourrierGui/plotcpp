#include <plotcpp/figure.hpp>

#include <QApplication>

namespace pcpp {

	Figure::Figure(
		int argc, char** argv,
		std::size_t rows, std::size_t cols)
	: _argc{argc}, _argv{argv},
		_app{new QApplication{argc, argv}},
		_plot{rows, cols}
	{
	}

	auto Figure::plot(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
		-> Graph
	{
		return _plot.plot(x, y, label);
	}

	auto Figure::hist(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
		-> Hist
	{
		return _plot.hist(x, y, label);
	}

	void Figure::title(const std::string& name)       { _plot.title(name);   }
	void Figure::clear()                              { _plot.clear();       }
	void Figure::xlabel(const std::string& label)     { _plot.xlabel(label); }
	void Figure::ylabel(const std::string& label)     { _plot.ylabel(label); }
	void Figure::legend()                             { _plot.legend();      }
	void Figure::update()                             { _plot.update();      }
	void Figure::at(std::size_t row, std::size_t col) { _plot.at(row, col);  }
	auto Figure::widget() -> PlotWidget&              { return _plot;        }

	void Figure::range(const Range& r)                { _plot.range(r);      }
	void Figure::range(double xmin, double xmax, double ymin, double ymax) {
		_plot.range(xmin, xmax, ymin, ymax);
	}

	int  Figure::show() {
		_plot.show();
		return QApplication::exec();
	}

} /* end of namespace sch */
