#pragma once

#include <vector>
#include <string>
#include <memory>

#include <plotcpp/utils.hpp>

class QWidget;

namespace pcpp {

	class PlotWidget;

	class PlotWrapper {
		private:
			std::shared_ptr<PlotWidget> _plot;

		public:
			PlotWrapper(int, int, QWidget* parent=0);
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
				const std::string& text
			) -> Text;

			void range(const Range&);
			void range(double,double,double,double);
			void at(int, int);
			void title (const std::string&);
			void xlabel(const std::string&);
			void ylabel(const std::string&);
			void legend();
			void clear();
			void update();
			void save(const std::string&,const Format& f=Format::png,int w=0,int h=0);
			void show();
			auto context() -> std::shared_ptr<PlotWidget>;
			void noaxis();
	};

} /* end of namespace pcpp */
