#pragma once

#include <QObject>
#include <QWidget>

#include <plotcpp/plotwrapper.hpp>

class QTimer;
class QElapsedTimer;

namespace pcpp {

	class AnimationWidget : public QWidget {
		Q_OBJECT

		public:
			using Action = std::function<bool(int64_t,PlotWrapper&)>;
			using ActionList
				= std::vector<std::pair<QTimer*,Action>>;

		private:
			PlotWrapper    _plot;
			ActionList     _actions;
			bool           _continue;
			QElapsedTimer* _qtime;

		public:
			AnimationWidget(int,int,QWidget* parent=0);
			AnimationWidget(const AnimationWidget&) = delete;
			void operator=(const AnimationWidget&) = delete;

			void start();
			void init(const std::function<void(PlotWrapper&)>&);
			void add(int msec, const Action&);
	};

} /* end of namespace pcpp */
