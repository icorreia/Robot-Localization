/* 
 * File:   Robot.cpp
 * Author: Ivo
 * 
 * Created on 12 de Julho de 2011, 13:06
 */

#include <iostream>
#include <ctime>
#include "Robot.h"
#include "RandomNumbers.h"

using namespace std;

#define MOTION_SD 2
#define ROTATION_SD 0.1

Robot::Robot(point p, double a)
{
    location.position = p;
    location.angle = a;

    cout << "CREATING RANDOM NUMBERS INSTANCE..." << endl;
    randGenerator = new RandomNumbers((unsigned) time(0));
    cout << "RANDOM NUMBERS INSTANCE CREATED!" << endl;
    cout << "CREATING ALGORITHMS INSTANCE..." << endl;
    algorithms = new Algorithms(NO_ACCESS_POINTS, randGenerator);
    cout << "ALGORITHMS INSTANCE CREATED!" << endl;
}

Robot::~Robot()
{
    delete algorithms;
    delete randGenerator;
}

void Robot::moveRobot(int no)
{
    /* We assume that the robot moves with gaussian error and therefore, we need
     * to calculate incertities associated with each odometry measure.
     */
    double motionIncertity, rotationIncertity;
    double xMotionIncrease, yMotionIncrease, angleIncrease;

    Move move = motionModel.makeNextMove(no);

    rotationIncertity = randGenerator->uniform(0, ROTATION_SD);
    motionIncertity = randGenerator->uniform(0, MOTION_SD);

    /* The predict step use these values to update the particles, and that's
     * why we need to save them.
     */
    xMotionIncrease = move.x + motionIncertity;
    yMotionIncrease = move.y + motionIncertity;
    angleIncrease = move.rotation + rotationIncertity;
    
    location.angle += move.rotation;
    location.position.x += move.x;
    location.position.y += move.y;

    location.edge = algorithms->findBestEdge(location);
    algorithms->updateDistance(location);
    location.offset = algorithms->calculateOffset(location, location.edge);

   
    algorithms->predict(xMotionIncrease, yMotionIncrease, angleIncrease);
    algorithms->update();
    algorithms->locationBelief(location);
}

void Robot::printPosition()
{
    cout << " The robot is in the (" << location.position.x << ", " << location.position.y
            << "), with angle " << location.angle << "." << endl;
}

