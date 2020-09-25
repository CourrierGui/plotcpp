#include <algorithm>
#include <iostream>
#include <limits>
#include <qcustomplot.h>
#include <QObject>
#include <QTimer>
#include <QApplication>

#include <plotcpp/plotcpp.hpp>

namespace sch {

	Rect::Rect(double xmin, double xmax, double ymin, double ymax)
		: xmin{xmin},xmax{xmax},ymin{ymin},ymax{ymax}
	{

	}

	Color::Color(unsigned char r,unsigned char g,unsigned char b)
		: r{r}, g{g}, b{b}
	{

	}

	Figure::Figure(
		int argc, char** argv,
		std::size_t rows, std::size_t cols)
	: _argc{argc}, _argv{argv},
		_app{new QApplication{_argc, _argv}},
		_plot{std::make_shared<QCustomPlot*>(new QCustomPlot{nullptr})},
		_rows{rows}, _cols{cols},
		_row{0}, _col{0},
		_plots{}
	{
		QApplication::setApplicationName("plot");
		QCPLayoutGrid* layout = (*_plot)->plotLayout();
		layout->clear();
		(*_plot)->setAutoAddPlottableToLegend(false);

		for (std::size_t i=0; i<rows; ++i) {
			for (std::size_t j=0; j<cols; ++j) {
				auto* grid = new QCPLayoutGrid;
				auto* text = new QCPTextElement(
					*_plot, "",
					QFont("sans", 24/rows, QFont::Bold)
				);

				auto* axis = new QCPAxisRect(*_plot);

				grid->addElement(0, 0, text);
				grid->addElement(1, 0, axis);
				layout->addElement(i, j, grid);
				layout->setLayer("background");
				grid->setLayer("main");
				text->setLayer("axes");
				axis->setLayer("axes");
			}
		}
	}

	void Figure::plot(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const Color& c,
		const std::string& label)
	{
		auto* axis = get_axis();
		auto* graph = new QCPGraph(
			axis->axis(QCPAxis::atBottom),
			axis->axis(QCPAxis::atLeft)
		);
		_plots[graph] = "graph";

		graph->setPen(QPen(QColor(c.r, c.g, c.b)));
		graph->setData(
			QVector<double>{x.begin(), x.end()},
			QVector<double>{y.begin(), y.end()}
		);
		graph->setName(label.c_str());

		add_to_legend(axis, graph);
		(*_plot)->rescaleAxes();
		/* update_rect(x, y); */
	}

	void Figure::plot(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
	{
		plot(x, y, color(), label);
	}

	void Figure::hist(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
	{
		hist(x, y, color(), label);
	}

	void Figure::hist(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const Color& c,
		const std::string& label)
	{
		auto* axis = get_axis();
		auto* data = new QCPBars(
			axis->axis(QCPAxis::atBottom),
			axis->axis(QCPAxis::atLeft)
		);
		_plots[data] = "bars";

		data->setAntialiased(false);
		data->setName(label.c_str());
		data->setPen(QPen(QColor(c.r, c.g, c.b)));
		data->setBrush(QBrush(QColor(c.r, c.g, c.b)));

		QVector<QString> labels;
		QVector<double> ticks{x.begin(),x.end()};
		for (const auto& val: x) { labels << QString::number(val); }

		QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
		textTicker->addTicks(ticks, labels);
		axis->axis(QCPAxis::atBottom)->setTicker(textTicker);
		data->setData(ticks, QVector<double>{y.begin(), y.end()});

		add_to_legend(axis, data);
		(*_plot)->rescaleAxes();
		/* update_rect(x, y, 1, 1); */
	}

	void Figure::title(const std::string& title) {
		auto* layout = get_layout();
		auto* text = dynamic_cast<QCPTextElement*>(layout->element(0, 0));
		text->setText(title.c_str());
	}

	void Figure::clear() {
		auto* axis = get_axis();
		for (auto plot: axis->axis(QCPAxis::atBottom)->plottables()) {
			(*_plot)->removePlottable(plot);
		}
		auto* leg = dynamic_cast<QCPLegend*>(axis->insetLayout()->elementAt(0));
		if (leg != nullptr) {
			axis->insetLayout()->remove(leg);
		}
	}

	void Figure::set_data(
		QCPAbstractPlottable* plt,
		const std::vector<double>& x,
		const std::vector<double>& y)
	{
		auto type = _plots[plt];
		if (type == "graph") {
			dynamic_cast<QCPGraph*>(plt)->setData(
				{x.begin(), x.end()},
				{y.begin(), y.end()}
			);
		} else if (type == "bars") {
			dynamic_cast<QCPBars*>(plt)->setData(
				{x.begin(), x.end()},
				{y.begin(), y.end()}
			);
		}
	}

	void Figure::xlabel(const std::string& label) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atBottom)->setLabel(label.c_str());
	}

