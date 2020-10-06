#include <items.hpp>

#include <qcustomplot.h>

namespace pcpp {

	template<typename ItemPtr>
		ItemBase<ItemPtr>::ItemBase(ItemPtr ptr) : _data{ptr} {  }

	Line::Line(QCPItemLine* data) : ItemBase<QCPItemLine*>{data} {  }

	auto Line::head(const LineEnd& end) -> Line& {
		switch (end) {
			case LineEnd::None:
				_data->setHead(QCPLineEnding::esNone);
				break;
			case LineEnd::Disc:
				_data->setHead(QCPLineEnding::esDisc);
				break;
			case LineEnd::Diamond:
				_data->setHead(QCPLineEnding::esDiamond);
				break;
			case LineEnd::FlatArrow:
				_data->setHead(QCPLineEnding::esFlatArrow);
				break;
			case LineEnd::SpikeArrow:
				_data->setHead(QCPLineEnding::esSpikeArrow);
				break;
			case LineEnd::LineArrow:
				_data->setHead(QCPLineEnding::esLineArrow);
				break;
			case LineEnd::Bar:
				_data->setHead(QCPLineEnding::esBar);
				break;
			case LineEnd::HalfBar:
				_data->setHead(QCPLineEnding::esHalfBar);
				break;
			case LineEnd::SkewedBar:
				_data->setHead(QCPLineEnding::esSkewedBar);
				break;
		}
		return *this;
	}

	auto Line::tail(const LineEnd& end) -> Line& {
		switch (end) {
			case LineEnd::None:
				_data->setTail(QCPLineEnding::esNone);
				break;
			case LineEnd::Disc:
				_data->setTail(QCPLineEnding::esDisc);
				break;
			case LineEnd::Diamond:
				_data->setTail(QCPLineEnding::esDiamond);
				break;
			case LineEnd::FlatArrow:
				_data->setTail(QCPLineEnding::esFlatArrow);
				break;
			case LineEnd::SpikeArrow:
				_data->setTail(QCPLineEnding::esSpikeArrow);
				break;
			case LineEnd::LineArrow:
				_data->setTail(QCPLineEnding::esLineArrow);
				break;
			case LineEnd::Bar:
				_data->setTail(QCPLineEnding::esBar);
				break;
			case LineEnd::HalfBar:
				_data->setTail(QCPLineEnding::esHalfBar);
				break;
			case LineEnd::SkewedBar:
				_data->setTail(QCPLineEnding::esSkewedBar);
				break;
		}
		return *this;
	}
	
} /* end of namespace pcpp */
