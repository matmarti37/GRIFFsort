#ifndef STATE_MACHINE_ASSEMBLE_H
#define STATE_MACHINE_ASSEMBLE_H

#define DEPTH         100
#define START_TAG     1024
#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#define END_OF_SORT       5

#include "grif-format.h"
#include "midas-format.h"
#include "SFU-format.h"
#include "map.h"

typedef struct data_pointers
{
  unsigned long proc;
  long   last;
  size_t son;
}data_pointers;

typedef struct node
{
  long   tag;
  int    fold;
}node;


extern int analyze_assembled_event(raw_event*);
int add_fragment(long, data_pointers*, node*);
int print_list(data_pointers *, node*,gmap*);
int sort_list(data_pointers *, node*);
int add_node(long, data_pointers *, node*);
int tag_on_list(long, data_pointers *, node*);
void sort_and_assemble(char*,char*);
int unpack_grif_bank_for_assembly(int *, int , data_pointers* , node*, gmap*);
int analyze_fragment_for_assebly(Grif_event*, short*,data_pointers*, node*, gmap* );
int get_fragments_for_assembly(data_pointers*, node*, gmap*);
#endif
