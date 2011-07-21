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
    void printPosition();

    Algorithms *algorithms;

private:
    point position;
    double angle;
    RandomNumbers *randGenerator;

    MotionModel motionModel;
    
};

#endif	/* ROBOT_H */

