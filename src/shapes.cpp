#include <utils.hpp>
#include <shapes.hpp>

#include <qcustomplot.h>

namespace pcpp {

  template<typename ItemPtr, typename D>
    ShapeBase<ItemPtr,D>::ShapeBase(ItemPtr data) : _data{data} {  }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::pen(const Color& c) -> D& {
      this->_data->setPen(QPen(QColor{c.r, c.g, c.b}));
      return *static_cast<D*>(this);
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::pen(int r, int g, int b) -> D& {
      this->_data->setPen(QPen(QColor{r, g, b}));
      return *static_cast<D*>(this);
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::brush(const Color& c) -> D& {
      this->_data->setBrush(QBrush(QColor{c.r, c.g, c.b}));
      return *static_cast<D*>(this);
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::brush(int r, int g, int b) -> D& {
      this->_data->setBrush(QBrush(QColor{r, g, b}));
      return *static_cast<D*>(this);
    }

  Text::Text(QCPItemText* data) : ShapeBase<QCPItemText*,Text>{data} {  }

  auto Text::font(const std::string& font_name, int size) -> Text& {
    this->_data->setFont(QFont(font_name.c_str(), size));
    return *this;
  }

  auto Text::color(const Color& c) -> Text& {
    this->_data->setColor(QColor(c.r, c.g, c.b));
    return *this;
  }

  auto Text::color(int r, int g, int b) -> Text& {
    this->_data->setColor(QColor(r, g, b));
    return *this;
  }

  auto Text::rotate(double degrees) -> Text& {
    this->_data->setRotation(degrees);
    return *this;
  }

  auto Text::width() -> double {
    return (this->_data->topRight->pixelPosition().x()
            - this->_data->topLeft->pixelPosition().x());
  }

  auto Text::height() -> double {
    return (this->_data->bottomRight->pixelPosition().y()
            - this->_data->topRight->pixelPosition().y());
  }

  auto Text::align(const AlignFlags& a) -> Text& {
    Qt::Alignment flags;
    if (a & Align::bottom ) { flags |= Qt::AlignBottom;  }
    if (a & Align::top    ) { flags |= Qt::AlignTop;     }
    if (a & Align::left   ) { flags |= Qt::AlignLeft;    }
    if (a & Align::hcenter) { flags |= Qt::AlignHCenter; }
    if (a & Align::center ) { flags |= Qt::AlignCenter;  }
    if (a & Align::right  ) { flags |= Qt::AlignRight;   }
    this->_data->setPositionAlignment(flags);
    return *this;
  }

  Rectangle::Rectangle(QCPItemRect* data) : ShapeBase<QCPItemRect*,Rectangle>{data} {  }

  template auto ShapeBase<QCPItemRect*,Rectangle>::pen(const Color&)   -> Rectangle&;
  template auto ShapeBase<QCPItemRect*,Rectangle>::pen(int,int,int)    -> Rectangle&;
  template auto ShapeBase<QCPItemRect*,Rectangle>::brush(const Color&) -> Rectangle&;
  template auto ShapeBase<QCPItemRect*,Rectangle>::brush(int,int,int)  -> Rectangle&;

  template auto ShapeBase<QCPItemText*,Text>::pen(const Color&)   -> Text&;
  template auto ShapeBase<QCPItemText*,Text>::pen(int,int,int)    -> Text&;
  template auto ShapeBase<QCPItemText*,Text>::brush(const Color&) -> Text&;
  template auto ShapeBase<QCPItemText*,Text>::brush(int,int,int)  -> Text&;

} /* end of namespace pcpp */
