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

#include "TCutG.h"
TCutG *pGate = new TCutG();
TCutG *aGate = new TCutG();

TH1D *h;
calibration_parameters* cal_par;
#endif
