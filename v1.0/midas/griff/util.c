#include <stdio.h>
#include <time.h>       /* time() */

#include "grif-format.h"

extern int *grif_fragment;
extern int grif_fragment_len;
extern int midas_timestamp;
extern long midas_bytes;


#define IGNORE_SCALARS 1 // dtype=0xf is not really scalar

#define LINEWORD 24
int dump_fragment(FILE *stream)
{
   int i;
   fprintf(stream,"      ");
   for(i=0; i<grif_fragment_len; i++){
      if( ((i % LINEWORD ) == 0) && (i != 0) ){ fprintf(stream,"\n      "); }
      if( i == 1 && (grif_fragment[i] & 0xf0000000 ) != 0xd0000000 ){
	 fprintf(stream,"            ");
      }
      // TEMP DURING WAVEFORM BUG
      if( i>0 && (((grif_fragment[i  ]>>28) & 0xF) == 0xA) &&
          (((grif_fragment[i-1]>>28) & 0xF) == 0xB) ){ continue; }
      fprintf(stream,"0x%08x  ", grif_fragment[i] );
   }
   if( (i % LINEWORD ) != 0 ){ fprintf(stream,"\n"); }
   return(0);
}

#define INTERVAL     5
int show_status_line(int evlen)
{
   static int ev, bytes, last_ev, last_bytes;
   static time_t last_time=-1;
   time_t curr_time = time(NULL);
   float mbytes, mbytes_org;
   static int eventnum;

   mbytes_org = midas_bytes/1000000.0;
   ++ev;  eventnum = ev; bytes += evlen; mbytes = bytes/1000000.0;
   if( last_time == -1 ){ last_time = curr_time; }
   if( curr_time - last_time >= INTERVAL ){
      fprintf(stderr, "%10d events ...  %6.1f Mbytes ... ", ev, mbytes);
      fprintf(stderr, " %6d ev/s  %8.1f kbytes/s\n", (ev-last_ev)/ INTERVAL,
	                             (bytes-last_bytes)/(1024.0*INTERVAL) );
      last_ev=ev;  last_bytes=bytes;  last_time = curr_time;
   }
   //print_reconstructed_event(ptr, 10, 0);
   if( ((++ev) % 50000) == 0 ){
      fprintf(stderr, "%10d events ...  %6.1f Mbytes [%6.1f]\n", ev, mbytes, mbytes_org);
   }
}

#define SORT_UNFILTERED 1

