#ifndef SORT_H
#define SORT_H

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
#include "SFU-common.h"
#include "sort_but_not_assemble.h"

TH1D *h_channel,*h_detector;
TH2D *h_2D,*h_mapping;
int x_vals[S2K];
int y_vals[S2K];
int det_map[S2K];
#endif
