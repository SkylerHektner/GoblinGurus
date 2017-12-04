#include "pathfinder.h"

Pathfinder::Pathfinder(std::vector<std::pair<int, int>> * collisionPoints) {
    for (int i = 0; i < collisionPoints->size; i++) {
        map[collisionPoints->at(i).first][collisionPoints->at(i).second] = true;
    }
}

/**
 * @brief Pathfinder::findPath - Calculates the location in the map that best suits the given conditions
 * @param enemy_x - The x position of the enemy you'd like to move
 * @param enemy_y - The y position of the enemy you'd like to move
 * @param speed - The number of squares the enemy can move
 * @param player_x - The current X position of the player
 * @param player_y - The current Y position of the player
 * @param get_close - The priority of getting close to the player. Positive values prioritize approaching
 * the player. Negative values prioritize getting away from the player. 0 ignores this value
 * @param move_to_row_column - The priority of aligning on the same row or column as the player. Negative
 * values proritize aligning on diagonals while positive values prioritize the alignment
 * @return A list of move actions to be taken in order to move the enemy to its correct location.
 */
std::vector<std::pair<int, int>> Pathfinder::findPath(int enemy_x, int enemy_y, int speed, int player_x, int player_y,
                                                      double get_close, double move_to_row_column) {
    String result = "";
    pathfind(enemy_x, enemy_y, speed, player_x, player_y, get_close, move_to_row_column, &result);
}

/**
 * @brief Pathfinder::pathfind - Calculates the best path and returns the priority of that path, and
 * stores the path in a string. NOTE: The algorithm does consider the fact that staying still may be the
 * best option
 * @param enemy_x - The x position of the enemy you'd like to move
 * @param enemy_y - The y position of the enemy you'd like to move
 * @param speed - The number of squares the enemy can move
 * @param player_x - The current X position of the player
 * @param player_y - The current Y position of the player
 * @param get_close - The priority of getting close to the player. Positive values prioritize approaching
 * the player. Negative values prioritize getting away from the player. 0 ignores this value
 * @param move_to_row_column - The priority of aligning on the same row or column as the player. Negative
 * values proritize aligning on diagonals while positive values prioritize the alignment
 * @param result - the string that will contain the best result of the called upon node
 * @return - The largest number created by the four directions of this node
 */
int Pathfinder::pathfind(int enemy_x, int enemy_y, int speed, int player_x, int player_y,
                         double get_close, double move_to_row_column, QString &result) {

}

bool Pathfinder::shouldAttack(QString enemyType, int player_x, int player_y) {
    return false;
}

