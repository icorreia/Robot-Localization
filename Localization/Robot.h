/* 
 * File:   Robot.h
 * Author: Ivo
 *
 * Created on 12 de Julho de 2011, 13:06
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include "Space.h"

class Robot {
public:
    Robot();
    Robot(const Robot& orig);
    virtual ~Robot();
private:
    double speed;
    point position;
    vector direction;
    
};

#endif	/* ROBOT_H */

