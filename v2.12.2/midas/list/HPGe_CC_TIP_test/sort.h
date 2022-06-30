#ifndef SORT_H
#define SORT_H


#include "SFU-common.h"
#include "sort_and_assemble_list.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH1D *h;
TCanvas *c;  
TApplication *theApp;

int hist[S32K];
unsigned long long window;

int analyze_list(int,int,node*){return -1;};
int analyze_fragment(Grif_event*, short*){return -1;};

TH2D *PID[5];
TH1D *TIME[5];
TH1D *chHP[5];
TH1D *tgHP[5];

#endif
