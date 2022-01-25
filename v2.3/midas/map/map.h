#ifndef __MAP_H
#define __MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct gmap
{
  char title[256];
  int div;
} gmap;


void read_map(char*,gmap*);
void print_map();
#endif
