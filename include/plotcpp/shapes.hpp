#pragma once

#include <cstddef>
#include <string>

#include <utils.hpp>

class QCPItemText;
class QCPItemRect;

namespace pcpp {

  template<typename ItemPtr, typename D>
    class ShapeBase : public D {
      public:
        auto pen(const Color&)   -> D&;
        auto pen(int,int,int)    -> D&;
        auto brush(const Color&) -> D&;
        auto brush(int,int,int)  -> D&;
    };

  class TextImpl {
    public:
      TextImpl(QCPItemText*);
      auto width()  -> double;
      auto height() -> double;
      auto font(const std::string&, int) -> TextImpl&;
      auto align(const AlignFlags&)      -> TextImpl&;
      auto rotate(double)                -> TextImpl&;
      auto color(const Color&)           -> TextImpl&;
      auto color(int,int,int)            -> TextImpl&;

    protected:
      QCPItemText* _data;
  };

  class RectangleImpl {
    public:
      RectangleImpl(QCPItemRect*);
    protected:
      QCPItemRect* _data;
  };

  using Rectangle = ShapeBase<QCPItemRect*, RectangleImpl>;
  using Text = ShapeBase<QCPItemText*, TextImpl>;


} /* end of namespace pcpp */
