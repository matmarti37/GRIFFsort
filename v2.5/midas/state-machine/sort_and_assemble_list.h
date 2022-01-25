#ifndef STATE_MACHINE_ASSEMBLE_H
#define STATE_MACHINE_ASSEMBLE_H

#define DEPTH       40000000
#define SHIFT         10000

/* #define DEPTH            48 */
/* #define SHIFT             4 */

#define START_TSNS    65536

#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#define END_OF_SORT       5

#include "grif-format.h"
#include "midas-format.h"

typedef struct data_pointers
{
  unsigned long proc;
  int    last;
  int    trig;
  size_t son;
}data_pointers;

typedef struct node
{
  long    tsns;
  int     chan;
  long    ts;
  int     cfd;
}node;


extern int analyze_list(int,int,node*);
int print_list(int, int, node*);
int store_list(int, node*, FILE*);
int sort_list(data_pointers *, node*);
int add_node(node*, data_pointers *, node*);
void sort_and_assemble(char*);
void sort_and_assemble_subruns(char*);
int unpack_grif_bank_for_assembly(int *, int , data_pointers* , node*);
int analyze_fragment_for_assebly(Grif_event*, short*,data_pointers*, node*);
int get_fragments_for_assembly(data_pointers*, node*);
#endif
