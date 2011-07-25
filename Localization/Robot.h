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
    /* This particle will represent the real position of the robot. It's only
     * needed for simulation purposes, as, when collecting signal strengths,
     * we cannot simply rely on the position of the current particle to estimate
     * values, as it may not be the true position of the robot.
     */
    Particle location;

    RandomNumbers *randGenerator;
    Algorithms *algorithms;
    MotionModel motionModel;
    
};

#endif	/* ROBOT_H */

