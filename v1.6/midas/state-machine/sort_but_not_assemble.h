#ifndef STATE_MACHINE_NOT_ASSEMBLE_H
#define STATE_MACHINE_NOT_ASSEMBLE_H

#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4

#include "grif-format.h"
#include "midas-format.h"
#include <stdlib.h>

extern int analyze_fragment(Grif_event*,short*);
void sort_but_not_assemble(char*);
int  get_fragments(long*);

#endif
