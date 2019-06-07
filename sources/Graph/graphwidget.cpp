#include "../../headers/Graph/graphwidget.h"
#include "../../headers/Graph/edge.h"
#include "../../headers/Graph/node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    this->scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(800, 600);
    setWindowTitle(tr("Content Delivery Network"));

    // CDN initialization
    this->cdn = new CDN();
}

GraphWidget::~GraphWidget()
{
    delete cdn;

    for (auto &edge : vectorEdges)
        delete edge;

    for (auto &node : vectorNodes)
        delete node;

    scene->deleteLater();
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    keyboardSequence += event->key();

    if (event->key() == Qt::Key_Backspace)
        keyboardSequence = Qt::Key_Backspace;

    switch (keyboardSequence) {
        // zomm In if keyboard sequence equal Key_Plus
        case Qt::Key_Plus:
            zoomIn();
            keyboardSequence = 0;
            break;
        // zomm Out if keyboard sequence equal Key_Minus
        case Qt::Key_Minus:
            zoomOut();
            keyboardSequence = 0;
            break;
        // deleting of keyboard sequence if has been pressed Key_BackSpace
        case Qt::Key_Backspace:
            keyboardSequence = 0;
            break;
        // clearing of main scene if has been entered next key word
        case Qt::Key_C + Qt::Key_L + Qt::Key_E + Qt::Key_A + Qt::Key_R:
            this->vectorEdges.clear();
            this->vectorNodes.clear();
            scene->clear();
            keyboardSequence = 0;
            break;
        // mixing of nodes if has been entered next key word
        case Qt::Key_S + Qt::Key_H + Qt::Key_U + Qt::Key_F + Qt::Key_F + Qt::Key_L + Qt::Key_E:
            shuffle();
            keyboardSequence = 0;
            break;
        // saving graph configuration if has been entered next key word
        case Qt::Key_S + Qt::Key_A + Qt::Key_V + Qt::Key_E:
            JsonWriter::writeToJson(vectorNodes, "config.json");
            keyboardSequence = 0;
            break;
        // opening configuration file and read from it all information for future building of graph
        case Qt::Key_O + Qt::Key_P + Qt::Key_E + Qt::Key_N:
            if (vectorNodes.isEmpty() and vectorEdges.isEmpty()) {
                JsonReader::readFromJson("config.json", vectorNodes, vectorEdges);

                for (int i=0; i < vectorNodes.size(); i++)
                    scene->addItem(vectorNodes[i]);

                for (int i=0; i < vectorEdges.size(); i++)
                    scene->addItem(vectorEdges[i]);
            }

            else {
                QMessageBox::critical(nullptr, "Fail", "File is already opened!");
            }

            keyboardSequence = 0;
            break;
        // calculating delivery path if has been entered next key word
        case Qt::Key_C + Qt::Key_A + Qt::Key_L + Qt::Key_C:
            cdn->setEdges(vectorEdges);
            cdn->getMatrix().setRow(vectorNodes.size());
            cdn->getMatrix().setCol(vectorNodes.size());
            cdn->getMatrix().transformFrom(cdn->getEdges());
            keyboardSequence = 0;
            break;
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-350 + QRandomGenerator::global()->bounded(700), -350 + QRandomGenerator::global()->bounded(700));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}