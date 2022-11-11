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
int  chi_sq_cutoff;
TH1D *h[256],*hcsi;
TH2D *h2[256];
int hist[256][S4K];
int det_map[S2K];

#endif
