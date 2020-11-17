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
        auto head(const LineEnd&) -> LineBase<ItemPtr,D>&;
        auto tail(const LineEnd&) -> LineBase<ItemPtr,D>&;
        auto pen(const Color&)    -> LineBase<ItemPtr,D>&;
        auto pen(int,int,int)     -> LineBase<ItemPtr,D>&;
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
