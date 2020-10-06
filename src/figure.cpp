#include <figure.hpp>
#include <ui_figure.hpp>
#include <plotwidget.hpp>

#include <QApplication>
#include <QWidget>

namespace pcpp {

	Figure::Figure(
		int& argc, char** argv,
		int rows, int cols)
	: _argc{argc}, _argv{argv},
		_app{new QApplication{argc, argv}},
		_ui{new Ui::Figure}, _widget{new QWidget}
		/* _plot{new PlotWidget{rows, cols}} */
	{
		_ui->setupUi(rows, cols, _widget);
		QObject::connect(
			_ui->_save, SIGNAL(clicked()),
			_ui->_plot, SLOT(screen_capture())
		);
	}

	Figure::~Figure() {
		delete _ui;
	}

	auto Figure::plot(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
		-> Graph
	{
		return _ui->_plot->plot(x, y, label);
	}

	auto Figure::hist(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label,
		bool reversed)
		-> Hist
	{
		return _ui->_plot->hist(x, y, label, reversed);
	}

	auto Figure::text(
		double x, double y,
		const std::string& text) -> Text
	{
		return _ui->_plot->text(x, y, text);
	}

	auto Figure::rect(
		const Point& topLeft, const Point& bottomRight) -> Rectangle
	{
		return _ui->_plot->rect(topLeft, bottomRight);
	}

	void Figure::title(const std::string& name)   { _ui->_plot->title(name);   }
	void Figure::clear()                          { _ui->_plot->clear();       }
	void Figure::xlabel(const std::string& label) { _ui->_plot->xlabel(label); }
	void Figure::ylabel(const std::string& label) { _ui->_plot->ylabel(label); }
	void Figure::legend()                         { _ui->_plot->legend();      }
	void Figure::update()                         { _ui->_plot->update();      }
	void Figure::at(int row, int col)             { _ui->_plot->at(row, col);  }
	auto Figure::widget() -> PlotWidget&          { return *_ui->_plot;        }
	void Figure::range(const Range& r)            { _ui->_plot->range(r);      }

	void Figure::range(double xmin, double xmax, double ymin, double ymax) {
		_ui->_plot->range(xmin, xmax, ymin, ymax);
	}

	int  Figure::show() {
		_widget->show();
		return QApplication::exec();
	}

	void Figure::save(
		const std::string& name, const Format& format,
		int width, int height)
	{
		_ui->_plot->save(name, format, width,	height);
	}

	void Figure::noaxis() { _ui->_plot->noaxis(); }

} /* end of namespace sch */
