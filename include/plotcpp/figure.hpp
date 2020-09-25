#pragma once

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <iostream>
#include <memory>

#include <plotcpp/utils.hpp>

/*
 * TODO
 * new graph at each plot... bad for animation -> clear should remove them ?
 * plot, hist, ... return Plot object which contains pointers to plotables
 * so that you can modify the plot's options and replot after a plot.
 */

namespace pcpp {

	struct Rect {
		double xmin, xmax, ymin, ymax;
		Rect(double, double, double, double);
	};

	struct Color {
		unsigned char r,g,b;
		Color(unsigned char,unsigned char,unsigned char);
	};

	class figure {
		private:
			using Plot = std::shared_ptr<QCustomPlot*>;
			int           _argc;
			char**        _argv;
			QApplication* _app;
			Plot          _plot;
			std::size_t   _rows, _cols;
			std::size_t   _row,  _col;

			std::map<QCPAbstractPlottable*,std::string> _plots;

		public:
			figure(int,char**,std::size_t=1,std::size_t=1);
			figure(const figure&) = delete;
			void operator=(const figure&) = delete;

			void plot(
				const std::vector<double>&,
				const std::vector<double>&,
				const Color& c,
				const std::string& label=""
			);
			void plot(
				const std::vector<double>&,
				const std::vector<double>&,
				const std::string& label=""
			);
			void hist(
				const std::vector<double>&,
				const std::vector<double>&,
				const Color& c,
				const std::string& label=""
			);
			void hist(
				const std::vector<double>&,
				const std::vector<double>&,
				const std::string& label=""
			);

			void range(const range&);
			void at(std::size_t, std::size_t);
			void title (const std::string&);
			void xlabel(const std::string&);
			void ylabel(const std::string&);
			void legend();
			int  show() const;
			void clear();
			void set_ticks(
				const std::vector<double>&,
				const std::vector<std::string>&
			);
			auto update() -> void;
			void set_data(
				QCPAbstractPlottable*,
				const std::vector<double>&,
				const std::vector<double>&
			);
			auto context() -> Plot;

		private:
			auto color() const -> color;
			void update_rect(
				const std::vector<double>&,
				const std::vector<double>&,
				int=0,int=0
			);
			auto get_axis() -> QCPAxisRect*;
			auto get_axis() const -> const QCPAxisRect*;
			auto get_layout() -> QCPLayoutGrid*;
			auto get_layout() const -> const QCPLayoutGrid*;
			static void add_to_legend(QCPAxisRect*,QCPAbstractPlottable*);
	};

} /* end of namespace pcpp */
