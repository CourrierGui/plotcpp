#pragma once

#include <plotcpp/utils.hpp>

#include <QWidget>
#include <QObject>

#include <memory>

namespace pcpp {

	class PlotWidget : public QWidget {
		Q_OBJECT

		public:
			using QPlotPtr = std::shared_ptr<QCustomPlot>;

		private:
			QPlotPtr    _plot;
			int         _rows, _cols;
			int         _row,  _col;
			std::map<QCPAbstractPlottable*, std::string> _plots;

		public:
			PlotWidget(int,int, QWidget* parent=0);
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

			auto text(
				double, double,
				const std::string&
			) -> Text;

			void range(const Range&);
			void range(double,double,double,double);
			void at(int,int);
			void title (const std::string&);
			void xlabel(const std::string&);
			void ylabel(const std::string&);
			void legend();
			void clear();
			void update();
			void save(const std::string&,const Format& f=Format::png, int whidth=0, int height=0);
			auto context() -> std::shared_ptr<QCustomPlot>;
			void noaxis();

		private:
			auto get_axis() const -> QCPAxisRect*;
			auto get_axis()       -> QCPAxisRect*;
			void add_to_legend(QCPAxisRect* axis, QCPAbstractPlottable* plot);
			void update_rect(
				const std::vector<double>& x,
				const std::vector<double>& y,
				int dmin, int dmax
			);
			auto color()      const -> Color;
			auto get_layout() const -> QCPLayoutGrid*;
			auto get_layout()       -> QCPLayoutGrid*;
		
		public slots:
			void screen_capture();
	};

} /* end of namespace pcpp */
