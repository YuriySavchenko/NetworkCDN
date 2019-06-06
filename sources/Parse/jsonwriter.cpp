#include "../../headers/Parse/jsonwriter.h"

/* implementation of explicit constructor for saving name */
JsonWriter::JsonWriter(const QString &name)
{
    this->name = name;
}

/* implementation of explicit constructor for saving nodes */
JsonWriter::JsonWriter(const QVector<Node *> &nodes)
{
    this->nodes = nodes;
}

/* implementation of explicit constructor for saving name and nodes */
JsonWriter::JsonWriter(const QString &name, const QVector<Node *> &nodes)
{
    this->name = name;
    this->nodes = nodes;
}

/* implementation of method for writing into json file */
void JsonWriter::writeToJson()
{
    writeToJson(this->nodes, this->name);
}

/* implementation of method for writing into json file by QVector nodes */
void JsonWriter::writeToJson(const QVector<Node *> &nodes)
{
    writeToJson(nodes, this->name);
}

/* implementation of method for writing into { name }.json byf QVector nodes */
void JsonWriter::writeToJson(const QVector<Node *> nodes, const QString &name)
{
    QJsonDocument json;
    QVariantList listJsonNodes;
    QVariantMap mapJsonNodes;

    if (nodes.size() >= 1) {
        for (int i=0; i < nodes.size(); i++) {
            QVariantMap node;
            QVariantList edges;

            for (int j=0; j < nodes[i]->edges().size(); j++) {
                if (nodes[i]->name != nodes[i]->edges()[j]->destNode()->name) {
                    QVariantMap edge;
                    edge.insert("source", nodes[i]->name);
                    edge.insert("target", nodes[i]->edges()[j]->destNode()->name);
                    edge.insert("metric", nodes[i]->edges()[j]->getMetric());
                    edges.append(edge);
                }
            }

            node.insert("name", nodes[i]->name);
            node.insert("x", nodes[i]->pos().rx());
            node.insert("y", nodes[i]->pos().ry());
            node.insert("edges", edges);

            listJsonNodes.append(node);
        }

        mapJsonNodes.insert("nodes", listJsonNodes);
    }

    QFile file(name);

    if (file.open(QIODevice::WriteOnly))
        file.write(json.fromVariant(mapJsonNodes).toJson());
    else
        QMessageBox::critical(nullptr, "Fail", "File has not been opened!");

    file.close();
}

/* implementation method for setting value for { name } of file */
void JsonWriter::setName(const QString &name)
{
    this->name = name;
}

/* implementation method for setting value for QVector { nodes } */
void JsonWriter::setNodes(const QVector<Node *> &nodes)
{
    this->nodes = nodes;
}
