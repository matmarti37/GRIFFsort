#ifndef GRIF_FORMAT_H
#define GRIF_FORMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "midas-format.h"

#define MAX_SAMPLE_LEN  4096
#define ENERGY_BINS    65536 /* 65536 131072 262144 */
#define NUM_CHAN        4096

typedef struct griffin_fragment_struct { // 74 bytes
   int          ph;   int suppress;    long  ts;
   int     address;   int chan;        int    dtype;   
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


int unpack_grif_bank(int *, int, Grif_event *, int, short*);
int unpack_grif3_event(unsigned*, int, Grif_event*, int,short*);
void print_fragment_info(Grif_event*,int);
#endif
