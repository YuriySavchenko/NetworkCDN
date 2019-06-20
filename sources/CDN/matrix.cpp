#include "../../headers/CDN/matrix.h"

/* implementation of default constructor */
Matrix::Matrix()
{
}

/* implementation of explicit constructor, which also gets count of nodes */
Matrix::Matrix(const int &nodes)
    : row(nodes), col(nodes)
{
    // creating matrix
    for (int i=0; i < row; i++) {
        QVector<double> tmp(col, 0);
        matrix.append(tmp);
    }
}

/* implementation of explicit constructor, which also gets count of rows and cols */
Matrix::Matrix(const int &rows, const int &cols)
    : row(rows), col(cols)
{
    // creating matrix
    for (int i=0; i < row; i++) {
        QVector<double> tmp(col, 0);
        matrix.append(tmp);
    }
}

/* implementation of function which allows transform typical list with edges into numeric matrix */
void Matrix::transformFrom(const QVector<Edge *> &edges)
{
    // creating matrix
    for (int i=0; i < row; i++) {
        QVector<double> tmp(col, 0);
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
void Matrix::setRow(const int &row)
{
    this->row = row;
}

/* implementation of method for setting value into variable col */
void Matrix::setCol(const int &col)
{
    this->col = col;
}

/* implementation of method for getting value from variable row */
int Matrix::getRow()
{
    return this->row;
}

/* implementation of method for getting value from variable col */
int Matrix::getCol()
{
    return this->col;
}
