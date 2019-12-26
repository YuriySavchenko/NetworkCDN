#ifndef CDN_H
#define CDN_H

#include <iostream>
#include <QVector>
#include <QQueue>

#include "../../headers/Graph/edge.h"
#include "../../headers/CDN/matrix.h"

using ListOfTraversedPaths = QVector<QVector<int>>;

//!
//! \brief The CDN class\n
//! \b CDN - class which presents \b Content \b Delivery \b Network \n
//! \b CDN allows save \b matrix of \b hosts and also gives access
//! calculate the shortest \e path of delivery \e packages\n
//!
class CDN
{
public:
    CDN();                          //!< A \e constructor
    CDN(const QVector<Edge *> &);   //!< A \e particular constructor with parameter list of \b edges
    ~CDN();                         //!< A \e destructor

private:
    Matrix matrix;                  //!< A \e variable \b matrix for saving \b hosts
    QVector<Edge *> edges;          //!< A \e variable for saving \a vector of \b edges
    QVector<QVector<int>> paths;    //!< A \e variable for saving all \a paths of \b graph between \a source node and \a dest node

    ListOfTraversedPaths table;     //!< A \e variable for saving all founded \a paths on the \b graph

public:
    QVector<Edge *>& getEdges();            //!< A \e function for getting \b edges
    Matrix& getMatrix();                    //!< A \e function for getting \b matrix

public:
    void setEdges(const QVector<Edge *> &);     //!< A \e method for saving \a vector of \b edges
    void setMatrix(const Matrix &);             //!< A \e method for saving \b matrix

public:
    void addPath(const QVector<int> &path);                     //!< A \e method for saving one \a path of \b graph
    QVector<int> findPaths(const int &src, const int &dst);     //!< A \e method for searching neighbors \a nodes in \b graph

public:
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
};

#endif // CDN_H
