#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
//#include "TCutG.h"

TH2D *h[NCSI];
TH2D *h_ring[10];
calibration_parameters* cal_par;
int num1,num2;
#endif
