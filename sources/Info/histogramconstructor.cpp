#include "../../headers/Info/histogramconstructor.h"

/* implementation of the explicit constructor */
HistogramConstructor::HistogramConstructor(QWidget *parent) :
    QWidget(parent)
{
    resize(500, 400);
    setWindowTitle(QString::fromUtf8("Histogram"));

    customPlot = new QCustomPlot(this);
    vBoxLayout = new QVBoxLayout(this);

    vBoxLayout->addWidget(customPlot);
    setLayout(vBoxLayout);
}

/* implementation of the virtual destructor */
HistogramConstructor::~HistogramConstructor()
{
    customPlot->deleteLater();
    vBoxLayout->deleteLater();
    fossil->deleteLater();
}

/* implementation of the method which allows to create and demonstrate a histogram */
void HistogramConstructor::showHistogram(const QVector<double> & metrics, const QVector<int> & path)
{
    fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(fossil);

    QPen pen;

    pen.setWidthF(1.5);
    pen.setColor(QColor(50, 50, 100));

    fossil->setName(QString::fromUtf8("Histogram"));
    fossil->setPen(pen);
    fossil->setBrush(QColor(50, 50, 250, 70));

    // setting up values for x axis

    QVector<double> ticks;
    QVector<QString> labels;

    // setting up ticks
    for (int i=0; i < metrics.size(); i++)
        ticks.append(i+1);

    // setting up labels
    for (int i=0; i < path.size()-1; i++)
        labels.append(QString::number(path[i]+1)+"->"+QString::number(path[i+1]+1));

    customPlot->xAxis->setAutoTicks(false);
    customPlot->xAxis->setAutoTickLabels(false);
    customPlot->xAxis->setTickVector(ticks);
    customPlot->xAxis->setTickVectorLabels(labels);
    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->setRange(0, metrics.size()+1);

    // setting up values for y axis

    customPlot->yAxis->setRange(0, 1);
    customPlot->yAxis->setPadding(5);
    customPlot->yAxis->setLabel(QString::fromUtf8("Metrics of edges"));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // setting up data for histogram

    fossil->setData(ticks, metrics);

    // setting up the legend

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));

    QPen legendPen;

    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->replot();
}

/* implementation of the method which allows to save created histogram as png file */
void HistogramConstructor::saveHistogram(QString name)
{
    if (name.contains(".png"), Qt::CaseSensitive)
        customPlot->savePng(name, 800, 600, 1.0, -1);

    else if (name.contains(".jpg"), Qt::CaseSensitive)
        customPlot->saveJpg(name, 800, 600, 1.0, -1);

    else
        QMessageBox::warning(this, "Writting Fail", "Histogram hasn't been saved!");
}

/* implementation of the method which allows to clear all settings for histogram */
void HistogramConstructor::clearHistogram()
{
    this->customPlot->removePlottable(fossil);
}