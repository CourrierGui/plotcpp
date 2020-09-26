#pragma once

//TODO move the header file to src directory

#include <plotcpp/utils.hpp>

#include <QWidget>
#include <QObject>

#include <memory>

namespace pcpp {

	class PlotWidget : public QWidget {
		Q_OBJECT

		public:
			/* using GraphPtr = std::shared_ptr<Graph>; */
			using QPlotPtr = std::shared_ptr<QCustomPlot>;

		private:
			QPlotPtr    _plot;
			std::size_t _rows, _cols;
			std::size_t _row,  _col;
			std::map<QCPAbstractPlottable*, std::string> _plots;

		public:
			PlotWidget(std::size_t, std::size_t, QWidget* parent=0);
			~PlotWidget();

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
			void clear();
			void update();
			void save(const std::string&,const Format& f=Format::png);

		private:
			auto get_axis() const -> QCPAxisRect*;
			auto get_axis()       -> QCPAxisRect*;
			void add_to_legend(QCPAxisRect* axis, QCPAbstractPlottable* plot);
			void update_rect(
				const std::vector<double>& x,
				const std::vector<double>& y,
				int dmin, int dmax
			);
			auto color() const -> Color;
			auto get_layout() const -> QCPLayoutGrid*;
			auto get_layout()       -> QCPLayoutGrid*;
	};

} /* end of namespace pcpp */
