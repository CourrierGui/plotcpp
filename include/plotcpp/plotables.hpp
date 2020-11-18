#pragma once

#include <cstddef>
#include <string>

#include <utils.hpp>

class QCPBars;
class QCPGraph;

namespace pcpp {

  template<typename T, typename PtrType>
    class PlotableBase {
      public:
        PlotableBase(PtrType);
        auto pen(const Color&)   -> T&;
        auto pen(int,int,int)    -> T&;
        auto brush(const Color&) -> T&;
        auto brush(int,int,int)  -> T&;
    protected:
        PtrType _data;
    };

  class Hist : public PlotableBase<Hist,QCPBars*> {
    public:
      Hist(QCPBars* data);
      auto width(double) -> Hist&;
  };

    class Graph : public PlotableBase<Graph,QCPGraph*> {
      public:
        Graph(QCPGraph* data);
        auto style(const Style&) -> Graph&;
    };

} /* end of namespace pcpp */
