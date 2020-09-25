#include <plotcpp/animation.hpp>

#include <QApplication>

namespace pcpp {

	Animation::Animation(
		int argc, char** argv,
		std::size_t rows, std::size_t cols)
		: _argc{argc}, _argv{argv},
			_app{new QApplication{_argc, _argv}},
		_animation{rows, cols}
	{

	}

	void Animation::init(const std::function<void(PlotWidget&)>& setup) {
		_animation.init(setup);
	}

	int Animation::start() {
		_animation.start();
		return _app->exec();
	}

	void Animation::add(int msec, const AnimationWidget::Action& action) {
		_animation.add(msec, action);
	}

} /* end of namespace pcpp */
