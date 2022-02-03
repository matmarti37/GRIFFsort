#ifndef __MAP_H
#define __MAP_H

#define CSIPOSLT  512
#define TIGPOSLT 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SFU-format.h"

typedef struct chstr
{
  int pos;
  int seg;
  int col;
} chstr;


typedef struct gmap
{
  char    title[256];
  char    tccmap[256];
  char    tsegmap[256];
  char    tsupmap[256]; 
  int     tig_min;
  int     tig_max;
  chstr   hpge_lt[TIGPOSLT];
  chstr   supp_lt[TIGPOSLT];
  int     csiarray_min;
  int     csiarray_max;
  char    csimap[256];
  int     csiarray_fit;
  int     csi_lt[CSIPOSLT];
  double  csiarray_trc;
  double  csiarray_tf;
  double  csiarray_ts;
  double  csiarray_tr;
  int     csiarray_pretrig;
} gmap;


void read_map(char*,gmap*);
void print_map(gmap*);
void print_csimap(gmap*);
void print_tccmap(gmap*);
void print_tsegmap(gmap*);
void print_tsupmap(gmap*);

#endif
