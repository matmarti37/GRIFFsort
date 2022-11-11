#ifndef SORT_H
#define SORT_H

#include <time.h>

#include "sort_and_assemble_list.h"
#include "map.h"

FILE* out;

int prev_TSUP, min_TSUP, max_TSUP, buffer_TSUP, buffer_DROPPED, minmax_DROPPED, prev_DROPPED, total_FRAGMENTS;
int analyze_fragment(Grif_event*, short*){return -1;};
#endif
