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

  template<typename ItemPtr, typename D>
    class LineBase {
      public:
        LineBase(ItemPtr data);
        auto head(const LineEnd&) -> D&;
        auto tail(const LineEnd&) -> D&;
        auto pen(const Color&)    -> D&;
        auto pen(int,int,int)     -> D&;
      protected:
        ItemPtr _data;
    };

  class Line : public LineBase<QCPItemLine*,Line> {
    public:
      Line(QCPItemLine*);
  };

  class Curve : public LineBase<QCPItemCurve*,Curve> {
    public:
      Curve(QCPItemCurve* data);
  };

} /* end of namespace pcpp */
