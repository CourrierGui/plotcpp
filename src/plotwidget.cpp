#include <plotcpp/plotwidget.hpp>

#include <qcustomplot.h>
#include <QHBoxLayout>

namespace pcpp {

	PlotWidget::PlotWidget(
		std::size_t rows, std::size_t cols,
		QWidget* parent)
		: QWidget{parent},
		_plot{std::make_shared<QCustomPlot>(new QCustomPlot{this})},
		_rows{rows}, _cols{cols},
		_row{0},     _col{0},
		_plots{}
	{
		QHBoxLayout* hlayout = new QHBoxLayout;
		setLayout(hlayout);
		hlayout->addWidget(&*_plot);
		QCPLayoutGrid* layout = _plot->plotLayout();
		layout->clear();
		_plot->setAutoAddPlottableToLegend(false);

		for (std::size_t i=0; i<rows; ++i) {
			for (std::size_t j=0; j<cols; ++j) {
				auto* grid = new QCPLayoutGrid;
				auto* text = new QCPTextElement(
					&*_plot, "",
					QFont("sans", 24/rows, QFont::Bold)
				);

				auto* axis = new QCPAxisRect(&*_plot);

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

	PlotWidget::~PlotWidget() {  }

	auto PlotWidget::plot(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
		-> Graph
	{
		auto* axis = get_axis();
		auto* graph = new QCPGraph(
			axis->axis(QCPAxis::atBottom),
			axis->axis(QCPAxis::atLeft)
		);
		_plots[graph] = "graph";

		std::size_t index
			= get_axis()->axis(QCPAxis::atBottom)->plottables().size();
		auto c = Color::next(index);
		graph->setPen(QPen(QColor(c.r, c.g, c.b)));
		graph->setData(
			QVector<double>{x.begin(), x.end()},
			QVector<double>{y.begin(), y.end()}
		);
		graph->setName(label.c_str());

		add_to_legend(axis, graph);
		_plot->rescaleAxes();
		return Graph{graph};
	}

	auto PlotWidget::hist(
		const std::vector<double>& x,
		const std::vector<double>& y,
		const std::string& label)
		-> Hist
	{
		auto* axis = get_axis();
		auto* data = new QCPBars(
			axis->axis(QCPAxis::atBottom),
			axis->axis(QCPAxis::atLeft)
		);
		_plots[data] = "bars";

		data->setAntialiased(false);
		data->setName(label.c_str());

		std::size_t index
			= get_axis()->axis(QCPAxis::atBottom)->plottables().size();
		auto c = Color::next(index);

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
		_plot->rescaleAxes();
		return Hist{data};
	}

	void PlotWidget::at(std::size_t row, std::size_t col) {
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

	void PlotWidget::title(const std::string& name) {
		auto* layout = get_layout();
		auto* text = dynamic_cast<QCPTextElement*>(layout->element(0, 0));
		text->setText(name.c_str());
	}

	void PlotWidget::xlabel(const std::string& label) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atBottom)->setLabel(label.c_str());
	}

	void PlotWidget::ylabel(const std::string& label) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atLeft)->setLabel(label.c_str());
	}

	void PlotWidget::legend() {
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

	void PlotWidget::clear() {
		auto* axis = get_axis();
		for (auto plot: axis->axis(QCPAxis::atBottom)->plottables()) {
			_plot->removePlottable(plot);
		}
		auto* leg = dynamic_cast<QCPLegend*>(axis->insetLayout()->elementAt(0));
		if (leg != nullptr) {
			axis->insetLayout()->remove(leg);
		}
	}

	void PlotWidget::add_to_legend(
		QCPAxisRect* axis,
		QCPAbstractPlottable* plot)
	{
		if (auto* element=axis->insetLayout()->elementAt(0); element != nullptr)
		{
			auto* legend = dynamic_cast<QCPLegend*>(element);
			legend->addItem(new QCPPlottableLegendItem(legend, plot));
		}
	}

	void PlotWidget::update_rect(
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

		Range rng{
			std::min(xrange.lower, *xmin-dmin),
			std::max(xrange.upper, *xmax+dmax),
			std::min(yrange.lower, *ymin),
			std::max(yrange.upper, *ymax)
		};
		range(rng);
	}

	auto PlotWidget::color() const -> Color {
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
				case 0:  r=v, g=t, b=p; break;
				case 1:  r=q, g=v, b=p; break;
				case 2:  r=p,g=v,b=t; break;
				case 3:  r=p,g=q,b=v; break;
				case 4:  r=t,g=p,b=v; break;
				case 5:  r=v,g=p,b=q; break;
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


	auto PlotWidget::get_layout() const -> QCPLayoutGrid* {
		auto* layout = _plot->plotLayout();
		return dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
	}

	auto PlotWidget::get_layout() -> QCPLayoutGrid* {
		auto* layout = _plot->plotLayout();
		return dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
	}

	auto PlotWidget::get_axis() const -> QCPAxisRect* {
		auto* layout = _plot->plotLayout();
		auto* plot_layout
			= dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
		return dynamic_cast<QCPAxisRect*>(plot_layout->element(1, 0));
	}

	auto PlotWidget::get_axis() -> QCPAxisRect* {
		auto* layout = _plot->plotLayout();
		auto* plot_layout
			= dynamic_cast<QCPLayoutGrid*>(layout->element(_row, _col));
		return dynamic_cast<QCPAxisRect*>(plot_layout->element(1, 0));
	}

	void PlotWidget::range(const Range& r) {
		auto* axis = get_axis();
		axis->axis(QCPAxis::atBottom)->setRange(r.xmin, r.xmax);
		axis->axis(QCPAxis::atLeft)->setRange(r.ymin, r.ymax);
	}

} /* end of namespace pcpp */
