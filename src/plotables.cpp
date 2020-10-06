#include <plotables.hpp>
#include <utils.hpp>
#include <numbers>

#include <qcustomplot.h>

namespace pcpp {

	static const std::array<QCPScatterStyle::ScatterShape,18> qcp_styles = {
		QCPScatterStyle::ssNone,              QCPScatterStyle::ssDot,	
		QCPScatterStyle::ssCross,	            QCPScatterStyle::ssPlus,
		QCPScatterStyle::ssCircle,            QCPScatterStyle::ssDisc,
		QCPScatterStyle::ssSquare,            QCPScatterStyle::ssDiamond,	
		QCPScatterStyle::ssStar,              QCPScatterStyle::ssTriangle,
		QCPScatterStyle::ssTriangleInverted,  QCPScatterStyle::ssCrossSquare,	
		QCPScatterStyle::ssPlusSquare,        QCPScatterStyle::ssCrossCircle,	
		QCPScatterStyle::ssPlusCircle,        QCPScatterStyle::ssPeace,
		QCPScatterStyle::ssPixmap,            QCPScatterStyle::ssCustom,
	};

	template<typename PlotablePtr>
		PlotableBase<PlotablePtr>::PlotableBase(PlotablePtr ptr) : _data{ptr} {  }

	template<typename PlotablePtr>
		auto PlotableBase<PlotablePtr>::pen(const Color& c)
		-> PlotableBase<PlotablePtr>&
		{
			_data->setPen(QPen(QColor(c.r, c.g, c.b)));
			return *this;
		}

	template<typename PlotablePtr>
		auto PlotableBase<PlotablePtr>::pen(int r, int g, int b)
		-> PlotableBase<PlotablePtr>&
		{
			_data->setPen(QPen(QColor(r, g, b)));
			return *this;
		}
	template<typename PlotablePtr>
		auto PlotableBase<PlotablePtr>::brush(const Color& c)
		-> PlotableBase<PlotablePtr>&
		{
			_data->setBrush(QBrush(QColor(c.r, c.g, c.b)));
			return *this;
		}

	template<typename PlotablePtr>
		auto PlotableBase<PlotablePtr>::brush(int r, int g, int b)
		-> PlotableBase<PlotablePtr>&
		{
			_data->setBrush(QBrush(QColor(r, g, b)));
			return *this;
		}

	Hist::Hist(QCPBars* data) : PlotableBase<QCPBars*>{data} {  }

	auto Hist::width(double width) -> Hist& {
		_data->setWidth(width);
		return *this;
	}

	Graph::Graph(QCPGraph* data) : PlotableBase<QCPGraph*>{data} {  }

	auto Graph::style(const Style& st) -> Graph& {
		_data->setScatterStyle(qcp_styles[static_cast<std::size_t>(st)]);
		return *this;
	}

	template class PlotableBase<QCPBars*>;
	template class PlotableBase<QCPGraph*>;

} /* end of namespace pcpp */
