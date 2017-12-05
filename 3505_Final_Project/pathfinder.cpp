#include "pathfinder.h"
#include <iostream>

Pathfinder::Pathfinder(std::vector<std::pair<int, int>> & collisionPoints, int height, int width) {
    this->height = height;
    this->width = width;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            walls[y][x] = 0;
    for (unsigned int i = 0; i < collisionPoints.size(); i++) {
        walls[collisionPoints[i].second][collisionPoints[i].first] = true;
    }
}

std::vector<std::pair<int, int>> Pathfinder::findPath(std::vector<std::pair<int, int>> & enemyLocations,
               int activeEnemyIndex, int speed, double align, double approach, std::pair<int, int> playerLocation) {
    std::vector<std::pair<int, int>> emptyVector;
    double priorities[10][16];
    int playerDistance[10][16];
    int alignDistance[10][16];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            if (walls[y][x])
                priorities[y][x] = -99;
            else if (std::pair<int, int>(x, y) == playerLocation)
                priorities[y][x] = -99;
            else
                priorities[y][x] = 0;
            playerDistance[y][x] = 0;
            alignDistance[y][x] = 0;
        }
    QQueue<std::pair<int, int>> BFSNodes;
    calcPlayerDistance(playerDistance, walls, playerLocation, playerLocation, BFSNodes);
    BFSNodes.clear();
    calcAlignDistance(alignDistance, walls, playerLocation, playerLocation, BFSNodes);
    calcPriorities(playerDistance, approach, alignDistance, align, speed, priorities);
    double find = bestPath(enemyLocations[activeEnemyIndex], priorities, speed);
    QString path = pathfind(enemyLocations[activeEnemyIndex], priorities, speed, find);
    std::vector<std::pair<int, int>> result = decodeString(enemyLocations[activeEnemyIndex], path);

    debugPrintMap(enemyLocations, playerLocation, result);

    return result;
}

std::vector<std::pair<int, int>> Pathfinder::decodeString(std::pair<int, int> enemyLocation, QString path) {
    std::vector<std::pair<int, int>> coordinates;
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    for (int i = 0; i < path.length(); i++) {
        char direction = (path.toStdString())[i];
        if (direction == 'u')
            y--;
        else if (direction == 'd')
            y++;
        else if (direction == 'l')
            x--;
        else if (direction == 'r')
            x++;
        else
            continue;
        coordinates.push_back(std::pair<int, int>(x, y));
    }

    return coordinates;
}

QString Pathfinder::pathfind(std::pair<int, int> enemyLocation, double priorities[10][16], int speed, double valToFind) {
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    if (priorities[y][x] < -90)
        return nullptr;
    if (priorities[y][x] == valToFind)
        return " ";
    if (speed == 0)
        return nullptr;
    QString returnVal = nullptr;
    if (y-1 >= 0) {
        returnVal = pathfind(std::pair<int, int>(x, y-1), priorities, speed-1, valToFind);
        if (returnVal != nullptr)
            return "u" + returnVal;
    }
    if (x+1 < width) {
        returnVal = pathfind(std::pair<int, int>(x+1, y), priorities, speed-1, valToFind);
        if (returnVal != nullptr)
            return "r" + returnVal;
    }
    if (y+1 < height) {
        returnVal = pathfind(std::pair<int, int>(x, y+1), priorities, speed-1, valToFind);
        if (returnVal != nullptr)
            return "d" + returnVal;
    }
    if (x-1 >= 0) {
        returnVal = pathfind(std::pair<int, int>(x-1, y), priorities, speed-1, valToFind);
        if (returnVal != nullptr)
            return "l" + returnVal;
    }
    return nullptr;
}

double Pathfinder::bestPath(std::pair<int, int> enemyLocation, double priorities[10][16], int speed) {
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    if (priorities[y][x] < -90)
        return -99;
    if (speed == 0)
        return priorities[y][x];
    double result = priorities[y][x];
    if (y-1 >= 0)
        result = std::max(result, bestPath(std::pair<int, int>(x, y-1), priorities, speed-1));
    if (y+1 < height)
        result = std::max(result, bestPath(std::pair<int, int>(x, y+1), priorities, speed-1));
    if (x-1 >= 0)
        result = std::max(result,  bestPath(std::pair<int, int>(x-1, y), priorities, speed-1));
    if (x+1 < width)
        result = std::max(result,  bestPath(std::pair<int, int>(x+1, y), priorities, speed-1));
    return result;
}

