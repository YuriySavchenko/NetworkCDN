#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <QDebug>
#include <QSize>

#include "../../headers/Graph/edge.h"
#include "../../headers/Graph/node.h"

//!
//! \brief The Matrix class\n
//! \b Matrix - presents mathematic type\n
//! Main target for \b matrix it's saving all \b hosts
//! which has beed created via \a Graph \a Builder \n
//!
class Matrix
{
public:
    Matrix();                                   //!< A \e basic \a constructor
    Matrix(const int &);                        //!< A particular \e constructor with parameter \b nodes
    Matrix(const int &, const int &);           //!< A particular \e constructor with parameters \b rows and \b cols
    ~Matrix() = default;                        //!< A \e destructor

private:
    int row;                                    //!< A \e count of \b rows for matrix
    int col;                                    //!< A \e count of \b columns for matrix
    QVector<QVector<double>> matrix;            //!< A \e variable which presents this type \b matrix

public:
    void transformFrom(const QVector<Edge *> &);    //!< A \e method for transforming into \b matrix

public:
    double &at(const int &, const int &);                           //!< A \e function for getting or changing value from \b matrix
    const QVector<double> operator[](const unsigned int &) const;   //!< Overridden \e operator for getting \b vector by position

public:
    void setRow(const int &);               //!< A \e method which allows setup value for \b row
    void setCol(const int &);               //!< A \e method which allows setup value for \b col
};

#endif // MATRIX_H
