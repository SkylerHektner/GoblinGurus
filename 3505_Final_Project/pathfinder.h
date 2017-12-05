#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QQueue>
#include <QString>

class Pathfinder
{
public:
    Pathfinder(std::vector<std::pair<int, int>> & collisionPoints, int width, int height);
    std::vector<std::pair<int, int>> findPath(std::vector<std::pair<int, int>> &enemyLocations, int activeEnemyIndex, int speed, double align, double approach, std::pair<int, int> playerLocation);
private:
    bool walls[10][16];
    int height;
    int width;
    void debugPrintMap(std::vector<std::pair<int, int>> & enemyLocations, std::pair<int, int> & playerLocation, std::vector<std::pair<int, int>> & path);
    void calcPlayerDistance(int playerDistance[10][16], bool walls[10][16], std::pair<int, int> playerLocation, std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BSTNodes);
    void breadthFirstDistanceCalc(int matrix[10][16], bool walls[10][16], std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BFSNodes);
    void calcAlignDistance(int alignDistance[10][16], bool walls[10][16], std::pair<int, int> playerLocation, std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BSTNodes);
    void calcPriorities(int approachMatrix[10][16], double approachFactor, int alignMatrix[10][16], double alignFactor, int speed, double resultMatrix[10][16]);
    double bestPath(std::pair<int, int> enemyLocation, double priorities[10][16], int speed);
    QString pathfind(std::pair<int, int> enemyLocation, double priorities[10][16], int speed, double valToFind);
    std::vector<std::pair<int, int>> decodeString(std::pair<int, int> enemyLocation, QString path);
};
#endif // PATHFINDER_H
