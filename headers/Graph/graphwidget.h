#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QInputDialog>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDateTime>
#include <QTime>

#include "../Parse/jsonwriter.h"
#include "../Parse/jsonreader.h"
#include "../CDN/cdn.h"
#include "../Info/instructions.h"
#include "../Info/histogramconstructor.h"

class Node;
class Edge;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    virtual ~GraphWidget();

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif

    void scaleView(qreal scaleFactor);

private:
    CDN *cdn;
    Instructions *info;
    QGraphicsScene *scene;
    HistogramConstructor *histogram;

    QVector<Node *> vectorNodes;
    QVector<Edge *> vectorEdges;

    int keyboardSequence = 0;
    int count;
    bool isGraphLoaded;
};

#endif // GRAPHWIDGET_H
