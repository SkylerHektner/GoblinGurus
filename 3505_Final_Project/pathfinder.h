#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>

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
};
#endif // PATHFINDER_H
