#ifndef __PID1_H
#define __PID1_H
#include "sys.h"


void PID_init();
float PID_realize(float speed);
#endif
