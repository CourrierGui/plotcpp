#pragma once

#include <utils.hpp>

class QCPItemLine;
class QCPItemCurve;

namespace pcpp {
	
	enum class LineEnd {
		None, Disc, Diamond,
		FlatArrow, SpikeArrow, LineArrow,
		Bar, HalfBar, SkewedBar
	};

	template<typename ItemPtr>
		class LineBase {
			public:
				LineBase(ItemPtr ptr);
				auto head(const LineEnd&) -> LineBase<ItemPtr>&;
				auto tail(const LineEnd&) -> LineBase<ItemPtr>&;
			protected:
				ItemPtr _data;
		};

	class Line : public LineBase<QCPItemLine*> {
		public:
			Line(QCPItemLine*);
	};

	class Curve : public LineBase<QCPItemCurve*> {
		public:
			Curve(QCPItemCurve* data);
	};

} /* end of namespace pcpp */
