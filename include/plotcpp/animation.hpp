#pragma once

#include <plotcpp/animation_widget.hpp>

namespace pcpp {

	class Animation {
		private:
			int                           _argc;
			char**                        _argv;
			std::shared_ptr<QApplication> _app;
			AnimationWidget               _animation;

		public:
			Animation(int,char**,std::size_t,std::size_t);

			int start();
			void init(const std::function<void(PlotWidget&)>&);
			void add (int msec, const AnimationWidget::Action&);
	};

} /* end of namespace pcpp */
