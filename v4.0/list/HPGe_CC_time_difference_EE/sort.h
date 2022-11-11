#ifndef SORT_H
#define SORT_H


#include "SFU-common.h"
#include "read_and_sort_list.h"

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TApplication.h"

TH2D *h;
TCanvas *c;  
TApplication *theApp;

long long tsstore,Estore,Egate_low,Egate_high;
int time_low,time_high,divisor;

#endif