	void Figure::ylabel(const std::string& label) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atLeft)->setLabel(label.c_str());
	}

	void Figure::legend() {
		auto* axis = get_axis();
		auto* legend = new QCPLegend();
		axis->insetLayout()->addElement(
			dynamic_cast<QCPLayoutElement*>(legend), Qt::AlignTop|Qt::AlignLeft
		);
		legend->setLayer("legend");

		for (auto* plot: axis->axis(QCPAxis::atBottom)->plottables()) {
			plot->addToLegend(legend);
		}
	}

	int Figure::show() const {
		(*_plot)->show();
		return QApplication::exec();
	}

	auto Figure::context() -> Plot {
		return _plot;
	}

	void Figure::update() {
		(*_plot)->replot();
		(*_plot)->update();
	}

	void Figure::at(std::size_t row, std::size_t col) {
		if (row < _rows && col < _cols) {
			_row = row;
			_col = col;
		} else {
			std::string msg{"Invalid index: Row="};
			msg += std::to_string(row);
			msg += ", Col=";
			msg += std::to_string(col);
			throw std::runtime_error(msg);
		}
	}

	void Figure::add_to_legend(
		QCPAxisRect* axis,
		QCPAbstractPlottable* plot)
	{
		if (auto* element=axis->insetLayout()->elementAt(0); element != nullptr)
		{
			auto* legend = dynamic_cast<QCPLegend*>(element);
			legend->addItem(new QCPPlottableLegendItem(legend, plot));
		}
	}

	void Figure::update_rect(
		const std::vector<double>& x,
		const std::vector<double>& y,
		int dmin, int dmax)
	{
		if (x.empty() && y.empty()) {
			return;
		}

		auto* axis = get_axis();

		QCPRange xrange = axis->axis(QCPAxis::atBottom)->range();
		QCPRange yrange = axis->axis(QCPAxis::atLeft)->range();
		auto [xmin,xmax] = std::minmax_element(x.begin(), x.end());
		auto [ymin,ymax] = std::minmax_element(y.begin(), y.end());

		Rect rect{
			std::min(xrange.lower, *xmin-dmin),
			std::max(xrange.upper, *xmax+dmax),
			std::min(yrange.lower, *ymin),
			std::max(yrange.upper, *ymax)
		};
		range(rect);
	}

	auto Figure::color() const -> Color {
		auto hsv_to_rgb = [](
			double h,
			double s,
			double v)
			-> Color
		{
			int h_i = static_cast<int>(6*h);
			double f{h*6 - h_i};
			double p{v * (1 - s)};
			double q{v * (1 - f*s)};
			double t{v * (1 - (1 - f) * s)};

			double r=0;
			double g=0;
			double b=0;
			switch (h_i) {
				case 0: r=v, g=t, b=p; break;
				case 1: r=q, g=v, b=p; break;
				case 2: r=p,g=v,b=t; break;
				case 3: r=p,g=q,b=v; break;
				case 4: r=t,g=p,b=v; break;
				case 5: r=v,g=p,b=q; break;
				default: r=0, g=0, b=0; break;
			}

			return Color{
				static_cast<unsigned char>(256*r),
				static_cast<unsigned char>(256*g),
				static_cast<unsigned char>(256*b)
			};
		};
		std::size_t index
			= get_axis()->axis(QCPAxis::atBottom)->plottables().size();
		double h = 1.0/5*index;
		return hsv_to_rgb(h, 0.5, 0.95);
	}


	auto Figure::get_layout() const -> const QCPLayoutGrid* {
		auto* layout = (*_plot)->plotLayout();
		return dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
	}

	auto Figure::get_layout() -> QCPLayoutGrid* {
		auto* layout = (*_plot)->plotLayout();
		return dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
	}

	auto Figure::get_axis() const -> const QCPAxisRect* {
		auto* layout = (*_plot)->plotLayout();
		auto* plot_layout
			= dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
		return dynamic_cast<QCPAxisRect*>(plot_layout->element(1, 0));
	}

	auto Figure::get_axis() -> QCPAxisRect* {
		auto* layout = (*_plot)->plotLayout();
		auto* plot_layout
			= dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
		return dynamic_cast<QCPAxisRect*>(plot_layout->element(1, 0));
	}

	void Figure::range(const Rect& r) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atBottom)->setRange(r.xmin, r.xmax);
		axis->axis(QCPAxis::atLeft)->setRange(r.ymin, r.ymax);
	}

	void Figure::set_ticks(
		const std::vector<double>& ticks,
		const std::vector<std::string>& labels)
	{
		QVector<QString> qlabels;
		for (const auto& val: labels) { qlabels << val.c_str(); }

		QVector<double> qticks{ticks.begin(), ticks.end()};
		auto* axis = get_axis()->axis(QCPAxis::atBottom);
		auto* ticker = dynamic_cast<QCPAxisTickerText*>(axis->ticker().get());

		if (ticker != nullptr) {
			ticker->setTicks(qticks, qlabels);
		}
	}

	Animation::Animation(
		int argc, char** argv,
		std::size_t rows, std::size_t cols)
		: _figure{argc,argv,rows,cols}, _actions{}
	{

	}

	void Animation::init(const std::function<void(Figure&)>& setup) {
		setup(_figure);
	}

	auto Animation::start() -> int {
		bool _continue = true;
		if (!_actions.empty()) {
			auto* qtime = new QElapsedTimer;

			// TODO make_timers private function
			std::vector<QTimer*> timers;
			timers.reserve(_actions.size());

			for (const auto& pair: _actions) {
				auto time = pair.second;
				auto* timer = new QTimer(*_figure.context());
				timer->setInterval(time);
				timers.push_back(timer);
			}

			auto action_it = _actions.begin();
			auto timer_it = timers.begin();
			while (action_it != _actions.end() && timer_it != timers.end()) {
				auto action = (action_it++)->first;
				auto* timer = *timer_it;

				if ((timer_it+1) != timers.end()) {
					auto* next_timer = *(timer_it+1);
					QObject::connect(
						timer, &QTimer::timeout,
						[this, action, &_continue, timer, next_timer, &qtime]()
						{
							if (_continue) {
								int time = qtime->elapsed();
								_continue = action(time, _figure);
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
								_continue = action(time, _figure);
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
		
		return _figure.show();
	}

	void Animation::add(int msec, const Action& action) {
		_actions.push_back(
			std::make_pair(
				action,
				/* std::make_shared<const Action*>(&action), */
				msec
			)
		);
	}

} /* end of namespace sch */
