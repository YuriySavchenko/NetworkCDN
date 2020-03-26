#include "../../headers/CDN/cdn.h"

/* implementation of function which allows to get the matrix */
Matrix &CDN::getMatrix()
{
    return this->matrix;
}

/* implementation of the function which allows to get the last found path */
const QVector<int> & CDN::getLastFoundPath()
{
    return this->lastFoundPath;
}

/* implementation of the function which allows to get the metrics of the last found path */
const QVector<double> & CDN::getMetricsOfLastFoundPath()
{
    return this->metricsOfLastFoundPath;
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

/* implementation of method which allows to find all neighbors for all nodes */
QVector<int> CDN::findPath(const int &src, const int &dst)
{
    if (!mMapPaths.contains(QPair<int, int> {src, dst}) && !mMapPaths.contains(QPair<int, int> {dst, src})) {
        paths.clear();

        // Mark all the vertices as not visited
        QVector<bool> visited(matrix.getRowsCount(), false);

        // Create an array to store paths
        QVector<int> path(matrix.getRowsCount());
        int path_index = 0;

        // Create an map which stores a lists of neighbors nodes
        QMap<int, QVector<int>> neighborsNodes;

        for (int i=0; i < matrix.getRowsCount(); i++)
            neighborsNodes[i] = QVector<int> ();

        for (int i=0; i < matrix.getRowsCount(); i++) {
            for (int j=0; j < matrix.getColsCount(); j++) {
                if (matrix.at(i, j) > 0) {
                    neighborsNodes[i].append(j);
                    neighborsNodes[j].append(i);
                }
            }
        }

        // Call the recursive helper function to find all paths
        findPathsUtil(src, dst, neighborsNodes, visited, path, path_index);

        QVector<QPair<bool, QVector<int>>> markedPaths;

        for (int i=0; i < paths.size(); i++) {
            markedPaths.append(QPair<bool, QVector<int>> {false, paths[i]});
        }

        if (src < dst)
            mMapPaths[QPair<int, int> {src, dst}] = markedPaths;

        else if (dst < src)
            mMapPaths[QPair<int, int> {dst, src}] = markedPaths;
    }

    // Map for saving all paths and their metric
    QMap<int, double> matchPathMetric;
    QVector<QPair<bool, QVector<int>>> foundPaths;

    if (src < dst)
        foundPaths = mMapPaths[QPair<int, int> {src, dst}];

    else if (dst < src)
        foundPaths = mMapPaths[QPair<int, int> {dst, src}];

    for (int i=0; i < foundPaths.size(); i++) {
        for (int j=0; j < foundPaths[i].second.size()-1; j++) {
            if (matrix.at(foundPaths[i].second[j], foundPaths[i].second[j+1]) > 0.0 &&
                matrix.at(foundPaths[i].second[j], foundPaths[i].second[j+1]) <= 0.1) {
                foundPaths[i].first = true;
                break;
            }

            else if (matrix.at(foundPaths[i].second[j+1], foundPaths[i].second[j]) > 0.0 &&
                matrix.at(foundPaths[i].second[j+1], foundPaths[i].second[j]) <= 0.1) {
                foundPaths[i].first = true;
                break;
            }

        }
    }

    // Looking for the best optimality path for delivery
    for (int i=0; i < foundPaths.size(); i++) {
        if (foundPaths[i].first)
            continue;

        double sum = 0;

        // Count metric like difference between maximal value and existing
        for (int j=0; j < foundPaths[i].second.size()-1; j++) {
            // If metric value places upper than diagonal
            if (matrix.at(foundPaths[i].second[j], foundPaths[i].second[j+1])) {
                sum += 1 - matrix.at(foundPaths[i].second[j], foundPaths[i].second[j+1]);
            }
            // If metric value places under diagonal
            else if (matrix.at(foundPaths[i].second[j+1], foundPaths[i].second[j])) {
                sum += 1 - matrix.at(foundPaths[i].second[j+1], foundPaths[i].second[j]);
            }
        }

        matchPathMetric[i] = sum;
    }

    double min = INT_MAX;
    int lastFoundPathIndex = -1;

    for (const auto &key : matchPathMetric.keys())
        if (matchPathMetric[key] < min)
            min = matchPathMetric[key];

    for (int i=0; i < foundPaths.size(); i++) {
        if (matchPathMetric[i] == min && !foundPaths[i].first) {
            // saving path as last found path
            lastFoundPathIndex = i;
            this->lastFoundPath = foundPaths[i].second;
            break;
        }
    }

    if (lastFoundPathIndex == -1)
        return QVector<int> {};

    for (int i=0; i < foundPaths[lastFoundPathIndex].second.size()-1; i++) {
        if (matrix[foundPaths[lastFoundPathIndex].second[i]][foundPaths[lastFoundPathIndex].second[i+1]] > 0.1) {
            matrix.at(foundPaths[lastFoundPathIndex].second[i], foundPaths[lastFoundPathIndex].second[i+1]) =
            matrix[foundPaths[lastFoundPathIndex].second[i]][foundPaths[lastFoundPathIndex].second[i+1]]-0.1;
        }

        else if (matrix[foundPaths[lastFoundPathIndex].second[i+1]][foundPaths[lastFoundPathIndex].second[i]] > 0.1) {
            matrix.at(foundPaths[lastFoundPathIndex].second[i+1], foundPaths[lastFoundPathIndex].second[i]) =
            matrix[foundPaths[lastFoundPathIndex].second[i+1]][foundPaths[lastFoundPathIndex].second[i]]-0.1;
        }
    }

    return lastFoundPath;
}

/* implementation of method which is looking for all paths in graph between source node and destonation node */
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

/* implementation of the method that allows to calculate metrics for last found path */
void CDN::calcMetricsOfLastFoundPath()
{
    this->metricsOfLastFoundPath.clear();

    for (int i=0; i < lastFoundPath.size()-1; i++) {
        if (matrix[lastFoundPath[i]][lastFoundPath[i+1]] > 0)
            metricsOfLastFoundPath.append(matrix[lastFoundPath[i]][lastFoundPath[i+1]]);

        if (matrix[lastFoundPath[i+1]][lastFoundPath[i]] > 0)
            metricsOfLastFoundPath.append(matrix[lastFoundPath[i+1]][lastFoundPath[i]]);
    }
}

/* implementation of the method that allows to reset all settings for cdn controller */
void CDN::resetSettings()
{
    this->paths.clear();
    this->lastFoundPath.clear();
    this->metricsOfLastFoundPath.clear();
    this->mMapPaths.clear();
}