#define MAX_CHAN 1024
int check_grif_event(Grif_event *ptr, int *org_event, int orglen )
{
   static int  last_k[MAX_CHAN], last_trig[MAX_CHAN], last_atrig[MAX_CHAN];
   static int  last_e[MAX_CHAN], last_cfd[MAX_CHAN],  seen_evt[MAX_CHAN];
   static long last_ts[MAX_CHAN];
   static time_t prev_midastime = -1;
   static int last_netpkt = -1;
   static int last_mstid  = -1;
   static int event  = 0;
   static long last_ts_evt  = 0;
   static int start_timestamp;
   int i, j, k, m, ph, integ, diff, trig, atrig, cfd, lowts, chan, wlen;
   float dts_us;
   long ts;

   ++event;
   
   if( start_timestamp == -1 ){ start_timestamp = midas_timestamp; }

   if( ptr->net_id != 0 ){
//      fprintf(stdout,"NETPKTSTART event %6d netid %6d [+%d]\n",
//	      event, ptr->net_id & 0xfffffff, ptr->net_id - last_netpkt );
      if( last_netpkt == -1 ){ last_netpkt = ptr->net_id; }
      else {
	 if( ptr->net_id != last_netpkt + 1 ){
	    fprintf(stdout,"ERROR event %6d - missed %d net pkts [%d to %d]\n",
		    event,  ptr->net_id - 1 - last_netpkt, last_netpkt, ptr->net_id );
	 }
	 last_netpkt = ptr->net_id;
      }
   }
   
   // SCALAR - print data and exit here
   if( ptr->dtype == 0xf && !IGNORE_SCALARS){ 
      fprintf(stdout,"     Chan:%2d Scalars 0x%08x 0x%08x 0x%08x 0x%08x ",
	      chan, 0, 0, 0, 0 );
      dump_fragment(stdout);
      return(0);
   }
   if( ptr->dtype == 0xf ){ return(0); }


   if( ptr->master_id == -1 ){
      // fprintf(stdout,"UNFILTERED EVENT\n"); dump_fragment(stdout);
      if( ! SORT_UNFILTERED ){ return(0); }
   }
   else if( last_mstid == -1 ){ last_mstid = ptr->master_id; }
   else {
      if( ptr->master_id != last_mstid + 1 ){
         //fprintf(stdout,"ERROR event %6d - missed %d mst id [%d to %d]\n",
         //	 event, ptr->master_id - 1 - last_mstid, last_mstid, ptr->master_id );
      }
      last_mstid = ptr->master_id;
      if( SORT_UNFILTERED ){ return(0); }
   }

   if( (chan = ptr->chan) >= MAX_CHAN ){
      fprintf(stdout,"ERROR chan %d out of range 0-%d\n", chan, MAX_CHAN );
      return(-1);
   }
   trig = ptr->trig_req;  atrig = ptr->trig_acc;
   ts  = ptr->timestamp;  cfd = ptr->cfd;  dts_us = (ts-last_ts[chan])/100.0;
   wlen = ptr->waveform_length;  lowts = ts & 0x0003ffff;  
   integ = ptr->integ; if( integ >= 8192 ){ integ -= 16384; }
   ph = (ptr->e_bad) ? 0 : ( 1.0 * ptr->energy / ( (ptr->integ==0) ? 1 : ptr->integ ) );

   if( ! SORT_UNFILTERED ){ // filter time ordering check
      //dump_fragment(stdout);
      //if( ts >= last_ts_evt ){ last_ts_evt = ts; return(0); }
      if( ts < last_ts_evt ){
         fprintf(stdout,"ERROR TIME ORDERING\n" );
      }
   }
   
   fprintf(stdout,"     Chan:%2d Ph[K]:%8d[%6d]  CFD-ts[", chan, ph, ptr->integ);
   fprintf(stdout,"cfd,ts][ts-prvchn][ts-prvevt]:%10d[0x%06x,0x%08lx]", cfd-16*lowts,cfd,ts);
   //fprintf(stdout,"[%8.2f][%8.2f]", dts_us, (ts-last_ts_evt)/100.0 );
   fprintf(stdout,"[%8.2f][%10ld]", dts_us, ts-last_ts_evt );
   if( ts < last_ts_evt ){
      fprintf(stdout,"**");
   } else { fprintf(stdout,"  "); }
   fprintf(stdout,"trig:%10d[+%3d]", trig, trig-last_trig[chan] );
   fprintf(stdout,"atrig:%10d[+%3d]", atrig, atrig-last_atrig[chan] );
   dump_fragment(stdout);  //fprintf(stdout,"\n");

   if( seen_evt[chan] ){
      if( trig != last_trig[chan]+1 ){
         fprintf(stdout,"ERROR event %6d - Chan %2d - missed %d trig_req [%d to %d]\n",
		 event, chan, trig  - 1 - last_trig[chan] , last_trig[chan], trig );
      }
      if( atrig != last_atrig[chan]+1 ){
         fprintf(stdout,"ERROR event %6d - Chan %2d - missed %d trig_acc [%d to %d]\n",
		 event, chan, atrig - 1 - last_atrig[chan], last_atrig[chan], atrig );
      }
   }
   
   seen_evt[chan] = 1;  last_ts_evt = ts;
   last_e[chan] = ph;   last_cfd[chan] = cfd;  last_k[chan] = ptr->integ;
   last_ts[chan] = ts;  last_trig[chan] = trig; last_atrig[chan] = atrig;
   return(0);
}
