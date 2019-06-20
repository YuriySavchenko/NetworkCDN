#include "../../headers/CDN/cdn.h"

/* implementation of basic constructor */
CDN::CDN()
{

}

/* implementation of explicit constructor */
CDN::CDN(const QVector<Edge *> &edges)
    : edges(edges)
{

}

/* implementation of destructor */
CDN::~CDN()
{

}

/* implementation of function which allows get vector of edges */
QVector<Edge *>& CDN::getEdges()
{
    return this->edges;
}

/* implementation of function which allows get matrix */
Matrix &CDN::getMatrix()
{
    return this->matrix;
}

/* implementation of method for saving vector of edges */
void CDN::setEdges(const QVector<Edge *> &edges)
{
    this->edges = edges;
}

/* implementation of method for saving matrix */
void CDN::setMatrix(const Matrix &matrix)
{
    this->matrix = matrix;
}

/* implementation of method for adding of path to all paths */
void CDN::addPath(const QVector<int> &path)
{
    paths.push_back(path);
}

/* implementation of method which allows find all neighbors for all nodes */
QVector<int> CDN::findPaths(const int &src, const int &dst)
{
    // Mark all the vertices as not visited
    QVector<bool> visited(matrix.getRow(), false);

    // Create an array to store paths
    QVector<int> path(matrix.getRow());
    int path_index = 0;

    // Create an map which stores a lists of neighbors nodes
    QMap<int, QVector<int>> neighborsNodes;

    for (int i=0; i < matrix.getRow(); i++)
        neighborsNodes[i] = QVector<int> ();

    for (int i=0; i < matrix.getRow(); i++) {
        for (int j=0; j < matrix.getCol(); j++) {
            if (matrix.at(i, j) > 0) {
                neighborsNodes[i].append(j);
                neighborsNodes[j].append(i);
            }
        }
    }

    // Call the recursive helper function to print all paths
    findPathsUtil(src, dst, neighborsNodes, visited, path, path_index);

    // Map for saving all paths and them metric
    QMap<int, double> matchPathMetric;

    // Looking for the best optimality path for delivery
    for (int i=0; i < paths.size(); i++) {
        double sum = 0;

        // Count metric like difference between maximal value and existing
        for (int j=0; j < paths[i].size()-1; j++) {
            // If metric value places upper than diagonal
            if (matrix.at(paths[i][j], paths[i][j+1]) != 0 && matrix.at(paths[i][j+1], paths[i][j]) == 0)
                sum += 1 - matrix.at(paths[i][j], paths[i][j+1]);

            // If metric value places under diagonal
            if (matrix.at(paths[i][j], paths[i][j+1]) == 0 && matrix.at(paths[i][j+1], paths[i][j]) != 0)
                sum += 1 - matrix.at(paths[i][j+1], paths[i][j]);
        }

        matchPathMetric[i] = sum;
    }

    double min = INT_MAX;

    for (int i=0; i < paths.size(); i++)
        if (matchPathMetric[i] < min)
            min = matchPathMetric[i];

    for (int i=0; i < paths.size(); i++)
        if (matchPathMetric[i] == min)
            return paths[i];

    return QVector<int> ();
}

/* implementation of method which looking for all paths of graph between source node and destonation node */
void CDN::findPathsUtil(const int &src, const int &dst, QMap<int, QVector<int>> map, QVector<bool> &visited, QVector<int> &path, int &path_index)
{
    // Mark the current node and store it in path[]
    visited[src] = true;
    path[path_index] = src;
    path_index++;

    // If current vertex is same as destination, then add path to paths
    if (src == dst) {
        QVector<int> newPath;

        for (int i=0; i < path_index; i++)
            newPath.append(path[i]);

        addPath(newPath);
    }

    // If current vertex is not destination
    else {
        // Recur for all the vertices adjacent to current vertex
        QVector<int>::iterator itr;

        for (itr=map[src].begin(); itr != map[src].end(); ++itr)
            if (!visited[*itr])
                findPathsUtil(*itr, dst, map, visited, path, path_index);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[src] = false;
}
