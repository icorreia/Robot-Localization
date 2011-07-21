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

class Robot {
public:
    Robot(point p, vector dir);
    Robot(const Robot& orig);
    virtual ~Robot();

    void moveRobot(int move);
    void printPosition();

private:
    point position;
    vector direction;

    MotionModel motionModel;
    
    
};

#endif	/* ROBOT_H */

