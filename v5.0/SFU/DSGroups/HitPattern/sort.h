#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TH2D.h"
#include "TFile.h"
#include "TStyle.h"

calibration_parameters* cal_par;
int supLow,supHigh;

double Ebeam;
double ds;
double beta;

double p_beam[4]; // 0 is magnitude, 1,2,3 are x,y,z;
double d_part[NCSI][4];
double p_part[NCSI][4]; // first index is for csi detector number
double np_part[NCSI][4]; // normalized particle momenta
double p_res[4];
double np_res[4];
double d_gamma[4];
double np_gamma[4];

int dshist[S4K];
int ering[NRING][S32K];
int edsgroup[NRING][S32K];
TH2D *dsring,*dsdsgroup,*dsgroupring;
#endif
