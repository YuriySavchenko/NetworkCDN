#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
    Edge();
    Edge(Node *sourceNode, Node *destNode, const QString &weight);

    Node *sourceNode() const;
    Node *destNode() const;

    void adjust();
    const QString getMetric();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    void setColor(const QString &);
    void setPenWidth(const int &);
    void setMetric(const QString &);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    QString metric;

    QString color {"gray"};
    int penWidth {1};
};

#endif // EDGE_H
