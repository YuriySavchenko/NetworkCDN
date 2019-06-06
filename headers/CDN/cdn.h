#ifndef CDN_H
#define CDN_H

#include <iostream>
#include <QVector>

#include "../../headers/Graph/edge.h"
#include "../../headers/CDN/matrix.h"

//!
//! \brief The CDN class\n
//! \b CDN - class which presents \b Content \b Delivery \b Network \n
//! \b CDN allows save \b matrix of \b hosts and also gives access
//! calculate the shortest \e path of delivery \e packages\n
//!
class CDN
{
public:
    CDN();							//!< A \e constructor
    CDN(const QVector<Edge *> &); 	//!< A \e particular constructor with parameter list of \b edges
    ~CDN();							//!< A \e destructor

private:
    Matrix matrix;					//!< A \e variable \b matrix for saving \b hosts
    QVector<Edge *> edges;			//!< A \e variable for saving \a vector of \b edges

public:
    QVector<Edge *>& getEdges();	//!< A \e function for getting \b edges
    Matrix& getMatrix();			//!< A \e function for getting \b matrix

public:
    void setEdges(const QVector<Edge *> &);		//!< A \e method for saving \a vector of \b edges
    void setMatrix(const Matrix &);				//!< A \e method for saving \b matrix
};

#endif // CDN_H
