#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TFile.h"
#include "TH2D.h"

int pos,col;
double supLow,supHigh;

//int  hist[NPOSTIGR][NCOL*2][S32K];
TH2D *h;

calibration_parameters* cal_par;



int tot_count,grf_count;


#endif
