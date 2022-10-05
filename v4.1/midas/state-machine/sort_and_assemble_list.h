#ifndef STATE_MACHINE_ASSEMBLE_H
#define STATE_MACHINE_ASSEMBLE_H

#define DEPTH      40000000
#define SHIFT         10000

/* #define DEPTH            48 */
/* #define SHIFT             4 */


#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#define END_OF_SORT       5

#include "grif-format.h"
#include "midas-format.h"
#include "SFU-format.h"
#include "SFU-common.h"
#include "map.h"


typedef struct data_pointers
{
  unsigned long proc;
  int    last;
  int    trig;
  size_t son;
}data_pointers;

typedef struct node
{
  unsigned long long    tsns;
  int          chan;
  int          trig;
  int          tig_trig;
  int          csi_trig;
  unsigned long long    trig_tsns;
  channel      ch;
  ShapePar     wfit;
  double       t0;
}node;

extern int prev_TSUP, min_TSUP, max_TSUP, buffer_TSUP, buffer_DROPPED, minmax_DROPPED, prev_DROPPED, pileup_DROPPED, total_FRAGMENTS;
extern int analyze_list(int,int,node*);
int print_list(int, int, node*);
int store_list(int, node*, FILE*);
int sort_list(data_pointers *, node*);
int add_node(node*, data_pointers *, node*);
void sort_and_assemble(char*,char*);
void sort_and_assemble_subruns(char*,char*);
int unpack_grif_bank_for_assembly(int *, int , data_pointers* , node*, gmap*);
int analyze_fragment_for_assembly(Grif_event*, short*,data_pointers*, node*, gmap*);
int get_fragments_for_assembly(data_pointers*, node*, gmap*);
int same_HPGe(node*, node*, gmap*);
int CC_channel(node*, gmap*);
int Seg_channel(node*, gmap*);
int Sup_channel(node*, gmap*);
int TIP_channel(node*, gmap*);
int map_event(raw_event*,node *, gmap*);

#endif
