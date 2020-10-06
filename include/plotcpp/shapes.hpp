#pragma once

#include <cstddef>
#include <string>

#include <utils.hpp>

class QCPItemText;
class QCPItemRect;

namespace pcpp {

	template<typename ItemPtr>
		class ShapeBase {
			public:
				ShapeBase(ItemPtr);
				auto pen(const Color&)   -> ShapeBase<ItemPtr>&;
				auto pen(int,int,int)    -> ShapeBase<ItemPtr>&;
				auto brush(const Color&) -> ShapeBase<ItemPtr>&;
				auto brush(int,int,int)  -> ShapeBase<ItemPtr>&;

			protected:
				ItemPtr _data;
		};

	class Text : public ShapeBase<QCPItemText*> {
		public:
			Text(QCPItemText*);
			auto font(const std::string&, int) -> Text&;
			auto width() -> double;
			auto height() -> double;
			auto align(const AlignFlags&) -> Text&;
			auto rotate(double) -> Text&;
			auto color(const Color&) -> Text&;
			auto color(int,int,int) -> Text&;
	};

	class Rectangle : public ShapeBase<QCPItemRect*> {
		public:
			Rectangle(QCPItemRect*);
	};

} /* end of namespace pcpp */
