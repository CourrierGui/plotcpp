#include <plotcpp/animation.hpp>
#include <plotcpp/animation_widget.hpp>

#include <QApplication>

namespace pcpp {

	Animation::Animation(
		int& argc, char** argv,
		int rows, int cols)
		: _argc{argc}, _argv{argv},
			_app{new QApplication{_argc, _argv}},
			_animation{new AnimationWidget{rows, cols}}
	{
	}

	void Animation::init(const std::function<void(PlotWrapper&)>& setup) {
		_animation->init(setup);
	}

	int Animation::start() {
		_animation->start();
		return _app->exec();
	}

	void Animation::add(int msec, const std::function<bool(int64_t,PlotWrapper&)>& action) {
		_animation->add(msec, action);
	}

} /* end of namespace pcpp */
