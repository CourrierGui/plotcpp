#pragma once

#include <memory>
#include <functional>
#include <cstddef>
#include <vector>
#include <string>

#include <plotcpp/utils.hpp>
#include <plotcpp/plotwrapper.hpp>

class QApplication;
class QWidget;

namespace pcpp {

	class PlotWidget;
	class AnimationWidget;

	class Animation {
		private:
			int&                             _argc;
			char**                           _argv;
			std::shared_ptr<QApplication>    _app;
			std::shared_ptr<AnimationWidget> _animation;

		public:
			Animation(int&,char**,int,int);
			Animation(const Animation&) = delete;
			void operator=(const Animation&) = delete;

			int start();
			void init(const std::function<void(PlotWrapper&)>&);
			void add(
				int msec,
				const std::function<bool(int64_t,PlotWrapper&)>&
			);
	};

} /* end of namespace pcpp */
