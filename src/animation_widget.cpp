#include <plotcpp/animation_widget.hpp>

#include <QElapsedTimer>
#include <QTimer>

namespace pcpp {

	AnimationWidget::AnimationWidget(
		std::size_t rows, std::size_t cols,
		QWidget* parent)
		: _plot{rows, cols, parent}, _actions{}
	{

	}

	void AnimationWidget::init(const std::function<void(PlotWidget&)>& setup) {
		setup(_plot);
	}

	void AnimationWidget::add(int msec, const Action& action) {
		_actions.push_back({msec, action});
	}

	void AnimationWidget::start() {
		bool _continue = true;
		if (!_actions.empty()) {
			auto* qtime = new QElapsedTimer;

			// TODO make_timers private function
			std::vector<QTimer*> timers;
			timers.reserve(_actions.size());

			for (const auto& pair: _actions) {
				auto time = pair.first;
				auto* timer = new QTimer(&_plot);
				timer->setInterval(time);
				timers.push_back(timer);
			}

			auto action_it = _actions.begin();
			auto timer_it = timers.begin();
			while (action_it != _actions.end() && timer_it != timers.end()) {
				auto action = (action_it++)->second;
				auto* timer = *timer_it;

				if ((timer_it+1) != timers.end()) {
					auto* next_timer = *(timer_it+1);
					QObject::connect(
						timer, &QTimer::timeout,
						[this, action, &_continue, timer, next_timer, &qtime]()
						{
							if (_continue) {
								int time = qtime->elapsed();
								_continue = action(time, _plot);
							} else {
								timer->stop();
								qtime->start();
								_continue = true;
								next_timer->start();
							}
						}
					);
				} else {
					QObject::connect(
						timer, &QTimer::timeout,
						[this, action, &_continue, timer, &qtime]()
						{
							if (_continue) {
								int time = qtime->elapsed();
								_continue = action(time, _plot);
							} else {
								timer->stop();
								_continue = true;
							}
						}
					);
				}
				++timer_it;
			}
			timers.front()->start();
			qtime->start();
		}
		
		_plot.show();
	}

} /* end of namespace */
