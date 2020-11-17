#include <items.hpp>

#include <qcustomplot.h>

namespace pcpp {

  template<typename ItemPtr,typename D>
    auto LineBase<ItemPtr, D>::head(const LineEnd& end) -> D& {
      switch (end) {
        case LineEnd::None:
          this->_data->setHead(QCPLineEnding::esNone);
          break;
        case LineEnd::Disc:
          this->_data->setHead(QCPLineEnding::esDisc);
          break;
        case LineEnd::Diamond:
          this->_data->setHead(QCPLineEnding::esDiamond);
          break;
        case LineEnd::FlatArrow:
          this->_data->setHead(QCPLineEnding::esFlatArrow);
          break;
        case LineEnd::SpikeArrow:
          this->_data->setHead(QCPLineEnding::esSpikeArrow);
          break;
        case LineEnd::LineArrow:
          this->_data->setHead(QCPLineEnding::esLineArrow);
          break;
        case LineEnd::Bar:
          this->_data->setHead(QCPLineEnding::esBar);
          break;
        case LineEnd::HalfBar:
          this->_data->setHead(QCPLineEnding::esHalfBar);
          break;
        case LineEnd::SkewedBar:
          this->_data->setHead(QCPLineEnding::esSkewedBar);
          break;
      }
      return *this;
    }

  template<typename ItemPtr, typename D>
    auto LineBase<ItemPtr,D>::tail(const LineEnd& end) -> D& {
      switch (end) {
        case LineEnd::None:
          this->_data->setTail(QCPLineEnding::esNone);
          break;
        case LineEnd::Disc:
          this->_data->setTail(QCPLineEnding::esDisc);
          break;
        case LineEnd::Diamond:
          this->_data->setTail(QCPLineEnding::esDiamond);
          break;
        case LineEnd::FlatArrow:
          this->_data->setTail(QCPLineEnding::esFlatArrow);
          break;
        case LineEnd::SpikeArrow:
          this->_data->setTail(QCPLineEnding::esSpikeArrow);
          break;
        case LineEnd::LineArrow:
          this->_data->setTail(QCPLineEnding::esLineArrow);
          break;
        case LineEnd::Bar:
          this->_data->setTail(QCPLineEnding::esBar);
          break;
        case LineEnd::HalfBar:
          this->_data->setTail(QCPLineEnding::esHalfBar);
          break;
        case LineEnd::SkewedBar:
          this->_data->setTail(QCPLineEnding::esSkewedBar);
          break;
      }
      return *this;
    }

  template<typename ItemPtr,typename D>
    auto LineBase<ItemPtr,D>::pen(const Color& c) -> D& {
      this->_data->setPen(QPen(QColor(c.r, c.g, c.b)));
      return *this;
    }

  template<typename ItemPtr,typename D>
    auto LineBase<ItemPtr,D>::pen(int r, int g, int b) -> D& {
      this->_data->setPen(QPen(QColor(r, g, b)));
      return *this;
    }

  LineImpl::LineImpl  (QCPItemLine*  data) : _data{data} {  }
  CurveImpl::CurveImpl(QCPItemCurve* data) : _data{data} {  }

  template class LineBase<QCPItemLine*,LineImpl>;
  template class LineBase<QCPItemCurve*,CurveImpl>;

  /* template auto LineBase<QCPItemLine*, LineImpl>::head(const LineEnd&) -> LineImpl&; */
  /* template auto LineBase<QCPItemLine*, LineImpl>::tail(const LineEnd&) -> LineImpl&; */
  /* template auto LineBase<QCPItemLine*, LineImpl>::pen(const Color&) -> LineImpl&; */
  /* template auto LineBase<QCPItemLine*, LineImpl>::pen(int,int,int) -> LineImpl&; */

  /* template auto LineBase<QCPItemCurve*, CurveImpl>::head(const LineEnd&) -> CurveImpl&; */
  /* template auto LineBase<QCPItemCurve*, CurveImpl>::tail(const LineEnd&) -> CurveImpl&; */
  /* template auto LineBase<QCPItemCurve*, CurveImpl>::pen(const Color&) -> CurveImpl&; */
  /* template auto LineBase<QCPItemCurve*, CurveImpl>::pen(int,int,int) -> CurveImpl&; */

} /* end of namespace pcpp */
