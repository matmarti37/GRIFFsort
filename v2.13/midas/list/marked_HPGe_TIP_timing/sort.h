#ifndef SORT_H
#define SORT_H

#define DTRIG 20

#include "SFU-common.h"
#include "sort_and_assemble_list.h"

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH1D *h;
TCanvas *c;  
TApplication *theApp;

int hist[S32K];

int analyze_fragment(Grif_event*, short*){return -1;};
int analyze_list(int,int,node*){return -1;};

#endif
