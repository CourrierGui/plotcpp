#pragma once

#include <utils.hpp>

class QCPItemLine;

namespace pcpp {
	
	enum class LineEnd {
		None, Disc, Diamond,
		FlatArrow, SpikeArrow, LineArrow,
		Bar, HalfBar, SkewedBar
	};

	template<typename ItemPtr>
		class ItemBase {
			public:
				ItemBase(ItemPtr ptr);
			protected:
				ItemPtr _data;
		};

	class Line : public ItemBase<QCPItemLine*> {
		public:
			Line(QCPItemLine*);
			auto head(const LineEnd&) -> Line&;
			auto tail(const LineEnd&) -> Line&;
	};

} /* end of namespace pcpp */
