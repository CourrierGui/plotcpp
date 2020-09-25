#pragma once

#include <QObject>
#include <QWidget>

#include <plotcpp/plotwidget.hpp>

namespace pcpp {

	class AnimationWidget : public QWidget {
		Q_OBJECT

		public:
			using Action = std::function<bool(int,PlotWidget&)>;
			using ActionList
				= std::vector<std::pair<int,Action>>;

		private:
			PlotWidget _plot;
			ActionList _actions;

		public:
			AnimationWidget(std::size_t,std::size_t,QWidget* parent=0);
			void start();
			void init(const std::function<void(PlotWidget&)>&);
			void add (int msec, const Action&);
	};

} /* end of namespace pcpp */
