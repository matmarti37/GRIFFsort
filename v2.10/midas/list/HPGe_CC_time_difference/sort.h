#ifndef SORT_H
#define SORT_H


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

long long tsstore;
int hist[S4K];

#endif
