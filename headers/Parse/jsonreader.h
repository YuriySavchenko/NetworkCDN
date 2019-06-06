#ifndef JSONREADER_H
#define JSONREADER_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

#include "../Graph/node.h"
#include "../Graph/edge.h"

//!
//! \brief The JsonReader class\n
//! \b JsonReader it's special class which allows
//! read configuration from \a json \a file for
//! \b graph and print it to \a scene.
//!
class JsonReader
{
public:
    JsonReader(const QString &);            //!< A \e constructor for saving \b name of file
    JsonReader() = default;                 //!< A default \e constructor
    ~JsonReader() = default;                //!< A default \e destructor

public:
    void readFromJson(QVector<Node *> &, QVector<Edge *> &);                            //!< A \e method for reading from \a json \a file
    static void readFromJson(const QString &, QVector<Node *> &, QVector<Edge *> &);    //!< A \e method for reading from \a json \a file with particular \b name

public:
    void setName(const QString &name);      //!< A method for setting \b name of file into variable

private:
    QString name { "config.json" };         //!< A \b name of \a json \a file
};

#endif // JSONREADER_H
