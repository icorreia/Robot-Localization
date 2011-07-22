/* 
 * File:   MotionModel.h
 * Author: Ivo
 *
 * Created on 13 de Julho de 2011, 15:06
 */

#ifndef MOTIONMODEL_H
#define	MOTIONMODEL_H

#include "Structures.h"

class MotionModel {
public:
    MotionModel();

    Move makeNextMove(int move);

private:
    Move moves[NO_MOVES];
};

#endif	/* MOTIONMODEL_H */

