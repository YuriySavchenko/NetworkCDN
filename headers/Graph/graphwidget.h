#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QDebug>

#include "../Parse/jsonwriter.h"
#include "../Parse/jsonreader.h"
#include "../CDN/cdn.h"

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
    QGraphicsScene *scene;
    QVector<Node *> vectorNodes;
    QVector<Edge *> vectorEdges;
    quint64 keyboardSequence = 0;
    quint64 count = 1;
};

#endif // GRAPHWIDGET_H
