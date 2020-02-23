#include "../../headers/CDN/matrix.h"

/* implementation of explicit constructor, which also gets count of nodes */
Matrix::Matrix(const int &nodes)
    : rows(nodes), cols(nodes)
{
    // creating matrix
    for (int i=0; i < rows; i++) {
        QVector<double> tmp(cols, 0);
        matrix.append(tmp);
    }
}

/* implementation of explicit constructor, which also gets count of rows and cols */
Matrix::Matrix(const int &rows, const int &cols)
    : rows(rows), cols(cols)
{
    // creating matrix
    for (int i=0; i < rows; i++) {
        QVector<double> tmp(cols, 0);
        matrix.append(tmp);
    }
}

/* implementation of function which allows transform typical list with edges into numeric matrix */
void Matrix::transformFrom(const QVector<Edge *> &edges)
{
    // creating matrix
    for (int i=0; i < rows; i++) {
        QVector<double> tmp(cols, 0);
        matrix.append(tmp);
    }

    // filling matrix by values of metric from vector edges
    for (int i=0; i < edges.size(); i++)
        matrix[edges[i]->sourceNode()->name.toInt()-1][edges[i]->destNode()->name.toInt()-1] = edges[i]->getMetric().toDouble();
}

/* implementation of function which allows get access till particular value from matrix */
double &Matrix::at(const int &i, const int &j)
{
    return this->matrix[i][j];
}

/* implementation of overridden operator which allows return vector from particular position */
const QVector<double> Matrix::operator[](const unsigned int &i) const
{
    return this->matrix[i];
}

/* implementation of method for setting value into variable row */
void Matrix::setRowsCount(const int &rows)
{
    this->rows = rows;
}

/* implementation of method for setting value into variable col */
void Matrix::setColsCount(const int &cols)
{
    this->cols = cols;
}

/* implementation of method for getting value from variable row */
int Matrix::getRowsCount()
{
    return this->rows;
}

/* implementation of method for getting value from variable col */
int Matrix::getColsCount()
{
    return this->cols;
}
