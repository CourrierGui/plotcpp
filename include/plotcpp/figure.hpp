#pragma once

#include <string>
#include <vector>
#include <plotcpp/plotwidget.hpp>

/*
 * TODO
 * new graph at each plot... bad for animation -> clear should remove them ?
 * plot, hist, ... return Plot object which contains pointers to plotables
 * so that you can modify the plot's options and replot after a plot.
 */

namespace pcpp {

	class Figure {
		private:
			int           _argc;
			char**        _argv;
			QApplication* _app;
			PlotWidget    _plot;

		public:
			Figure(int,char**,std::size_t=1,std::size_t=1);
			Figure(const Figure&) = delete;
			void operator=(const Figure&) = delete;

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

			void range(const Range&);
			void range(double,double,double,double);
			void at(std::size_t, std::size_t);
			void title (const std::string&);
			void xlabel(const std::string&);
			void ylabel(const std::string&);
			void legend();
			int  show();
			void clear();
			void update();
			auto widget() -> PlotWidget&;
	};

} /* end of namespace pcpp */
