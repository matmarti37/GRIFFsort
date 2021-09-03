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

TH2D *full_h,*accepted_h,*rejected_h;
TCanvas *c;
TApplication *theApp;
ShapePar* par;
int chi_sq_cutoff;
int counter;
int type_low,type_high;
char* outputfile;
char* output_dir;
char textfilename[256];
char rootfilename[256];

#endif
