// read midas data files
// set sources=( grif-replay.c midas-format.c grif-format.c util.c )
// gcc -g -o grif-replay $sources -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "grif-format.h"

int debug;
static Grif_event grif_event;
short waveform[MAX_SAMPLE_LEN];
int waveforms = 1; // process [1] or ignore them

extern void swapInt (char*, int), swapShort(char*, int), swapWords (char*, int);
extern int next_record(), next_event(), next_bank(char **, int **);
extern int unpack_grif_bank(int *data, int length, Grif_event *ptr, int);
extern int print_raw_event( unsigned *buf, int len );
extern int dump_bank( unsigned *data, int len );
static int cleanup();

extern int assemble_init();
extern int assemble_event(unsigned *, int, int **);
extern int process_event();
static int reconst_init=0;

static int event_limit  = 0x7FFFFFFF;
static int event_pause  = 0;
static int event_skip   = 0;

static int events_done;
int main(int argc, char *argv[])
{
   int i;
   for(i=1; i<argc; i++){
      if( *argv[i] == '-' ){
	 switch( *(argv[i]+1) ){
	 case 'd': debug=1; break; // write debug info
	 case 'p':                 // pause X ms between events
	    if( ++i >= argc ){
	       fprintf(stderr,"missing value for arg -p\n");
	    } else {
	       if( sscanf(argv[i], "%d", &event_pause) != 1 ){
		  fprintf(stderr,"can't read value:%s for arg -p\n", argv[i]);
		  event_pause = 0;
	       }
	    } break;
	 case 'e':                 // only sort X events
	    if( ++i >= argc ){
	       fprintf(stderr,"missing value for arg -e\n");
	    } else {
	       if( sscanf(argv[i], "%d", &event_limit) != 1 ){
		  fprintf(stderr,"can't read value:%s for arg -e\n", argv[i]);
		  event_limit = 0x7FFFFFFF;
	       }
	    } break;
	 case 's':                 // skip X events, after each event sorted
	    if( ++i >= argc ){
	       fprintf(stderr,"missing value for arg -s\n");
	    } else {
	       if( sscanf(argv[i], "%d", &event_skip) != 1 ){
		  fprintf(stderr,"can't read value:%s for arg -s\n", argv[i]);
		  event_skip = 0;
	       }
	    } break;
	 default: fprintf(stderr,"unknown option: %s\n", argv[i] ); break;
	 }
      } else {
	 fprintf(stderr,"unknown arg: %s\n", argv[i]);
      }
   }
   
   #define NEXT_EVENT        0
   #define PROCESSING_EVENT  1
   #define END_OF_RECORD     2
   #define END_OF_FILE       3
   int state=END_OF_RECORD;
   while(1){
      if( events_done >= event_limit ){ break; }
      switch(state){
      case END_OF_RECORD:
         if( next_record() <= 0 ){ state = END_OF_FILE; }
         else { state = NEXT_EVENT; }
         break;
      case NEXT_EVENT: // next midas event (can be multiple banks)
         if( next_event() < 0 ){ state = END_OF_RECORD; }
         else { state = PROCESSING_EVENT; }
         break;
      case PROCESSING_EVENT:
         if( process_event() < 0 ){ state = NEXT_EVENT; }
	 else { state = PROCESSING_EVENT; }
	 //if( event_pause ){ usleep(1000*event_pause); }
         break;
      case END_OF_FILE: cleanup(); exit(0);
      }
   }
   cleanup(); exit(0);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#define PEAK_INTERVAL 300
extern int midas_timestamp;
extern int analyse_peaks();
extern int finish_analysis();
extern int process_grif_event( Grif_event *, int *, int );
int process_grif_event(Grif_event *ptr, int *org_event, int orglen )
{
   static int ev;
   print_raw_event(org_event, orglen);
   if( ((++ev) % 1000) == 0 ){ fprintf(stderr, "%10d events ...\n", ev); }
   return(0);
}
int finish_analysis(){ return(0); }

/* loop over banks, looking for GRIF2 ones (or others ...)  */
/* The buffers returned are overwitten on subsequent calls */
int process_event()
{
   int i, bank_start, *bank_data, *reconst_ptr, reconst_size, items, evlen;
   time_t timestamp =midas_timestamp; 
   static int prev_timestamp = -1;
   char *bank_name;

   if( prev_timestamp == -1 ){ prev_timestamp = midas_timestamp; }
   if( midas_timestamp - prev_timestamp >= PEAK_INTERVAL ){
      prev_timestamp = midas_timestamp;
      fprintf(stderr,"%s ...\n", ctime(&timestamp) );
      //analyse_peaks();
   }
   while(1){
      if( (items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1); }
      if( strcmp(bank_name,"GRF3") == 0 || strcmp(bank_name,"GRF4") == 0 ){
	 bank_start = 1; /* new data bank */
         swapInt( (char *)bank_data, items*sizeof(int) );
	 //dump_bank(bank_data, items );
	 while( items > 0 ){
            evlen = unpack_grif3_bank( bank_data, items,&grif_event,waveforms);
	    if( evlen <= 0 ){ break; }
	    bank_data += evlen; items -= evlen;  grif_event.bank_start = bank_start;
	    if( events_done < event_skip ){ ++events_done; bank_start = 0; continue; }
            if( process_grif_event( &grif_event, bank_data-evlen, evlen ) ){
	       fprintf(stderr,"skipping %d items after error ...\n", items);
	       items = 0; bank_start = 0; break;
	    }
            if( event_pause ){ usleep(1000*event_pause); }
            ++events_done;  bank_start = 0; 
	 }
      }
   }
   return(-1); /* go to next event */
}

int cleanup(){ finish_analysis(); }
