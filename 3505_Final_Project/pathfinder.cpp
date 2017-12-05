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
    debugPrintMap(enemyLocations, playerLocation, emptyVector);
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
            if(std::find(enemyLocations.begin(), enemyLocations.end(), std::pair<int, int>(x, y)) != enemyLocations.end()) {
                std::cout << "E ";
            } else if (std::pair<int, int>(x, y) == playerLocation)
                std::cout << "P ";
            else
                std::cout << (walls[y][x] ? "X " : "- ");
        }
        std::cout << "|";
        std::cout << std::endl;
    }
}

