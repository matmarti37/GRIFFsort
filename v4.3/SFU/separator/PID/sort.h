#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "SFU-format.h"
#include "SFU-decoder.h"
#include "SFU-cal.h"

#include "TFile.h"

#include "TCutG.h"
/* TCutG *pGate[10]; */
/* TCutG *aGate[10]; */

TCutG *aGate = new TCutG();
TCutG *pGate = new TCutG();

int keep;
calibration_parameters* cal_par;
#endif
