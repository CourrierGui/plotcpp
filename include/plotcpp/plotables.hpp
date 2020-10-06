#pragma once

#include <cstddef>
#include <string>

#include <utils.hpp>

class QCPBars;
class QCPGraph;

namespace pcpp {

	template<typename PlotablePtr>
		class PlotableBase {
			public:
				PlotableBase(PlotablePtr ptr);
				auto pen(const Color&)   -> PlotableBase&;
				auto pen(int,int,int)    -> PlotableBase&;
				auto brush(const Color&) -> PlotableBase&;
				auto brush(int,int,int)  -> PlotableBase&;

			protected:
				PlotablePtr _data;
		};

	class Hist : public PlotableBase<QCPBars*> {
		public:
			Hist(QCPBars* data);
			auto width(double) -> Hist&;
	};

	class Graph : public PlotableBase<QCPGraph*> {
		public:
			Graph(QCPGraph* data);
			auto style(const Style&) -> Graph&;
	};

} /* end of namespace pcpp */
