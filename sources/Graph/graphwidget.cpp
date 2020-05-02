#include "../../headers/Graph/graphwidget.h"
#include "../../headers/Graph/edge.h"
#include "../../headers/Graph/node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));
    this->scene = new QGraphicsScene(this);
    this->info = new Instructions();
    this->histogram = new HistogramConstructor();
    this->isGraphLoaded = false;

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
    info->deleteLater();
    histogram->deleteLater();
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    keyboardSequence += event->key();

    if (event->key() == Qt::Key_Backspace)
        keyboardSequence = Qt::Key_Backspace;

    switch (keyboardSequence) {
        // zomm In if keyboard sequence equal Key_Plus
        case Qt::Key_Plus: {
            zoomIn();
            keyboardSequence = 0;
            break;
        }
        // zomm Out if keyboard sequence equal Key_Minus
        case Qt::Key_Minus: {
            zoomOut();
            keyboardSequence = 0;
            break;
        }
        // scene which allows to see instructions of using app
        case Qt::Key_H + Qt::Key_E + Qt::Key_L + Qt::Key_P: {
            info->showInstructions();
            keyboardSequence = 0;
            break;
        }
        // deleting of keyboard sequence if has been pressed Key_BackSpace
        case Qt::Key_Backspace: {
            keyboardSequence = 0;
            break;
        }
        // stopping of execution
        case Qt::Key_E + Qt::Key_X + Qt::Key_I + Qt::Key_T: {
            exit(0);
        }
        // clearing of main scene if has been entered next key word
        case Qt::Key_C + Qt::Key_L + Qt::Key_O + Qt::Key_S + Qt::Key_E: {
            this->cdn->resetSettings();
            this->vectorEdges.clear();
            this->vectorNodes.clear();
            scene->clear();
            keyboardSequence = 0;
            isGraphLoaded = false;
            break;
        }
        // setting up of default color for edges
        case Qt::Key_C + Qt::Key_L + Qt::Key_E + Qt::Key_A + Qt::Key_R: {
            keyboardSequence = 0;

            if (!isGraphLoaded) break;

            for (auto &edge : vectorEdges) {
                    edge->setColor("gray");
                    edge->update();
            }

            break;
        }
        // mixing of nodes if has been entered next key word
        case Qt::Key_S + Qt::Key_H + Qt::Key_U + Qt::Key_F + Qt::Key_F + Qt::Key_L + Qt::Key_E: {
            shuffle();
            keyboardSequence = 0;
            break;
        }
        // saving graph configuration if has been entered next key word
        case Qt::Key_S + Qt::Key_A + Qt::Key_V + Qt::Key_E: {
            keyboardSequence = 0;

            if (!isGraphLoaded) {
                QMessageBox::critical(nullptr, "Fail", tr("File has not been loaded!"));
                break;
            }

            QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file for write graph"), "", tr("Files (*.json)"));

            if (fileName.isEmpty()) {
                QMessageBox::critical(nullptr, "Fail", "File has not been opened!");
                keyboardSequence = 0;
                return;
            }

            JsonWriter::writeToJson(vectorNodes, fileName);
            break;
        }
        // opening configuration file and read from it all information for future building of graph
        case Qt::Key_O + Qt::Key_P + Qt::Key_E + Qt::Key_N: {
            keyboardSequence = 0;

            if (!vectorNodes.isEmpty() and !vectorEdges.isEmpty()) {
                QMessageBox::critical(nullptr, "Fail", "File is already opened!");
                break;
            }

            QString fileName = QFileDialog::getOpenFileName(this, tr("Choose graph file"), "", tr("Files (*.json)"));

            if (fileName.isEmpty()) {
                QMessageBox::critical(nullptr, "Fail", "File has not been opened!");
                break;
            }

            JsonReader::readFromJson(fileName, vectorNodes, vectorEdges);

            for (int i=0; i < vectorNodes.size(); i++)
                scene->addItem(vectorNodes[i]);

            for (int i=0; i < vectorEdges.size(); i++)
                scene->addItem(vectorEdges[i]);

            this->count = vectorNodes.size();
            isGraphLoaded = true;
            break;
        }
        // calculating delivery path if has been entered next key word
        case Qt::Key_C + Qt::Key_A + Qt::Key_L + Qt::Key_C: {
            keyboardSequence = 0;

            if (!isGraphLoaded) {
                QMessageBox::critical(this, "Opening Fail", "File has not been opened!");
                break;
            }

            bool ok;

            QString text = QInputDialog::getText(
                        this,
                        tr("Source and Destonation nodes"),
                        tr("Source and Destonation nodes: "),
                        QLineEdit::Normal,
                        "",
                        &ok);

            QStringList nodesSrcDst = text.split(",");

            if (nodesSrcDst.size() == 2 && nodesSrcDst[0].toInt() && nodesSrcDst[1].toInt()) {
                int srcNode = nodesSrcDst[0].toInt();
                int dstNode = nodesSrcDst[1].toInt();

                if ((srcNode > 0 && srcNode <= count) && (dstNode > 0 && dstNode <= count)) {
                    // clearing of found paths on the graph
                    for (auto &edge : vectorEdges) {
                        edge->setColor("gray");
                        edge->update();
                    }

                    cdn->getMatrix().setRowsCount(vectorNodes.size());
                    cdn->getMatrix().setColsCount(vectorNodes.size());
                    cdn->getMatrix().transformFrom(vectorEdges);

                    // final path of graph with the best metric for delivery
                    QVector<int> path = cdn->findPath(srcNode-1, dstNode-1);

                    if (!path.size())
                        QMessageBox::warning(this, "Path Error", "All paths are loaded!");

                    else {
                        // looking for edge in vectorEdges by received path of nodes
                        for (int i=0; i < path.size()-1; i++) {
                            for (auto &edge : vectorEdges) {
                                // if edge painted from lower node to greater node
                                if (edge->sourceNode()->name == QString::number(path[i]+1) && edge->destNode()->name == QString::number(path[i+1]+1)) {
                                    edge->setColor("red");
                                    edge->update();

                                    QTime time;
                                    time.start();
                                    while (time.elapsed() != 500) QCoreApplication::processEvents();
                                    edge->setMetric(QString::number(edge->getMetric().toDouble()-0.1));
                                    edge->update();
                                }

                                // if edge painted from greater node to lower node
                                else if (edge->sourceNode()->name == QString::number(path[i+1]+1) && edge->destNode()->name == QString::number(path[i]+1)) {
                                    edge->setColor("red");
                                    edge->update();

                                    QTime time;
                                    time.start();
                                    while (time.elapsed() != 500) QCoreApplication::processEvents();
                                    edge->setMetric(QString::number(edge->getMetric().toDouble()-0.1));
                                    edge->update();
                                }
                            }
                        }
                    }
                }

                else {
                    QMessageBox::warning(this, "Nodes Error", "Numbers of nodes cannot exceed count of nodes in Graph!");
                }
            }

            else {
                QMessageBox::critical(this, "Input Error", "Write only two numbers!");
            }

            break;
        }
        // showing of the histogram
        case Qt::Key_H + Qt::Key_I + Qt::Key_S + Qt::Key_T + Qt::Key_O + Qt::Key_G + Qt::Key_R + Qt::Key_A + Qt::Key_M: {
            keyboardSequence = 0;

            if (!isGraphLoaded) {
                QMessageBox::critical(this, "Opening Fail", "File has not been opened!");
                break;
            }

            else if (cdn->getLastFoundPath().isEmpty()) {
                QMessageBox::critical(this, "Showing Fail", "Calculating hasn't been done!");
                break;
            }

            cdn->calcMetricsOfLastFoundPath();

            QVector<double> metrics = cdn->getMetricsOfLastFoundPath();
            QVector<int> path = cdn->getLastFoundPath();

            this->histogram->showHistogram(cdn->getMetricsOfLastFoundPath(), cdn->getLastFoundPath());
            this->histogram->saveHistogram("histogram "+QDateTime::currentDateTime().toString()+".png");
            this->histogram->show();
            this->histogram->clearHistogram();
            break;
        }
        // changing metrics via random
        case Qt::Key_R + Qt::Key_A + Qt::Key_N + Qt::Key_D: {
            keyboardSequence = 0;

            if (!isGraphLoaded) {
                QMessageBox::critical(this, "Opening Fail", "File has not been opened!");
                break;
            }

            this->cdn->resetSettings();

            for (auto & edge : vectorEdges) {
                double min = 0.2;
                double max = 0.9;
                double value = static_cast<double>(rand())/RAND_MAX*(max - min) + min;

                edge->setMetric(QString::number(value, 'g', 2));

                edge->setColor("gray");
                edge->update();
            }

            break;
        }
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
