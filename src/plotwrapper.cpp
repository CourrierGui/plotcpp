#include <plotcpp/plotwrapper.hpp>
#include <plotcpp/plotwidget.hpp>

#include <QWidget>

namespace pcpp {

PlotWrapper::PlotWrapper(std::size_t rows, std::size_t cols, QWidget* parent)
	: _plot{new PlotWidget{rows, cols, parent}}
{

}

auto PlotWrapper::plot(
	const std::vector<double>& x,
	const std::vector<double>& y,
	const std::string& label
	) -> Graph
{
	return _plot->plot(x, y, label);
}

auto PlotWrapper::hist(
	const std::vector<double>& x,
	const std::vector<double>& y,
	const std::string& label
	) -> Hist
{
	return _plot->hist(x, y, label);
}

void PlotWrapper::at(std::size_t row, std::size_t col) { _plot->at(row, col); }
void PlotWrapper::title (const std::string& name)      { _plot->title(name);  }
void PlotWrapper::xlabel(const std::string& name)      { _plot->xlabel(name); }
void PlotWrapper::ylabel(const std::string& name)      { _plot->ylabel(name); }
void PlotWrapper::legend()                             { _plot->legend();     }
void PlotWrapper::clear()                              { _plot->clear();      }
void PlotWrapper::update()                             { _plot->update();     }

void PlotWrapper::save(const std::string& name, const Format& format) {
	_plot->save(name, format);
}

void PlotWrapper::range(const Range& r) { _plot->range(r); }

void PlotWrapper::range(
	double xmin, double xmax,
	double ymin ,double ymax)
{
	_plot->range(xmin, xmax, ymin, ymax);
}

void PlotWrapper::show() { _plot->show(); }
auto PlotWrapper::context() -> std::shared_ptr<PlotWidget> { return _plot; }

} /* end of namespace pcpp */
