#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

#include "../Graph/node.h"
#include "../Graph/edge.h"

//!
//! \brief The JsonWriter class\n
//! \b JsonWriter it's special \e class which allows
//! write configuration of graph to \e json file.
//!
class JsonWriter
{
public:
    JsonWriter(const QString &name);                                //!< A \e constructor which save \b name of \a file
    JsonWriter(const QVector<Node *> &nodes);                       //!< A \e constructor which save list of \b nodes
    JsonWriter(const QString &name, const QVector<Node *> &nodes);  //!< A \e constructor which save \b name of \a file and list of \b nodes
    JsonWriter() = default;                                         //!< A \e default \e constructor
    ~JsonWriter() = default;                                        //!< A \e default \e destructor

public:
    void writeToJson();                                                         //!< A \e method for writing to \a json \a file
    void writeToJson(const QVector<Node *> &nodes);                             //!< A \e method for writing to \a json \a file by particular list of \b nodes
    static void writeToJson(const QVector<Node *> nodes, const QString &name);  //!< A \e method for writing to \a json \a file by particular list of \b nodes and certain \b name of \a file

public:
    void setName(const QString &name);              //!< A \e method for setting \b name of \a file into variable
    void setNodes(const QVector<Node *> &nodes);    //!< A \e method for setting \b nodes of \b graph into variable

private:
    QString name { "config.json" };     //!< A \b name of \a file for writing
    QVector<Node *> nodes;              //!< A variable for saving \b nodes of \b graph
};

#endif // JSONWRITER_H
