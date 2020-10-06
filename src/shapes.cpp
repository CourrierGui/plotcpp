#include <utils.hpp>
#include <shapes.hpp>

#include <qcustomplot.h>

namespace pcpp {

	template<typename ItemPtr>
		ShapeBase<ItemPtr>::ShapeBase(ItemPtr ptr) : _data{ptr} {  }

	template<typename ItemPtr>
		auto ShapeBase<ItemPtr>::pen(const Color& c) -> ShapeBase<ItemPtr>& {
			_data->setPen(QPen(QColor{c.r, c.g, c.b}));
			return *this;
		}

	template<typename ItemPtr>
	auto ShapeBase<ItemPtr>::pen(int r, int g, int b) -> ShapeBase<ItemPtr>& {
		_data->setPen(QPen(QColor{r, g, b}));
		return *this;
	}

	template<typename ItemPtr>
	auto ShapeBase<ItemPtr>::brush(const Color& c) -> ShapeBase<ItemPtr>& {
		_data->setBrush(QBrush(QColor{c.r, c.g, c.b}));
		return *this;
	}

	template<typename ItemPtr>
	auto ShapeBase<ItemPtr>::brush(int r, int g, int b) -> ShapeBase<ItemPtr>& {
		_data->setBrush(QBrush(QColor{r, g, b}));
		return *this;
	}

	Text::Text(QCPItemText* data) : ShapeBase<QCPItemText*>{data} {  }

	auto Text::font(const std::string& font_name, int size) -> Text& {
		_data->setFont(QFont(font_name.c_str(), size));
		return *this;
	}

	auto Text::color(const Color& c) -> Text& {
		_data->setColor(QColor(c.r, c.g, c.b));
		return *this;
	}

	auto Text::color(int r, int g, int b) -> Text& {
		_data->setColor(QColor(r, g, b));
		return *this;
	}

	auto Text::rotate(double degrees) -> Text& {
		_data->setRotation(degrees);
		return *this;
	}

	auto Text::width() -> double {
		return (_data->topRight->pixelPosition().x()
					- _data->topLeft->pixelPosition().x());
	}

	auto Text::height() -> double {
		return (_data->bottomRight->pixelPosition().y()
					- _data->topRight->pixelPosition().y());
	}

	auto Text::align(const AlignFlags& a) -> Text& {
		Qt::Alignment flags;
		if (a & Align::bottom ) { flags |= Qt::AlignBottom;  }
		if (a & Align::top    ) { flags |= Qt::AlignTop;     }
		if (a & Align::left   ) { flags |= Qt::AlignLeft;    }
		if (a & Align::hcenter) { flags |= Qt::AlignHCenter; }
		if (a & Align::center ) { flags |= Qt::AlignCenter;  }
		if (a & Align::right  ) { flags |= Qt::AlignRight;   }
		_data->setPositionAlignment(flags);
		return *this;
	}

	Rectangle::Rectangle(QCPItemRect* data) : ShapeBase<QCPItemRect*>{data} {  }

	template class ShapeBase<QCPItemText*>;
	template class ShapeBase<QCPItemRect*>;

} /* end of namespace pcpp */
