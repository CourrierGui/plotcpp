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

namespace pcpp {

	class PlotWidget;
	class Figure {
		private:
			int                         _argc;
			char**                      _argv;
			QApplication*               _app;
			std::shared_ptr<PlotWidget> _plot;

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
			auto widget() -> std::shared_ptr<PlotWidget>&;
			void save(const std::string&, const Format& f=Format::png);
	};

} /* end of namespace pcpp */
