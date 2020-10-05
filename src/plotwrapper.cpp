#include <plotwrapper.hpp>
#include <plotwidget.hpp>

#include <QWidget>

namespace pcpp {

PlotWrapper::PlotWrapper(int rows, int cols, QWidget* parent)
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

auto PlotWrapper::text(double x, double y, const std::string& text)
	-> Text
{
	return _plot->text(x, y, text);
}

void PlotWrapper::at(int row, int col) { _plot->at(row, col); }
void PlotWrapper::title (const std::string& name)      { _plot->title(name);  }
void PlotWrapper::xlabel(const std::string& name)      { _plot->xlabel(name); }
void PlotWrapper::ylabel(const std::string& name)      { _plot->ylabel(name); }
void PlotWrapper::legend()                             { _plot->legend();     }
void PlotWrapper::clear()                              { _plot->clear();      }
void PlotWrapper::update()                             { _plot->update();     }

void PlotWrapper::save(
	const std::string& name, const Format& format,
	int width, int height)
{
	_plot->save(name, format, width, height);
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
void PlotWrapper::noaxis() { _plot->noaxis(); }

} /* end of namespace pcpp */
