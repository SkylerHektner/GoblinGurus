#include "pathfinder.h"
#include <iostream>

/**
 * @brief Pathfinder::Pathfinder - Creates the pathfinder class. This class (and I believe this is true
 * because of c++) can only have Pathfinders of 10x16.
 * @param collisionPoints - The vector of spaces that can't be moved into
 * @param height - 10. You have to pass it 10 or this whole thing will break.
 * @param width - 16 in our case.
 */
Pathfinder::Pathfinder(std::vector<std::pair<int, int>> & collisionPoints, int height, int width) {
    this->height = height;
    this->width = width;

    //Initialize the walls matrix
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            walls[y][x] = 0;

    //Build the walls matrix
    for (unsigned int i = 0; i < collisionPoints.size(); i++) {
        walls[collisionPoints[i].second][collisionPoints[i].first] = true;
    }
}

/**
 * @brief Pathfinder::findPath - Generates a list of steps to get to the square determined "best"
 * by the align, approach, and speed parameters
 * @param enemyLocations - The locations of all the enemies on the map.
 * @param activeEnemyIndex - The index of the enemy currently active
 * @param speed - The speed of the enemy
 * @param align - The priority to align on the same x or y as the player. A positive value means the
 * enemy wishes to get on the grid, while a negative value means the enemy wants to get as far away
 * from the grid as possible
 * @param approach - The priority to approach the player. A positive value means the enemy wishes to
 * approach the player, while a negative value means the enemy wishes to get as far away as possible.
 * @param playerLocation - The location of the player for getting the distances
 * @return - A list of steps to take to make one-step moves to the best possible square. Note: this
 * can be empty if the enemy decides that staying still is the best course of action (which is
 * definitely a possibility
 */
std::vector<std::pair<int, int>> Pathfinder::findPath(std::vector<std::pair<int, int>> & enemyLocations,
               int activeEnemyIndex, int speed, double align, double approach, std::pair<int, int> playerLocation) {
    std::vector<std::pair<int, int>> emptyVector;

    //Declare and initialize matrices
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

    //BFS to generate distances
    QQueue<std::pair<int, int>> BFSNodes;
    calcPlayerDistance(playerDistance, walls, playerLocation, playerLocation, BFSNodes);
    BFSNodes.clear();
    calcAlignDistance(alignDistance, walls, playerLocation, playerLocation, BFSNodes);

    //Calculate best path
    calcPriorities(playerDistance, approach, alignDistance, align, speed, priorities);
    double find = bestPath(enemyLocations[activeEnemyIndex], priorities, speed);
    QString path = pathfind(enemyLocations[activeEnemyIndex], priorities, speed, find);

    //Decode the path string into steps
    std::vector<std::pair<int, int>> result = decodeString(enemyLocations[activeEnemyIndex], path);

    //debugPrintMap(enemyLocations, playerLocation, result);

    return result;
}

/**
 * @brief Pathfinder::shouldAttack - Lets you know if the enemy should attack or not
 * @param enemyLocation - Location of the enemy you wish to know about
 * @param playerLocation - Locatin of the player
 * @param enemyType - The type of enemy. Currently only supports "Warrior", "Mage", and "Archer"
 * @return  - Whether or not the given enemy can attack the player.
 */
bool Pathfinder::shouldAttack(std::pair<int, int> enemyLocation, std::pair<int, int> playerLocation, QString enemyType) {
    //Declare and initialize matrices
    int playerDistance[10][16];
    int alignDistance[10][16];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            playerDistance[y][x] = 0;
            alignDistance[y][x] = 0;
        }

    //BFS for distances
    QQueue<std::pair<int, int>> BFSNodes;
    calcPlayerDistance(playerDistance, walls, playerLocation, playerLocation, BFSNodes);
    calcAlignDistance(alignDistance, walls, playerLocation, playerLocation, BFSNodes);

    //Return whether or not we should attack
    if (enemyType == "Warrior")
        return playerDistance[enemyLocation.second][enemyLocation.first] == 1;
    else if (enemyType == "Archer")
        return alignDistance[enemyLocation.second][enemyLocation.first] == 1;
    else if (enemyType == "Mage")
        return playerDistance[enemyLocation.second][enemyLocation.first] < 5;
}

