#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "sort_but_not_assemble.h"
#include "waveform_analyzer.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"
#include "TF1.h"
#include "TROOT.h"
#include "math.h"

ShapePar* par;
TH1D *h[256],*hcsi;
TH2D *h2[256];
int hist[256][S4K];


char data_filename[128], output_filename[128], map_filename[128], cal_filename[128], ring_filename[128];
int chisq_cutoff, ring_low, ring_high;

int det_map[S2K];
long double TIP_cal_params[256][2];

int ring_dets[10][2];
int dets_ring[256];
int det_low, det_high;

TH1D *det_h[256];
TH1D *ring_h[10];

TH1D *uncal_det_h[256];
TH1D *uncal_ring_h[10];

#endif
