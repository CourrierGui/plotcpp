#pragma once

#include <string>
#include <vector>
#include <memory>

#include <plotcpp/utils.hpp>

/*
 * TODO
 * new graph at each plot... bad for animation -> clear should remove them ?
 * plot, hist, ... return Plot object which contains pointers to plotables
 * so that you can modify the plot's options and replot after a plot.
 */

class QApplication;
class QWidget;

namespace Ui {
	class Figure;
} /* end of namespace Ui */

namespace pcpp {

	class PlotWidget;

	class Figure {
		private:
			int&                        _argc;
			char**                      _argv;
			QApplication*               _app;
			Ui::Figure*                 _ui;
			QWidget*                    _widget;
			/* std::shared_ptr<PlotWidget> _plot; */

		public:
			Figure(int&,char**,int=1,int=1);
			Figure(const Figure&) = delete;
			void operator=(const Figure&) = delete;
			~Figure();

			auto plot(
				const std::vector<double>&,
				const std::vector<double>&,
				const std::string& label=""
			) -> Graph;

			auto hist(
				const std::vector<double>&,
				const std::vector<double>&,
				const std::string& label=""
			) -> Hist;

			auto text(
				double,double,
				const std::string&
			) -> Text;

			void range(const Range&);
			void range(double,double,double,double);
			void at(int, int);
			void title (const std::string&);
			void xlabel(const std::string&);
			void ylabel(const std::string&);
			void legend();
			int  show();
			void clear();
			void update();
			auto widget() -> PlotWidget&;
			void save(const std::string&, const Format& f=Format::png);
			void noaxis();
	};

} /* end of namespace pcpp */
