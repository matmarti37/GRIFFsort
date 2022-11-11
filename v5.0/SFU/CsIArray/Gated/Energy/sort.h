#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"
#include "TFile.h"

// For TIGRESS
int pos,col;
int  hist[NPOSTIGR][NCOL][S32K];
calibration_parameters* cal_par;

// For CsIArray
#include "TCutG.h"
TCutG *pGate = new TCutG();

//int count=0;



#endif
