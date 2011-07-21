/* 
 * File:   Robot.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:06
 */

#include <iostream>
#include "Robot.h"
#include "RandomNumbers.h"

using namespace std;

#define MOTION_SD 0.5
#define ROTATION_SD 0.0001

Robot::Robot(point p, double a)
{
    position = p;
    angle = a;

    randGenerator = new RandomNumbers(0);
    algorithms = new Algorithms(NO_ACCESS_POINTS, randGenerator);
}

Robot::~Robot()
{
    delete algorithms;
    delete randGenerator;
}

void Robot::moveRobot(int no)
{
    double motionIncertity, rotationIncertity;
    double xMotionIncrease, yMotionIncrease, angleIncrease;

    Move move = motionModel.makeNextMove(no);

    rotationIncertity = randGenerator->uniform(0, ROTATION_SD);
    motionIncertity = randGenerator->uniform(0, MOTION_SD);

    xMotionIncrease = move.x + motionIncertity;
    yMotionIncrease = move.y + motionIncertity;
    angleIncrease = move.rotation + rotationIncertity;
    
    angle += angleIncrease;
    position.x += xMotionIncrease;
    position.y += yMotionIncrease;

    algorithms->predict(xMotionIncrease, yMotionIncrease, angleIncrease);
    algorithms->update();
    
}

void Robot::printPosition()
{
    cout << " The robot is in the (" << position.x << ", " << position.y
            << "), with angle " << angle << "." << endl;
}

