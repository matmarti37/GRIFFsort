#ifndef SORT_H
#define SORT_H

#define NRING 7
#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"
#include "TH2D.h"
#include "TFile.h"

/* int hist[NCSI][S32K]; */
TH2D *h;
calibration_parameters* cal_par;
int eLow,eHigh;
int num1,num2;
#endif
