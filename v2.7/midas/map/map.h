#ifndef __MAP_H
#define __MAP_H

#define CSIPOSLT  512
#define TCCPOSLT 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SFU-format.h"

typedef struct gmap
{
  char   title[256];
  char   tccmap[256];
  int    tcc_min;
  int    tcc_max;
  int    tccpos[TCCPOSLT];
  int    tcccol[TCCPOSLT];
  int    csiarray_min;
  int    csiarray_max;
  char   csimap[256];
  int    csiarray_fit;
  int    csipos[CSIPOSLT];
  double csiarray_trc;
  double csiarray_tf;
  double csiarray_ts;
  double csiarray_tr;
  int    csiarray_pretrig;
} gmap;


void read_map(char*,gmap*);
void print_map(gmap*);
void print_csipos(gmap*);
void print_tccpos(gmap*);
#endif
