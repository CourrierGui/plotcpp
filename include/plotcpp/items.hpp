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
    class LineBase : public D {
      public:
        auto head(const LineEnd&) -> D&;
        auto tail(const LineEnd&) -> D&;
        auto pen(const Color&)    -> D&;
        auto pen(int,int,int)     -> D&;
    };

  class LineImpl {
    public:
      LineImpl(QCPItemLine*);
    protected:
      QCPItemLine* _data;
  };

  class CurveImpl {
    public:
      CurveImpl(QCPItemCurve* data);
    protected:
      QCPItemCurve* _data;
  };

  using Curve = LineBase<QCPItemCurve*, CurveImpl>;
  using Line  = LineBase<QCPItemLine*, LineImpl>;

} /* end of namespace pcpp */
