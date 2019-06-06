#include "../../headers/Parse/jsonreader.h"


/* implementation of explictit constructor */
JsonReader::JsonReader(const QString &name)
{
    this->name = name;
}

/* implementation of method for reading from json file into QVector<Node *> */
void JsonReader::readFromJson(QVector<Node *> &nodes, QVector<Edge *> &edges)
{
    this->readFromJson(this->name, nodes, edges);
}

/* implementation of method for reading from { name }.json file into QVector<Node *> */
void JsonReader::readFromJson(const QString &name, QVector<Node *> &nodes, QVector<Edge *> &edges)
{
    QFile file(name);
    QJsonDocument json;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString text = file.readAll();
        json = QJsonDocument::fromJson(text.toUtf8());

        QJsonArray jArray = json.object()["nodes"].toArray();

        for (int i=0; i < jArray.size(); i++) {
            QJsonObject jObj = jArray[i].toObject();
            Node *node = new Node(jObj["name"].toString());
            node->setPos(QPointF {jObj["x"].toDouble(), jObj["y"].toDouble()});
            nodes.append(node);
        }

        for (int i=0; i < jArray.size(); i++) {
            QJsonObject jObj = jArray[i].toObject();
            QJsonArray jArr = jObj["edges"].toArray();

            if (jArr.size() >= 1) {
                for (int j=0; j < jArr.size(); j++) {
                    int source = jArr[j].toObject()["source"].toString().toInt()-1;
                    int target = jArr[j].toObject()["target"].toString().toInt()-1;
                    Edge *edge = new Edge(nodes[source], nodes[target], jArr[j].toObject()["metric"].toString());
                    edges.append(edge);
                }
            }
        }
    }

    else {
        QMessageBox::critical(nullptr, "Fail", "File has not been opened");
    }
}

void JsonReader::setName(const QString &name)
{
    this->name = name;
}
