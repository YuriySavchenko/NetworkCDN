#ifndef HISTOGRAM_CONSTRUCTOR_H
#define HISTOGRAM_CONSTRUCTOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QVector>
#include <QPen>

/* including of the qcustomplot class */
#include "../QCustomPlot/qcustomplot.h"

//!
//! \brief The HistogramConstructor class \n
//! \b HistogramConstructor - class which presents \a mechanism for creating \b histograms \n
//! \b HistogramConstructor allows to create a histogram and work with it by simple functions \n
//!
class HistogramConstructor : public QWidget
{

    Q_OBJECT

public:
    explicit HistogramConstructor(QWidget *parent = nullptr);       //!< The explicit \e constructor
    virtual ~HistogramConstructor();                                //!< The \e virtual \e destructor

private:
    QCustomPlot *customPlot;        //!< The \e object which presents scene of \a QCustomPlot
    QVBoxLayout *vBoxLayout;        //!< The \e object which presents \b Vertical \b Layout
    QCPBars *fossil;                //!< The \e plottable representing a \b bar \b chart in a \b plot.

public:
    void showHistogram(const QVector<double> &, const QVector<int> &);      //!< The \e method which allows to show the final \b histogram
    void saveHistogram(QString);                                            //!< The \e method which allows to save the \b histogram as \a PNG
    void clearHistogram();                                                  //!< The \e method which allows to clear all settings for \b histogram
};

#endif // HISTOGRAM_CONSTRUCTOR_H