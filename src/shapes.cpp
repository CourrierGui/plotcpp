#include <utils.hpp>
#include <shapes.hpp>

#include <qcustomplot.h>

namespace pcpp {

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::pen(const Color& c) -> ShapeBase<ItemPtr,D>& {
      this->_data->setPen(QPen(QColor{c.r, c.g, c.b}));
      return *this;
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::pen(int r, int g, int b) -> ShapeBase<ItemPtr,D>& {
      this->_data->setPen(QPen(QColor{r, g, b}));
      return *this;
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::brush(const Color& c) -> ShapeBase<ItemPtr,D>& {
      this->_data->setBrush(QBrush(QColor{c.r, c.g, c.b}));
      return *this;
    }

  template<typename ItemPtr, typename D>
    auto ShapeBase<ItemPtr, D>::brush(int r, int g, int b) -> ShapeBase<ItemPtr,D>& {
      this->_data->setBrush(QBrush(QColor{r, g, b}));
      return *this;
    }

  TextImpl::TextImpl(QCPItemText* data) : _data{data} {  }

  auto TextImpl::font(const std::string& font_name, int size) -> TextImpl& {
    this->_data->setFont(QFont(font_name.c_str(), size));
    return *this;
  }

  auto TextImpl::color(const Color& c) -> TextImpl& {
    this->_data->setColor(QColor(c.r, c.g, c.b));
    return *this;
  }

  auto TextImpl::color(int r, int g, int b) -> TextImpl& {
    this->_data->setColor(QColor(r, g, b));
    return *this;
  }

  auto TextImpl::rotate(double degrees) -> TextImpl& {
    this->_data->setRotation(degrees);
    return *this;
  }

  auto TextImpl::width() -> double {
    return (this->_data->topRight->pixelPosition().x()
            - this->_data->topLeft->pixelPosition().x());
  }

  auto TextImpl::height() -> double {
    return (this->_data->bottomRight->pixelPosition().y()
            - this->_data->topRight->pixelPosition().y());
  }

  auto TextImpl::align(const AlignFlags& a) -> TextImpl& {
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

  RectangleImpl::RectangleImpl(QCPItemRect* data) : _data{data} {  }

  template class ShapeBase<QCPItemText*, TextImpl>;
  template class ShapeBase<QCPItemRect*, RectangleImpl>;

} /* end of namespace pcpp */
