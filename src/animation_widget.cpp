#include <plotcpp/animation_widget.hpp>
#include <plotcpp/plotwidget.hpp>

#include <iostream>

#include <QElapsedTimer>
#include <QTimer>

namespace pcpp {

	AnimationWidget::AnimationWidget(
		int rows, int cols,
		QWidget* parent)
		: _plot{rows, cols, parent}, _actions{},
		_continue{true}, _qtime{new QElapsedTimer}
	{
	}

	void AnimationWidget::init(const std::function<void(PlotWrapper&)>& setup) {
		setup(_plot);
	}

	void AnimationWidget::add(int msec, const Action& action) {
		auto* timer = new QTimer{_plot.context().get()};
		timer->setInterval(msec);
		_actions.push_back({timer, action});
	}

	void AnimationWidget::start() {
		if (!_actions.empty()) {
			auto action_it = _actions.begin();
			while (action_it != _actions.end()) {
				auto action = action_it->second;
				auto* timer = action_it->first;

				if ((action_it+1) != _actions.end()) {
					auto* next_timer = (action_it+1)->first;
					QObject::connect(
						timer, &QTimer::timeout,
						[this, action, timer, next_timer]()
						{
							if (_continue) {
								int64_t time = _qtime->elapsed();
								if (_qtime->isValid()) {
								} else {
								}
								_continue = action(time, _plot);
							} else {
								timer->stop();
								_qtime->start();
								_continue = true;
								next_timer->start();
							}
						}
					);
				} else {
					QObject::connect(
						timer, &QTimer::timeout,
						[this, action, timer]()
						{
							if (_continue) {
								int64_t time = _qtime->elapsed();
								_continue = action(time, _plot);
							} else {
								timer->stop();
								_continue = true;
							}
						}
					);
				}
				++action_it;
			}
			auto* first_timer = new QTimer{_plot.context().get()};
			first_timer->setInterval(5);
			QObject::connect(
				first_timer, &QTimer::timeout,
				[first_timer, this]()
				{
					first_timer->stop();
					_actions.front().first->start();
					_qtime->start();
				}
			);
			first_timer->start();
		}
		_plot.show();
	}

} /* end of namespace pcpp */
