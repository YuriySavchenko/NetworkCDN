#include "../../headers/CDN/cdn.h"

/* implementation of basic constructor */
CDN::CDN()
{

}

/* implementation of explicit constructor */
CDN::CDN(const QVector<Edge *> &edges)
    : edges(edges)
{

}

/* implementation of destructor */
CDN::~CDN()
{

}

/* implementation of function which allows get vector of edges */
QVector<Edge *>& CDN::getEdges()
{
    return this->edges;
}

/* implementation of function which allows get matrix */
Matrix &CDN::getMatrix()
{
    return this->matrix;
}

/* implementation of method for saving vector of edges */
void CDN::setEdges(const QVector<Edge *> &edges)
{
    this->edges = edges;
}

/* implementation of method for saving matrix */
void CDN::setMatrix(const Matrix &matrix)
{
    this->matrix = matrix;
}
