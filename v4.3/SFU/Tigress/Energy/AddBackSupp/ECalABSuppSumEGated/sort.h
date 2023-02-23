#ifndef SORT_H
#define SORT_H


#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TH2D.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

int gatehist[7][S32K];
int hist[7][S32K];
calibration_parameters* cal_par;
double supLow,supHigh;
int gateELow[7], gateEHigh[7];
//int pos,col,colAddBack;

TH2D *h;

#endif
