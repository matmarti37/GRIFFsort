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

TH2D *acc_e_r,*acc_s_f,*acc_s_r;
TH2D *rej_e_r,*rej_s_f,*rej_s_r;
TH2D *all_e_r,*all_s_f,*all_s_r;
ShapePar* par;
int chi_sq_cutoff;
int counter;
int type_low,type_high;
char* outputfile;
char* output_dir;
char textfilename[256];
char rootfilename[256];
int det_map[S2K];
int det_low,det_high;

#endif
