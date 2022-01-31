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

char data_filename[128], output_filename[128];
char csi_map_filename[128], tig_map_filename[128], sup_map_filename[128];
char csi_cal_filename[128], tig_cal_filename[128], sup_cal_filename[128];
char csi_ring_filename[128], tig_ring_filename[128], sup_ring_filename[128];

int chisq_cutoff, ring_low, ring_high;

int csi_pos[S2K]; // csi_pos[channel]=detector
int tig_pos[S2K]; // tig_pos[channel]=position
char tig_sub[S2K]; // tig_sub[channel]=sub-position
int tig_seg[S2K]; // tig_seg[channel]=segment
char tig_charge[S2K]; //tig_charge[channel]=charge
int sup_pos[S2K]; // sup_pos[channel]=position
char sup_sub[S2K]; // sup_sub[channel]=sub-position
int sup_seg[S2K]; // sup_seg[channel]=segment
char sup_charge[S2K]; //sup_charge[channel]=charge

long double TIP_cal_params[256][2];

int ring_dets[10][2];
int dets_ring[256];
int det_low, det_high;

TH1D *det_h[256];
TH1D *ring_h[10];

TH1D *uncal_det_h[256];
TH1D *uncal_ring_h[10];

int ampl_flag=0;
int bad_channel;
int csi_count;

long long prev_timestamp;
TH1D *time_diff;

long long tot_count;

#endif
