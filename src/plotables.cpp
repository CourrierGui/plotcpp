#include <plotables.hpp>
#include <utils.hpp>
#include <numbers>

#include <qcustomplot.h>

namespace pcpp {

  static const std::array<QCPScatterStyle::ScatterShape,18> qcp_styles = {
    QCPScatterStyle::ssNone,              QCPScatterStyle::ssDot,
    QCPScatterStyle::ssCross,             QCPScatterStyle::ssPlus,
    QCPScatterStyle::ssCircle,            QCPScatterStyle::ssDisc,
    QCPScatterStyle::ssSquare,            QCPScatterStyle::ssDiamond,
    QCPScatterStyle::ssStar,              QCPScatterStyle::ssTriangle,
    QCPScatterStyle::ssTriangleInverted,  QCPScatterStyle::ssCrossSquare,
    QCPScatterStyle::ssPlusSquare,        QCPScatterStyle::ssCrossCircle,
    QCPScatterStyle::ssPlusCircle,        QCPScatterStyle::ssPeace,
    QCPScatterStyle::ssPixmap,            QCPScatterStyle::ssCustom,
  };

  template<typename T, typename PtrType>
    PlotableBase<T, PtrType>::PlotableBase(PtrType data) : _data{data} {  }

  template<typename T, typename PtrType>
    auto PlotableBase<T, PtrType>::pen(const Color& c)
    -> T&
    {
      this->_data->setPen(QPen(QColor(c.r, c.g, c.b)));
      return *static_cast<T*>(this);
    }

  template<typename T, typename PtrType>
    auto PlotableBase<T, PtrType>::pen(int r, int g, int b)
    -> T&
    {
      this->_data->setPen(QPen(QColor(r, g, b)));
      return *static_cast<T*>(this);
    }
  template<typename T, typename PtrType>
    auto PlotableBase<T, PtrType>::brush(const Color& c)
    -> T&
    {
      this->_data->setBrush(QBrush(QColor(c.r, c.g, c.b)));
      return *static_cast<T*>(this);
    }

  template<typename T, typename PtrType>
    auto PlotableBase<T, PtrType>::brush(int r, int g, int b)
    -> T&
    {
      this->_data->setBrush(QBrush(QColor(r, g, b)));
      return *static_cast<T*>(this);
    }

  Hist::Hist(QCPBars* data) : PlotableBase<Hist,QCPBars*>{data} {  }

  auto Hist::width(double width) -> Hist& {
    this->_data->setWidth(width);
    return *this;
  }

  Graph::Graph(QCPGraph* data) : PlotableBase<Graph,QCPGraph*>{data} {  }

  auto Graph::style(const Style& st) -> Graph& {
    this->_data->setScatterStyle(qcp_styles[static_cast<std::size_t>(st)]);
    return *this;
  }

  template auto PlotableBase<Hist,QCPBars*>::pen(int,int,int) -> Hist&;
  template auto PlotableBase<Hist,QCPBars*>::pen(const Color&) -> Hist&;
  template auto PlotableBase<Hist,QCPBars*>::brush(int,int,int) -> Hist&;
  template auto PlotableBase<Hist,QCPBars*>::brush(const Color&) -> Hist&;

  template auto PlotableBase<Graph,QCPGraph*>::pen(int,int,int) -> Graph&;
  template auto PlotableBase<Graph,QCPGraph*>::pen(const Color&) -> Graph&;
  template auto PlotableBase<Graph,QCPGraph*>::brush(int,int,int) -> Graph&;
  template auto PlotableBase<Graph,QCPGraph*>::brush(const Color&) -> Graph&;

} /* end of namespace pcpp */
