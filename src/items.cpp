#include <items.hpp>

#include <qcustomplot.h>

namespace pcpp {

  template<typename ItemPtr, typename D>
    LineBase<ItemPtr,D>::LineBase(ItemPtr data) : _data{data} {  }

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
      return *static_cast<D*>(this);
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
      return *static_cast<D*>(this);
    }

  template<typename ItemPtr,typename D>
    auto LineBase<ItemPtr,D>::pen(const Color& c) -> D& {
      this->_data->setPen(QPen(QColor(c.r, c.g, c.b)));
      return *static_cast<D*>(this);
    }

  template<typename ItemPtr,typename D>
    auto LineBase<ItemPtr,D>::pen(int r, int g, int b) -> D& {
      this->_data->setPen(QPen(QColor(r, g, b)));
      return *static_cast<D*>(this);
    }

  Line::Line  (QCPItemLine*  data) : LineBase<QCPItemLine*,Line>{data} {  }
  Curve::Curve(QCPItemCurve* data) : LineBase<QCPItemCurve*,Curve>{data} {  }

  template auto LineBase<QCPItemCurve*,Curve>::head(const LineEnd&) -> Curve&;
  template auto LineBase<QCPItemCurve*,Curve>::tail(const LineEnd&) -> Curve&;
  template auto LineBase<QCPItemCurve*,Curve>::pen(const Color&) -> Curve&;
  template auto LineBase<QCPItemCurve*,Curve>::pen(int,int,int) -> Curve&;

  template auto LineBase<QCPItemLine*,Line>::head(const LineEnd&) -> Line&;
  template auto LineBase<QCPItemLine*,Line>::tail(const LineEnd&) -> Line&;
  template auto LineBase<QCPItemLine*,Line>::pen(const Color&) -> Line&;
  template auto LineBase<QCPItemLine*,Line>::pen(int,int,int) -> Line&;

} /* end of namespace pcpp */
