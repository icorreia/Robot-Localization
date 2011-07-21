/* 
 * File:   Robot.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:06
 */

#include <iostream>
#include "Robot.h"

using namespace std;

Robot::Robot(point p, vector dir)
{
    position = p;
    direction = dir;
}

Robot::Robot(const Robot& orig) {

}

Robot::~Robot() {
}

void Robot::moveRobot(int no)
{
    Move move = motionModel.makeNextMove(no);
    /* We first rotate and then only we move. */
    direction = move.newDirection;
    position.x += move.x*direction.x;
    position.y += move.y*direction.y;
    
}

void Robot::printPosition()
{
    cout << " The robot is in the (" << position.x << ", " << position.y
            << "), with direction (" << direction.x << ", " << direction.y
            << ")" << endl;
}

