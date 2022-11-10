#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TFile.h"

#include "TCutG.h"
TCutG *pGate = new TCutG();
TCutG *aGate = new TCutG();


int keep;
calibration_parameters* cal_par;

int tot_count,grf_count,tot_keep,grf_keep,all_count;
#endif
