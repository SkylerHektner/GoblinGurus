#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>

class Pathfinder
{
public:
    Pathfinder(std::vector<std::pair<int, int>> * collisionPoints);
    std::vector<std::pair<int, int>> findPath(int enemy_x, int enemy_y, int speed, int player_x, int player_y, double get_close, double move_to_row_column);
    bool shouldAttack(QString enemyType, int player_x, int player_y);
private:
    bool map[10][16];
    int pathfind(int enemy_x, int enemy_y, int speed, int player_x, int player_y, double get_close, double move_to_row_column, QString &result);
};

#endif // PATHFINDER_H
