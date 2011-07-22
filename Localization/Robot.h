/* 
 * File:   Robot.h
 * Author: Ivo
 *
 * Created on 12 de Julho de 2011, 13:06
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include "Space.h"
#include "MotionModel.h"
#include "Structures.h"
#include "RandomNumbers.h"
#include "Algorithms.h"

class Robot {
public:
    Robot(point p, double a);
    virtual ~Robot();

    void moveRobot(int move);
    //TODO: May eventually be removed later.
    void printPosition();  

private:
    point position;
    double angle; //The orientation of the robot
    RandomNumbers *randGenerator;
    Algorithms *algorithms;
    MotionModel motionModel;
    
};

#endif	/* ROBOT_H */

