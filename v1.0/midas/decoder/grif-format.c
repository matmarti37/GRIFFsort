#include "grif-format.h"

unsigned* grif_fragment;
unsigned grif_fragment_len;

int unpack_grif_bank(int *data, int length, Grif_event *evptr, int process_waveforms, short* waveform)
{

   unsigned int *evntbufend = (unsigned *)data + length;
   unsigned int *evntbuf = (unsigned *)data;
   unsigned *ptr = evntbuf;
 
   while( evntbuf < evntbufend ){
     if( ((*(ptr++)>>28)&0xff) == 0xE ){
       grif_fragment = evntbuf; grif_fragment_len = ptr-evntbuf;
       if( unpack_grif3_event( evntbuf, ptr-evntbuf, evptr, process_waveforms,waveform ) ){
	 return(-1);
       }
       return(ptr-evntbuf);
     }
   }
   return(0); 
}
/*================================================================*/
int unpack_grif3_event(unsigned *evntbuf, int evntbuflen, Grif_event *ptr, int process_waveforms,short* waveform)
{

    int  type, value, qtcount, master_port, grifc_port;
   unsigned val32, *evntbufend = evntbuf+evntbuflen, *evstrt=evntbuf;
   static int event_count;
   short *wave_ptr = NULL;

  
   qtcount = 0;
   ++event_count;
   memset(ptr, 0, sizeof(Grif_event) ); ptr->master_id = -1;
   if( ((*evntbuf) & 0x80000000) != 0x80000000 ){
      fprintf(stderr,"griffin_decode: bad header in event %d\n", event_count );
      //dump_event(evstrt,evntbuflen); return(-1);
   }
   while( evntbuf < evntbufend ){ val32 = *(evntbuf++);
      type = val32 >> 28; value = val32 & 0x0fffffff;
      switch( type ){
      case 0x8:                                            /*  Event header */
         if( evntbuf != evstrt+1 ){
            fprintf(stderr,"Event 0x%x(chan%d) 0x8 not at start of data\n",
               event_count, ptr->chan );
	 }
         ptr->dtype  = ((value & 0x0000F) >>  0);
         ptr->address= ((value & 0xFFFF0) >>  4);
	 ptr->chan   = ((value & 0x00FF0) >>  4);
         grifc_port  = ((value & 0x0F000) >> 12);
         master_port = ((value & 0xF0000) >> 16);
         ptr->chan +=  16* grifc_port;// 16 chan per grif16
         ptr->chan += 256*master_port;// 16 port per grifc[ => 256 chan/grifc]
	                              //4 port per master [ => 1k chan/master]
	 qtcount = 0;
         if( ptr->chan >= NUM_CHAN || ptr->chan < 0 ){ ptr->chan=NUM_CHAN-1; }
         wave_ptr  = &ptr->waveform_length;     /* should be zero here */

         // if network count not present, next 2 words are [mstpat/ppg mstid] in filtered data
	 if( ( *(evntbuf) >> 31 ) == 0 ){ val32 = *(evntbuf++);
	    ptr->wf_present = (val32 & 0x8000) >> 15;
	    ptr->pileup     = (val32 & 0x001F);
	 } // in unfiltered data, above word is "fake" master_id, and following word is missing
	 if( ( *(evntbuf) >> 31 ) == 0 ){ ptr->master_id   = *(evntbuf++); }
	 //if( dtype == 0xF ){
	 //fprintf(stderr,"Scalar: 0x%08x  0x%08x  0x%08x  0x%08x  0x%08x  ",
	 //*(evntbuf-1),*(evntbuf), *(evntbuf+1), *(evntbuf+2), *(evntbuf+3) );
	 //   fprintf(stderr,"0x%08x  0x%08x  ", *(evntbuf+4), *(evntbuf+5) );
	 //   fprintf(stderr,"0x%08x\n", *(evntbuf+6) );
	 //}
 	 break;
      case 0x9:                      /* Channel Trigger Counter [AND MODE] */
         ptr->trig_req =  value & 0x0fffffff;
         break;
      case 0xa:                                           /*  Time Stamp Lo */
         if( ptr->timestamp == 0 ){ // TEMP DURING WAVEFORM BUG
            ptr->timestamp   |= ( value & 0x0fffffff );
         }
         break;
      case 0xb:                               /* Time Stamp Hi and deadtime */
	 ptr->timestamp   |= ( (long)(value & 0x0003fff) << 28);
	 ptr->deadtime     = ( (value & 0xfffc000) >> 14);
	 break;
      case 0xc:                                             /* waveform data */
         if( wave_ptr == NULL ){
            fprintf(stderr,"griffin_decode: no memory for waveform\n");
         } else if( process_waveforms == 1 ){/* + 14->16bit sign extension */
	    waveform[(*wave_ptr)  ]   = value & 0x3fff;
            waveform[(*wave_ptr)++] |= ((value>>13) & 1) ? 0xC000 : 0;
	    waveform[(*wave_ptr)  ]   =(value & 0xfffc000) >> 14;
            waveform[(*wave_ptr)++] |= ((value>>27) & 1) ? 0xC000 : 0;
	    //if( done == 0 ){
	    //   for(i=0; i<evntbuflen; i++){
	    //	  fprintf(stderr,"  0x%08x", *(evstrt+i) );
	    //	  if( ((i+1) % 6 ) == 0 ){ fprintf(stderr,"\n    "); }
	    //   }
	    //   if( (i % 6 ) != 0 ){ fprintf(stderr,"\n"); }
	    //   done = 1;
	    //}
	 }
	 break;
      case 0xd:                                   /* network packet counter */
         ptr->net_id = val32;
         // next 2 words are [mstpat/ppg mstid] in filtered data
	 if( ( *(evntbuf) >> 31 ) == 0 ){ val32 = *(evntbuf++);
	    ptr->wf_present = (val32 & 0x8000) >> 15;
	    ptr->pileup     = (val32 & 0x001F);
	 } // in unfiltered data, above word is "fake" master_id, and following word is missing
	 if( ( *(evntbuf) >> 31 ) == 0 ){ ptr->master_id   = *(evntbuf++); }
	 break;
      case 0xe:      // 14bit acc 14bit req                      /* Event Trailer */
         if( evntbuf != evntbufend ){
            fprintf(stderr,"Event 0x%x(chan%d) 0xE before End of data\n",
               event_count, ptr->chan );
	 }
	 ptr->trig_acc = (val32 & 0xfffc000) >> 14;
	 if( (val32 & 0x3fff) != (ptr->trig_req & 0x3fff) && ptr->dtype != 0xf ){
            fprintf(stdout,"Event 0x%x(chan%d) trig_req[%d] != trailer_trig_req[%d]\n",
		    event_count, ptr->chan, (ptr->trig_req & 0x3fff), (val32 & 0x3fff) );
            fprintf(stderr,"Event 0x%x(chan%d) trig_req[%d] != trailer_trig_req[%d]\n",
		    event_count, ptr->chan, (ptr->trig_req & 0x3fff), (val32 & 0x3fff) );
	 }
         //ptr->pileup     = (val32 & 0x001F);	 // not here anymore for sure !!!
         break;
      case 0x0: case 0x1: case 0x2: case 0x3:
      case 0x4: case 0x5: case 0x6: case 0x7: 
	 if( evntbuf - evstrt < 4 ){  // header stuff (with no 0xd present)
	    // next 2 words are [mstpat/ppg mstid] in filtered data
	    ptr->wf_present = (val32 & 0x8000) >> 15;
	    ptr->pileup     = (val32 & 0x001F);
	    if( ( *(evntbuf) >> 31 ) == 0 ){ ptr->master_id   = *(evntbuf++); }
	    break;
	 } else { // if dtype=6, maybe RF - extend sign from 30 to 32bits
	    if( ptr->dtype == 6 && (val32 & (1<<29)) ){ val32 |= 0xC0000000; }
	    if( ++qtcount == 1 ){                                /* Energy */
	       ptr->energy  = (ptr->dtype==6) ? val32 : val32 & 0x01ffffff;
	       ptr->e_bad   = (value >> 25) & 0x1;
	       ptr-> integ |= ((val32 & 0x7c000000) >> 17); ptr->nhit = 1;
	    } else if( qtcount == 2 ){                         /* CFD Time */
               ptr->cfd     = (ptr->dtype==6) ? val32 : val32 & 0x003fffff;
	       ptr-> integ |= ((val32 & 0x7FC00000) >> 22);
            } else if( qtcount == 3 ){
	       if(ptr->dtype==6){ ptr->cc_long  = val32; }  /* descant long*/
	       else { ptr->integ2 =   val32 & 0x003FFF;
		      ptr->nhit   = ((val32 & 0xFF0000) >> 16); }
	    } else if( qtcount == 4 ){
	       if(ptr->dtype==6){ ptr->cc_short  = val32; } /* descant short*/
	       else { ptr->energy2 =  val32 & 0x3FFFFF;
		      ptr->e2_bad  = (val32 >> 25) & 0x1; }
            } else if( qtcount == 5 ){
	       ptr->integ3 =   val32 & 0x00003FFF;
	       ptr->integ4 = ((val32 & 0x3FFF0000) >> 16);
	    } else if( qtcount == 6 ){ ptr->energy3 =  val32 & 0x3FFFFF;
	                               ptr->e4_bad  = (val32 >> 25) & 0x1;
	    } else if( qtcount == 7 ){ ptr->energy4 =  val32 & 0x3FFFFF;
	                               ptr->e4_bad  = (val32 >> 25) & 0x1;
	    } else {
	       fprintf(stderr,"Event 0x%x(chan%d) excess PH words\n",
               event_count, ptr->chan );
	    }
            break;
         }
      case 0xf: fprintf(stderr,"griffin_decode: 0xF.......\n");
                /* Unassigned packet identifier */ return(-1);
      default:  fprintf(stderr,"griffin_decode: default case\n"); return(-1);
      }
   }
  return 0;
}
/*================================================================*/
void print_fragment_info(Grif_event *ptr,int time_offset)
{
  int time;
  time=ptr->cfd&0x00ffffff;
  time-=(ptr->timestamp*16)&0x00ffffff;
  time+=time_offset;
  printf("=========================================================\n");
  printf(" Trigger  number : %8d 0x%8.8x\n",ptr->trigger_num&0x0fffffff,ptr->trigger_num);
  printf("             CFD : %8d 0x%8.8x\n",ptr->cfd,ptr->cfd);
  printf("      Time Stamp : %8ld 0x%8.8lx\n",ptr->timestamp,ptr->timestamp);
  printf("            Time : %8d 0x%8.8x\n",time, time);
  printf(" Waveform length : %8d 0x%8.8x\n",ptr->waveform_length,ptr->waveform_length);
}
