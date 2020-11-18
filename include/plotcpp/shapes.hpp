#pragma once

#include <cstddef>
#include <string>

#include <utils.hpp>

class QCPItemText;
class QCPItemRect;

namespace pcpp {

  template<typename ItemPtr, typename D>
    class ShapeBase {
      public:
        ShapeBase(ItemPtr);
        auto pen(const Color&)   -> D&;
        auto pen(int,int,int)    -> D&;
        auto brush(const Color&) -> D&;
        auto brush(int,int,int)  -> D&;
      protected:
        ItemPtr _data;
    };

  class Text : public ShapeBase<QCPItemText*,Text> {
    public:
      Text(QCPItemText*);
      auto width()  -> double;
      auto height() -> double;
      auto font(const std::string&, int) -> Text&;
      auto align(const AlignFlags&)      -> Text&;
      auto rotate(double)                -> Text&;
      auto color(const Color&)           -> Text&;
      auto color(int,int,int)            -> Text&;
  };

  class Rectangle : public ShapeBase<QCPItemRect*,Rectangle> {
    public:
      Rectangle(QCPItemRect*);
  };

} /* end of namespace pcpp */
