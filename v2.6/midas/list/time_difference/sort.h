#ifndef SORT_H
#define SORT_H



#include "sort_and_assemble_list.h"

#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH1D *h;
TCanvas *c;  
TApplication *theApp;

long tsstore;

int analyze_fragment(Grif_event*, short*){return -1;};
#endif