//Decodes the string into moves
std::vector<std::pair<int, int>> Pathfinder::decodeString(std::pair<int, int> enemyLocation, QString path) {
    //Initialize
    std::vector<std::pair<int, int>> coordinates;
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    //Do the implied move
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

        //Push to coordinates
        coordinates.push_back(std::pair<int, int>(x, y));
    }

    return coordinates;
}

//Find a path to the specified value. Note: This will not do the shortest path. I wanted practice with DFS as well as BFS
//I understand I should have used BFS if I wanted to find the shortest path.
QString Pathfinder::pathfind(std::pair<int, int> enemyLocation, double priorities[10][16], int speed, double valToFind) {
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    //If priority of this location is suuuuuuper low (caused by invalid locations) return null
    if (priorities[y][x] < -90)
        return nullptr;

    //If this is the value we're looking for, return something not null
    if (priorities[y][x] == valToFind)
        return " ";

    //If we reach here and can't move further, it isn't this way.
    if (speed == 0)
        return nullptr;

    //Recurse and generate string if our recursion gave us something other than null
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

    //Didn't find the value, return null
    return nullptr;
}

//Returns the largest number that can be reached from the location
double Pathfinder::bestPath(std::pair<int, int> enemyLocation, double priorities[10][16], int speed) {
    int x = enemyLocation.first;
    int y = enemyLocation.second;

    //Don't do walls
    if (priorities[y][x] < -90)
        return -99;

    //If speed is 0, this is the only possibility
    if (speed == 0)
        return priorities[y][x];

    //Otherwise, recurse and return the maximum
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

//Loops through to calculate the priorities
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

//Fills the player distance matrix
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

//Fills the align distance matrix
void Pathfinder::calcAlignDistance(int alignDistance[10][16], bool walls[10][16], std::pair<int, int> playerLocation, std::pair<int, int> currentLocation, QQueue<std::pair<int, int>> &BFSNodes) {
    int y = currentLocation.second;
    int x = currentLocation.first;

    if (walls[y][x]) {
        alignDistance[y][x] = -99;
        return;
    }

    bool shouldLoop = (currentLocation == playerLocation);

    //Head all the way down until we find a wall.
    int tempY = y;
    while (tempY < height && !walls[tempY][x]) {
        alignDistance[tempY][x] = 1;
        BFSNodes.append(std::pair<int, int>(x, tempY++));
    }

    //up to a wall
    tempY = y;
    while (tempY >= 0 && !walls[tempY][x]) {
        alignDistance[tempY][x] = 1;
        BFSNodes.append(std::pair<int, int>(x, tempY--));
    }

    //right
    int tempX = x;
    while (tempX < width && !walls[y][tempX]) {
        alignDistance[y][tempX] = 1;
        BFSNodes.append(std::pair<int, int>(tempX++, y));
    }

    //left
    tempX = x;
    while (tempX >= 0 && !walls[y][tempX]) {
        alignDistance[y][tempX] = 1;
        BFSNodes.append(std::pair<int, int>(tempX--, y));
    }

    //Finish BFS algorithm
    if (shouldLoop) {
        if (!BFSNodes.isEmpty())
            alignDistance[y][x] = -99;
        while (!BFSNodes.isEmpty()) {
            std::pair<int,int> next = BFSNodes.dequeue();
            breadthFirstDistanceCalc(alignDistance, walls, next, BFSNodes);
        }
    }
}

//Sets all unvisited (value == 0) children to 1+ itself, and then adds them to the Queue
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

//Uses cout for debugging
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