void Pathfinder::calcPriorities(int approachMatrix[10][16], double approachFactor, int alignMatrix[10][16], double alignFactor, int speed, double resultMatrix[10][16]) {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            if (approachMatrix[y][x] == -99 || alignMatrix[y][x] == -99)
                resultMatrix[y][x] = -99;
            else {
                resultMatrix[y][x] = approachFactor + alignFactor
                        - (approachMatrix[y][x] - 1) * approachFactor / (double) speed
                        - (alignMatrix[y][x] - 1) * alignFactor / (double) speed;
            }
        }
}

void Pathfinder::calcPlayerDistance(int playerDistance[10][16], bool walls[10][16], std::pair<int, int> playerLocation, std::pair<int, int> currentLocation, QQueue<std::pair<int, int> > &BFSNodes) {
    bool shouldLoop = (playerLocation == currentLocation);

    breadthFirstDistanceCalc(playerDistance, walls, currentLocation, BFSNodes);

    if (shouldLoop) {
        playerDistance[currentLocation.second][currentLocation.first] = -99;
        while (!BFSNodes.isEmpty()) {
            std::pair<int, int> next = BFSNodes.dequeue();
            calcPlayerDistance(playerDistance, walls, playerLocation, next, BFSNodes);
        }
    }
}

void Pathfinder::calcAlignDistance(int alignDistance[10][16], bool walls[10][16], std::pair<int, int> playerLocation, std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BFSNodes) {
    int y = currentLocation.second;
    int x = currentLocation.first;

    if (walls[y][x]) {
        alignDistance[y][x] = -99;
        return;
    }

    bool shouldLoop = (currentLocation == playerLocation);
    int tempY = y;
    while (tempY < height && !walls[tempY][x]) {
        alignDistance[tempY][x] = 1;
        BFSNodes.append(std::pair<int, int>(x, tempY++));
    }
    tempY = y;
    while (tempY >= 0 && !walls[tempY][x]) {
        alignDistance[tempY][x] = 1;
        BFSNodes.append(std::pair<int, int>(x, tempY--));
    }
    int tempX = x;
    while (tempX < width && !walls[y][tempX]) {
        alignDistance[y][tempX] = 1;
        BFSNodes.append(std::pair<int, int>(tempX++, y));
    }
    tempX = x;
    while (tempX >= 0 && !walls[y][tempX]) {
        alignDistance[y][tempX] = 1;
        BFSNodes.append(std::pair<int, int>(tempX--, y));
    }

    if (shouldLoop) {
        if (!BFSNodes.isEmpty())
            alignDistance[y][x] = -99;
        while (!BFSNodes.isEmpty()) {
            std::pair<int,int> next = BFSNodes.dequeue();
            breadthFirstDistanceCalc(alignDistance, walls, next, BFSNodes);
        }
    }
}


void Pathfinder::breadthFirstDistanceCalc(int matrix[10][16], bool walls[10][16], std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BFSNodes) {
    int x = currentLocation.first;
    int y = currentLocation.second;

    if (walls[y][x]) {
        matrix[y][x] = -99;
        return;
    }

    if (y - 1 >= 0 && matrix[y - 1][x] == 0) {
        matrix[y - 1][x] = matrix[y][x] + 1;
        BFSNodes.append(std::pair<int, int>(x, y-1));
    }
    if (y + 1 < height && matrix[y + 1][x] == 0) {
        matrix[y + 1][x] = matrix[y][x] + 1;
        BFSNodes.append(std::pair<int, int>(x, y+1));
    }
    if (x - 1 >= 0 && matrix[y][x - 1] == 0) {
        matrix[y][x - 1] = matrix[y][x] + 1;
        BFSNodes.append(std::pair<int, int>(x-1, y));
    }
    if (x + 1 < width && matrix[y][x + 1] == 0) {
        matrix[y][x + 1] = matrix[y][x] + 1;
        BFSNodes.append(std::pair<int, int>(x+1, y));
    }
}

void Pathfinder::debugPrintMap(std::vector<std::pair<int, int>> & enemyLocations, std::pair<int, int> & playerLocation, std::vector<std::pair<int, int>> & path) {
    QString line = "--";
    for (int i = 0; i < width; i++) {
        line += "--";
    }
    std::cout << line.toStdString();
    std::cout << std::endl;

    for (int y = 0; y < height; y++) {
        std::cout << "| ";
        for (int x = 0; x < width; x++) {
            if (std::find(path.begin(), path.end(), std::pair<int, int>(x, y)) != path.end())
                std::cout << "! ";
            else if(std::find(enemyLocations.begin(), enemyLocations.end(), std::pair<int, int>(x, y)) != enemyLocations.end())
                std::cout << "E ";
            else if (std::pair<int, int>(x, y) == playerLocation)
                std::cout << "P ";
            else
                std::cout << (walls[y][x] ? "X " : "- ");
        }
        std::cout << "|";
        std::cout << std::endl;
    }
}

