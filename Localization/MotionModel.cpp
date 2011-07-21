/* 
 * File:   MotionModel.cpp
 * Author: Ivo
 * 
 * Created on 13 de Julho de 2011, 15:06
 */

#include "MotionModel.h"
#include "Structures.h"

MotionModel::MotionModel()
{
    /* First, we have to define all the movements of the robot. A new movement
     * will be taken every 500ms, the time where each update step must be done.
     */
    moves[0].newDirection.x = 0;
    moves[0].newDirection.y = 1;
    moves[0].x = 0;
    moves[0].y = 250;
    moves[1].newDirection.x = 0;
    moves[1].newDirection.y = 1;
    moves[1].x = 0;
    moves[1].y = 250;
    moves[2].newDirection.x = -1;
    moves[2].newDirection.y = 0;
    moves[2].x = 250;
    moves[2].y = 0;
    moves[3].newDirection.x = -1;
    moves[3].newDirection.y = 0;
    moves[3].x = 250;
    moves[3].y = 0;
    moves[4].newDirection.x = 0;
    moves[4].newDirection.y = 1;
    moves[4].x = 0;
    moves[4].y = 250;
    moves[5].newDirection.x = 0;
    moves[5].newDirection.y = 1;
    moves[5].x = 0;
    moves[5].y = 250;
    moves[6].newDirection.x = 1;
    moves[6].newDirection.y = 0;
    moves[6].x = 250;
    moves[6].y = 0;
    moves[7].newDirection.x = 1;
    moves[7].newDirection.y = 0;
    moves[7].x = 250;
    moves[7].y = 0;
    moves[8].newDirection.x = 0;
    moves[8].newDirection.y = 1;
    moves[8].x = 0;
    moves[8].y = 250;
    moves[9].newDirection.x = 0;
    moves[9].newDirection.y = 1;
    moves[9].x = 0;
    moves[9].y = 250;
}

MotionModel::MotionModel(const MotionModel& orig)
{
}

MotionModel::~MotionModel()
{
}

Move MotionModel::makeNextMove(int move) { return moves[move]; }

