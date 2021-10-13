#ifndef CAL_TIP_H
#define CAL_TIP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char *cal_filename;
float TIP_cal_params[128][2];

int TIP_cal_initialize();
int TIP_calibration(char *cal_filename);

#endif
