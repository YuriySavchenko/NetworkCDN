#ifndef CDN_H
#define CDN_H

#include <iostream>
#include <QVector>
#include <QQueue>
#include <QDebug>
#include <QElapsedTimer>
#include <cmath>

#include "../../headers/Graph/edge.h"
#include "../../headers/CDN/matrix.h"

using ListOfTraversedPaths = QVector<QVector<int>>;

//!
//! \brief The CDN class \n
//! \b CDN - class which presents \b Content \b Delivery \b Network \n
//! \b CDN allows to save \b matrix of \b hosts and also gives access
//! calculate the shortest \e path of delivery \e packages \n
//!
class CDN
{
public:
    CDN() = default;                            //!< A \e constructor
    ~CDN() = default;                           //!< A \e destructor

private:
    Matrix matrix;                                      //!< A \e variable \b matrix for saving \b hosts

    QVector<QVector<int>> paths;                        //!< A \e variable for saving all \a paths of \b graph between \a source node and \a dest node
    QVector<int> lastFoundPath;                         //!< A \e variable for saving the last found \b path
    QVector<double> metricsOfLastFoundPath;             //!< A \e variable for saving \e list of \b metrics for the last found \b path

    ListOfTraversedPaths table;                         //!< A \e variable for saving all founded \a paths on the \b graph

public:
    Matrix& getMatrix();                                        //!< A \e function for getting \b matrix
    ListOfTraversedPaths getTable();                            //!< A \e function for getting \b table

    const QVector<int> & getLastFoundPath();                    //!< A \e function for getting the last found \b path
    const QVector<double> & getMetricsOfLastFoundPath();        //!< A \e function for getting \b metrics of the last found \b path

public:
    void setMatrix(const Matrix &);                             //!< A \e method for saving \b matrix

public:
    void addPath(const QVector<int> &path);                     //!< A \e method for saving one \a path of \b graph
    QVector<int> findPaths(const int &src, const int &dst);     //!< A \e method for searching neighbors \a nodes in \b graph

private:
    //!
    //! \brief findPathsUtil
    //! \param src
    //! \param dst
    //! \param map
    //! \param visited
    //! \param path
    //! \param path_index
    //!
    void findPathsUtil(const int &src, const int &dst, QMap<int, QVector<int>> map, QVector<bool> &visited, QVector<int> &path, int &path_index);

public:
    //!<
    //!< \brief calcMetricsOfLastFoundPath
    //!<
    void calcMetricsOfLastFoundPath();
};

#endif // CDN_H
