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
    moves[0].rotation = 0;
    moves[0].x = 0;
    moves[0].y = 250;
    moves[1].rotation = 0;
    moves[1].x = 0;
    moves[1].y = 250;
    moves[2].rotation = PI/2;
    moves[2].x = 250;
    moves[2].y = 0;
    moves[3].rotation = 0;
    moves[3].x = 250;
    moves[3].y = 0;
    moves[4].rotation = -PI/2;
    moves[4].x = 0;
    moves[4].y = 250;
    moves[5].rotation = 0;
    moves[5].x = 0;
    moves[5].y = 250;
    moves[6].rotation = 0;
    moves[6].x = 250;
    moves[6].y = 0;
    moves[7].rotation = -PI/2;
    moves[7].x = 250;
    moves[7].y = 0;
    moves[8].rotation = PI/2;
    moves[8].x = 0;
    moves[8].y = 250;
    moves[9].rotation = 0;
    moves[9].x = 0;
    moves[9].y = 250;
}

Move MotionModel::makeNextMove(int move) { return moves[move]; }

