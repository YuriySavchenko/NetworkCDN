#include "../../headers/Graph/edge.h"
#include "../../headers/Graph/node.h"

#include <qmath.h>
#include <QPainter>

Edge::Edge()
{

}

Edge::Edge(Node *sourceNode, Node *destNode, const QString &weight)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    metric = weight;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(5.)) {
        QPointF edgeOffset((line.dx() * 20) / length, (line.dy() * 20) / length);
        QPointF tmp {10, 10};
        sourcePoint = line.p1() + edgeOffset + tmp;
        destPoint = line.p2() - edgeOffset + tmp;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

const QString Edge::getMetric()
{
    return this->metric;
}

void Edge::setColor(const QString &value)
{
    color = value;
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(QColor(color), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw weight
    painter->setPen(Qt::black);
    painter->drawText(QPointF {(sourcePoint.x()+destPoint.x())/2,
                               (sourcePoint.y()+destPoint.y())/2},
                                metric);
}
