#ifndef GRIF_FORMAT_H
#define GRIF_FORMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "grif-format.h"
#include "midas-format.h"

#define MAX_SAMPLE_LEN  4096
#define NUM_CHAN        4096

typedef struct griffin_fragment_struct { 
   int          ph;   int suppress;    long  ts;
  int     address;   int chan;        int    dtype; int htype;
   int      energy;   int e_bad;       int    integ;   int cfd;
   int     energy2;   int e2_bad;      int   integ2;   int cc_long;
   int     energy3;   int e3_bad;      int   integ3;   int cc_short;
   int     energy4;   int e4_bad;      int   integ4;   int nhit;
   int    trig_req;   int trig_acc;    int   pileup;
   int deadtime;    int   bank_start;  long timestamp;   
   int   master_id;   int master_pattern;
   int      net_id;   int trigger_num;
   int  wf_present;   short waveform_length;  
} Grif_event;


extern int analyze_fragment(Grif_event*,short*);
int unpack_grif_bank(int *, int);
int unpack_grif3_event(unsigned*, int, Grif_event*, int,short*);
void print_fragment_info(Grif_event*);
#endif
