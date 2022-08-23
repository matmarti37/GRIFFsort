#include "sort_and_assemble_list.h"
int map_event(raw_event* data,node *ptr, gmap* map)
{

  unsigned long long tsns_min,tsns_max;
  int pos,col,seg;
  int take,id;
  unsigned long long int one=1;

  if(data->h.frag_fold==0)
    {
      data->h.trig_num=ptr->trig;
      	data->h.timestamp_min=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_min=(ptr->tsns>>24)&0x00ffffff;
	data->h.timestamp_max=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_max=(ptr->tsns>>24)&0x00ffffff;
    }
  
  
  if(data->h.trig_num!=ptr->trig)
    {
      printf("Error in mapping, wrong trigger %d %d\n", data->h.trig_num,ptr->trig);
      printf("Exiting\n");
      exit(0);
    }
  data->h.frag_fold++;

  tsns_min=(data->h.timestamp_up_min<<31)+data->h.timestamp_min;
  tsns_max=(data->h.timestamp_up_max<<31)+data->h.timestamp_max;


   if(tsns_min<ptr->tsns)
     {
	data->h.timestamp_min=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_min=(ptr->tsns>>24)&0x00ffffff;
      }
   
   if(tsns_max>ptr->tsns)
     {
	data->h.timestamp_max=ptr->tsns&0x00ffffff;
	data->h.timestamp_up_max=(ptr->tsns>>24)&0x00ffffff;
      }
   
   /***************************** Start TIGRESS HPGe ***********************/
   if(ptr->chan>=map->tig_min)
     if(ptr->chan<=map->tig_max)
       {
	 take=0;
	 //map central contacts and segments
	 if((seg=map->hpge_lt[ptr->chan-map->tig_min].seg)>=0)//valid segment
	   if(seg<NSEGTIGR)//valid segment
	      if((pos=map->hpge_lt[ptr->chan-map->tig_min].pos)>0)//valid position
		if(pos<NPOSTIGR)//valid position
		  if((col=map->hpge_lt[ptr->chan-map->tig_min].col)>=0)//valid color
		    if(col<NCOL)//valid color  	       
		      {
			if(ptr->ch.charge>0)
			  {
			    //data->tg.det[pos].ge[col].seg[seg].charge=ptr->ch.charge;
			    data->tg.det[pos].ge[col].seg[seg].charge=ptr->ch.charge/map->tig_kpar;
			    data->tg.det[pos].ge[col].h.EHP|=(one<<seg);
			    data->tg.det[pos].ge[col].h.Efold++;
			    take|=1;
			  }

			if(ptr->ch.cfd>=0)
			  {			
			    data->tg.det[pos].ge[col].seg[seg].cfd=ptr->ch.cfd;
			    data->tg.det[pos].ge[col].h.THP|=(one<<seg);
			    data->tg.det[pos].ge[col].h.Tfold++;
			    take|=1;
			  }		
		      }
	 
	 if(take==1)
	   {
	     data->h.setupHP|=TIGRESS_BIT;
	     
	     data->tg.det[pos].ge[col].seg[seg].timestamp=ptr->ch.timestamp;
	     data->tg.det[pos].ge[col].seg[seg].timestamp_up=ptr->ch.timestamp_up;
	     data->tg.det[pos].ge[col].h.TSHP|=(one<<seg);
	     data->tg.det[pos].ge[col].h.TSfold++;

	     //count crystals
	     id=(pos-1)*NCOL+col;
	     if((data->tg.g.GeHP&(one<<id))==0)
	       {
		 data->tg.g.GeHP|=(one<<id);
		 data->tg.g.Gefold++;
	       }
	     if((data->tg.g.THP&(one<<id))==0)
	       {
		 data->tg.g.THP|=(one<<id);
		 data->tg.g.Tfold++;
	       }
	     //count positions
	     id=pos-1;
	     if((data->tg.g.PosHP&(one<<id))==0)
	       {
		 data->tg.g.PosHP|=(one<<id);
		 data->tg.g.Posfold++;
	       }
	     //count clovers
	     if((data->tg.h.GeHP&(one<<id))==0)
	       {
		 data->tg.h.GeHP|=(one<<id);
		 data->tg.h.Gefold++;
	       }
	     
	     //count crystals within a clover
	     if((data->tg.det[pos].h.GeHP&(one<<col))==0)
	       {
		 data->tg.det[pos].h.GeHP|=(one<<col);
		 data->tg.det[pos].h.Gefold++;
	       }
	     
	   }  
       }
   /***************************** End   TIGRESS HPGe ***********************/

   /***************************** Start TIGRESS BGO  ***********************/

  if(ptr->chan>=map->tig_min)
     if(ptr->chan<=map->tig_max)
       {
	 take=0;
	 if((seg=map->supp_lt[ptr->chan-map->tig_min].seg)>0)//valid segment
	   if(seg<NSUP)//valid segment
	      if((pos=map->supp_lt[ptr->chan-map->tig_min].pos)>0)//valid position
		if(pos<NPOSTIGR)//valid position
		  if((col=map->supp_lt[ptr->chan-map->tig_min].col)>=0)//valid color
		    if(col<NCOL)//valid color  	       
		      {
			if(ptr->ch.charge>0)
			  {
			    data->tg.det[pos].bgo[col].sup[seg].charge=ptr->ch.charge;
			    data->tg.det[pos].bgo[col].h.EHP|=(one<<seg);
			    data->tg.det[pos].bgo[col].h.Efold++;
			    take|=1;
			  }

			if(ptr->ch.cfd>=0)
			  {			
			    data->tg.det[pos].bgo[col].sup[seg].cfd=ptr->ch.cfd;
			    data->tg.det[pos].bgo[col].h.THP|=(one<<seg);
			    data->tg.det[pos].bgo[col].h.Tfold++;
			    take|=1;
			  }		
		      }

	 if(take==1)
	   {
	     data->h.setupHP|=TIGRESS_BIT;		      
	     data->tg.det[pos].bgo[col].sup[seg].timestamp=ptr->ch.timestamp;
	     data->tg.det[pos].bgo[col].sup[seg].timestamp_up=ptr->ch.timestamp_up;
	     data->tg.det[pos].bgo[col].h.TSHP|=(one<<seg);
	     data->tg.det[pos].bgo[col].h.TSfold++;
		      
	     //count crystals
	     id=(pos-1)*NCOL+col;
	     if((data->tg.g.BGOHP&(one<<id))==0)
	       {
		 data->tg.g.BGOHP|=(one<<id);
		 data->tg.g.BGOfold++;
	       }
	     if((data->tg.g.THP&(one<<id))==0)
	       {
		 data->tg.g.THP|=(one<<id);
		 data->tg.g.Tfold++;
	       }
	     //count positions
	     id=pos-1;
	     if((data->tg.g.PosHP&(one<<id))==0)
	       {
		 data->tg.g.PosHP|=(one<<id);
		 data->tg.g.Posfold++;
	       }
	     //count clovers
	     if((data->tg.h.BGOHP&(one<<id))==0)
	       {
		 data->tg.h.BGOHP|=(one<<id);
		 data->tg.h.BGOfold++;
	       }
	     //count crystals within a clover
	     if((data->tg.det[pos].h.BGOHP&(one<<col))==0)
	       {
		 data->tg.det[pos].h.BGOHP|=(one<<col);
		 data->tg.det[pos].h.BGOfold++;
	       }
	   }	 
       }
   
   /***************************** End   TIGRESS BGO  ***********************/
   /***************************** Start TIP           **********************/
 if(ptr->chan>=map->csiarray_min)
    if(ptr->chan<=map->csiarray_max)
      {
	id=ptr->chan-map->csiarray_min;
	pos=map->csi_lt[id];
	if(pos>0)
	  if(pos<NCSI)
	    {
	      take=0;
	      if(ptr->ch.charge>0)
		{
		  data->csiarray.csi[pos].charge=ptr->ch.charge;
		  data->csiarray.h.Efold++;
		  data->csiarray.h.EHP[pos/64]=(one<<pos%64);		 
		  take|=1;
		}
	      if(ptr->ch.cfd>0)
		{
		  data->csiarray.csi[pos].cfd=ptr->ch.cfd;
		  data->csiarray.h.Tfold++;
		  data->csiarray.h.THP[pos/64]|=(one<<pos%64);		 
		  take|=1;
		}
	      if(take==1)
		{
		  data->csiarray.csi[pos].timestamp=ptr->ch.timestamp;
		  data->csiarray.csi[pos].timestamp_up=ptr->ch.timestamp_up;
		  data->csiarray.h.TSfold++;
		  data->csiarray.h.TSHP[pos/64]|=(one<<pos%64);
		  data->h.setupHP|=CsIArray_BIT;
		  memcpy(&data->csiarray.wfit[pos],&ptr->wfit,sizeof(ShapePar));
		  data->csiarray.t0[pos]=ptr->wfit.t[0];
		}
	     
	    }
      }
  /***************************** End TIP             **********************/
  
  return 0;
}

/*================================================================*/
int sort_list(data_pointers* dp, node* list)
{
  int i;
  node store;
  //position the last element in the right spot
  if(dp->last-1==0)//at the start, nothing to order
    {
      //     printf("on start, no sorting\n");
      return 1;
    }
  
  if(list[dp->last-1].tsns>=list[dp->last-2].tsns)//already in order, do nothing
     {
       //    printf("in order\n");
       return 1;
     } 

 
  memcpy(&store,&list[dp->last-1],sizeof(node));//store the last element

  if(dp->last>S8K)
    i=store.tsns/list[dp->last-S1K].tsns*(dp->last-S1K);//approximate position
  else
    i=dp->last-2;//pointer to the position before the last added element
  
  while(store.tsns>list[i].tsns)
    i++;  

  while(store.tsns<list[i].tsns)
    {
      i--;
      if(i==-1) break;
    }
  
  if(i==-1)//shift the whole list
    {
      memmove(&list[1],&list[0],(dp->last-1)*sizeof(node));
      memcpy(&list[0],&store,sizeof(node));
      return 1;
    }
 
  memmove(&list[i+2],&list[i+1],(dp->last-i-1)*sizeof(node));
  memcpy(&list[i+1],&store,sizeof(node));

  return 1;
}
/*================================================================*/
/* void sort_and_assemble_subruns(char* subrun_list_name, char* map_name) */
/* { */
/*   FILE* subrun_list; */
/*   FILE* input; */
/*   char name[132]; */
/*   static gmap map; */
/*   int state=END_OF_RECORD; */
/*   int stop=0; */
/*   data_pointers* dp=NULL; */
/*   node*          list; */

/*  /\* open the list of subrun midas files *\/ */
/*   if((subrun_list=fopen(subrun_list_name,"r"))==NULL) */
/*     { */
/*       printf("ERROR!!! I can't open the subrun midas file list!\n"); */
/*       exit(-2); */
/*     } */

/*   /\* read name of first input file *\/ */
/*   if(fscanf(subrun_list,"%s",name)==EOF) */
/*     { */
/*       printf("ERROR!!! the subrun file name not read properly!\n"); */
/*       exit(-2); */
/*     } */

/*  /\* open the first input file*\/ */
/*   if((input=fopen(name,"r"))==NULL) */
/*     { */
/*       printf("\nI can't open input file %s\n",name); */
/*       exit(-2); */
/*     } */
/*    /\*initialize the sort *\/ */
/*   dp=(data_pointers*)malloc(sizeof(data_pointers)); */
/*   dp->proc=0; */
/*   dp->son=sizeof(node); */
/*   dp->last=0; */
/*   dp->trig=0; */

  
/*   printf("Allocating %ld MB of RAM for reconstructing events\n",DEPTH*dp->son/sizeof(char)/1024/1024); */

/*   list=(node*) malloc(DEPTH*dp->son); */
/*   memset(list,0,DEPTH*dp->son); */

/* /\* get the map *\/ */
/*   read_map(map_name,&map); */
  
/*   while(stop==0){ */
/*     switch(state){ */
/*     case END_OF_RECORD: */
/*       if( next_record(input) <= 0 ){ state = END_OF_FILE;} */
/*       else {state = NEXT_EVENT;} */
/*       break; */
/*     case NEXT_EVENT: */
/*       if( next_event() < 0 ){ state = END_OF_RECORD; } */
/*       else { state = GET_FRAGMENTS; } */
/*       break; */
/*     case GET_FRAGMENTS: */
/*       if( get_fragments_for_assembly(dp,list,&map) < 0 ) */
/* 	{ state = NEXT_EVENT;} */
/*       else { state = GET_FRAGMENTS;  } */
/*       break; */
/*     case END_OF_FILE: */
/*       fclose(input); */
/*       printf("\n Number of analyzed midas banks is %8ld\n",dp->proc); */
/*       printf("\n"); */
/*       /\* read the name of the next input file *\/ */
/*       if(fscanf(subrun_list,"%s",name)==EOF){ state = END_OF_SORT; } */
/*       else */
/* 	{ */
/* 	  /\* open the next file *\/ */
/* 	  if((input=fopen(name,"r"))==NULL) */
/* 	    { */
/* 	      printf("\nI can't open input file %s\n",name); */
/* 	      exit(-2); */
/* 	    } */
/* 	  /\* sort next file *\/ */
/* 	  state = END_OF_RECORD; */
/* 	} */
/*       break; */
/*     case END_OF_SORT: */
/*       /\* close the midas list *\/ */
/*       fclose(subrun_list); */
/*       /\* analyze the last data assembly buffer *\/ */
/*       analyze_list(dp->last,dp->trig,list);   */
/*       stop=1; */
/*       break; */
/*     default: */
/*       printf("Unknown case\n"); */
/*       exit(0); */
/*       break; */
/*     } */
/*   } */

  
/* } */
/*================================================================*/
int add_node(node* nd, data_pointers* dp, node* list)
{

    if(dp->last==DEPTH)
    {
      memmove(&list[0],&list[SHIFT],(DEPTH-SHIFT)*sizeof(node));
      memset(&list[DEPTH-SHIFT],0,SHIFT*dp->son);    
      dp->last-=SHIFT;
      dp->trig+=SHIFT;  
    }

  //if early tsns comes after shifts, warn and terminate
  if(dp->trig!=0)
    if(nd->tsns<list[0].tsns)
      {
	printf("Reconstruction error, early tsns comes late\n");
	printf("Tsns  %16lld  first tsns on list %16lld last tsns on the list %16lld\n",nd->tsns,list[0].tsns,list[dp->last-1].tsns);
	printf("Correct DEPTH and SHIFT, recompile, try again\n");
	printf("Exiting\n");
	exit(0);
      }
 

  memcpy(&list[dp->last],nd,dp->son);
  dp->last++;
  sort_list(dp,list);

  //  print_list(dp->last,0,list);getc(stdin);
  return 0;
}

/*================================================================*/
int analyze_fragment_for_assembly(Grif_event* ptr, short* waveform,data_pointers* dp, node* list,gmap* map)
{
  long long tsns;
  node nd;
  WaveFormPar wpar;
  int d;
  
  //CFD timing from online DAQ CFD
  tsns=(ptr->timestamp&0xfffffffffffc0000)<<4;
  tsns+=ptr->cfd;
  tsns*=10;
  tsns/=16;
  nd.tsns=tsns;

  nd.trig_tsns=0x000000000000;
  //nd.csi_tsns=0x000000000000;

  // nd.ts=ptr->timestamp;
  nd.ch.cfd=ptr->cfd;
  nd.chan=ptr->chan;
  nd.ch.charge=ptr->energy;
  nd.ch.timestamp=(int)(ptr->timestamp&0xffffffff);
  nd.ch.timestamp_up=(int)((ptr->timestamp>>32)&0xffff);
  nd.trig=-1;
  nd.tig_trig=-1;
  nd.csi_trig=-1;
  memset(&nd.wfit,0,sizeof(ShapePar));

  //verify that upper bits of the timestamp, tsup, is being correctly written by the DAQ
  //this chunk of code relies on set up that occurs in midas2list
  //initialization should have prev_TSUP = 0 and max_TSUP < 0

  if(max_TSUP>=0)
    if(nd.ch.timestamp_up>=max_TSUP)
      printf("Dropping fragment due to tsup being too high.\n");
      return 0;

  if(prev_TSUP>=0)
    {
      if((prev_TSUP-nd.ch.timestamp_up)>1)
	{
	  printf("Dropping fragment due to tsup error.\n");
	  //printf("Energy: %d\n", ptr->energy);
	  //printf("TSUP: %d\n", nd.ch.timestamp_up);
	  //printf("Prev: %d\n", prev_TSUP);
	  return 0;
	}
      
      prev_TSUP=nd.ch.timestamp_up;
    }
    
  
  //for TIP channels do the fits
  if(nd.chan>=map->csiarray_min)
    if(nd.chan<=map->csiarray_max)
      if(map->csiarray_fit==1)
	if(map->csi_lt[nd.chan-map->csiarray_min]>0)
	  if(map->csi_lt[nd.chan-map->csiarray_min]<NCSI)
	    if((d=ptr->waveform_length)!=0)
	      {
		nd.wfit.t[1]=map->csiarray_trc; //set tRC
		nd.wfit.t[2]=map->csiarray_tf; //set tF
		nd.wfit.t[3]=map->csiarray_ts; //set tS
		nd.wfit.t[4]=map->csiarray_tr; //set tGamma
		fit_CsI_waveform(d,waveform,&nd.wfit,&wpar);
		//for a fit with type>0 overwrite the timing with the t0 from fit
		if(nd.wfit.type>0)
		  {
		    //		    printf("Old tsns %16lld   ",tsns);
		    tsns=(long long)(10.*((double)ptr->timestamp+nd.wfit.t[0]-(double)map->csiarray_pretrig));
		    if(tsns<0)
		      {
			printf("Dropping fragment with tsns = %lld as derived from TIP fit.\n",tsns);
			return 0;
		      }
		    nd.tsns=tsns;
		    //		    printf("New tsns %16lld\n",tsns);
		    //		    getc(stdin);
		  }
		
		/* print_ShapePar(&nd.wfit); */
		/* getc(stdin); */
	      }
	      
  /* if(nd.ch.cfd<2) */
  /*   return 0; */
  
  add_node(&nd,dp,list);
 

  return 0;
}

/*================================================================*/
void sort_and_assemble(char* inp_name, char* map_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0;
  static gmap    map;
  data_pointers* dp=NULL;
  node*          list;

 /* open the input file*/
  if((input=fopen(inp_name,"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",inp_name);
      exit(-2);
    }
 
  /*initialize the sort */
  dp=(data_pointers*)malloc(sizeof(data_pointers));
  dp->proc=0;
  dp->son=sizeof(node);
  dp->last=0;
  dp->trig=0;

  printf("Allocating %ld MB of RAM for reconstructing events\n",DEPTH*dp->son/sizeof(char)/1024/1024);

  list=(node*) malloc(DEPTH*dp->son);
  memset(list,0,DEPTH*dp->son);

  /* get the map */
  read_map(map_name,&map);
  
  while(stop==0){
    switch(state){
    case END_OF_RECORD:
      if( next_record(input) <= 0 ){ state = END_OF_FILE;}
      else {state = NEXT_EVENT;}
      break;
    case NEXT_EVENT:
      if( next_event() < 0 ){ state = END_OF_RECORD; }
      else { state = GET_FRAGMENTS; }
      break;
    case GET_FRAGMENTS:
      if( get_fragments_for_assembly(dp,list,&map) < 0 )
	{ state = NEXT_EVENT;}
      else
	{ state = GET_FRAGMENTS;  }
      break;
    case END_OF_FILE:
      fclose(input);
      printf("\n Number of analyzed midas banks is %8ld\n",dp->proc);
      printf("\n");
      analyze_list(dp->last,dp->trig,list);
      stop=1;
      break;
    default:
      printf("Unknown case\n");
      exit(0);
      break;
    }
  }
}
  


/*================================================================*/
int get_fragments_for_assembly(data_pointers* dp, node* list,gmap *map)
{
  int *bank_data, items;
  char *bank_name;
  
  
  /* loop over banks, looking for GRFFIN   */
  while(1)
    {
      if((items = next_bank( &bank_name, &bank_data )) < 0 ){ return(-1);}
      if( strcmp(bank_name,"GRF3") == 0 || strcmp(bank_name,"GRF4") == 0)
	{
	  swapInt( (char *)bank_data, items*sizeof(int) );
	  
	  unpack_grif_bank_for_assembly( bank_data, items, dp, list, map);
	  
	  if((dp->proc%10000)==0){printf("Number of analyzed GRF3/GRF4 banks is %8ld\r",dp->proc);}    
	  dp->proc++;
	}
    }
   return(-1); /* go to next event */
}

/*================================================================*/
int unpack_grif_bank_for_assembly(int *data, int length, data_pointers* dp, node* list, gmap* map)
{
 
   unsigned int *evntbufend = (unsigned *)data + length;
   unsigned int *evntbuf = (unsigned *)data;
   unsigned *ptr = evntbuf;
   Grif_event grif_event;
   short waveform[MAX_SAMPLE_LEN];
   int process_waveforms=1;
 
   while( evntbuf < evntbufend ) //scan the bank until the end given by length
     if( ((*(ptr++)>>28)&0xff) == 0xE )//advance the ptr until the end of the header
       {
	 //unpack if the end of the header has been reached
	 if(unpack_grif3_event(evntbuf, ptr-evntbuf, &grif_event, process_waveforms,waveform)==0)
	   analyze_fragment_for_assembly(&grif_event,waveform,dp,list,map);
	   
	 evntbuf=ptr;

       }
   

   return(0); 
}

/*================================================================*/
int print_list(int limit, int offset, node* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16lld Ch %4d Ts_up %8u Ts %8u CFD %8u TigTrig %8d CsITrig %8d TrigTs[ns] %16lld Trig %8d\n",i+offset,(unsigned int)list[i].tsns,list[i].chan,(unsigned int)list[i].ch.timestamp_up,(unsigned int)list[i].ch.timestamp,(unsigned int)list[i].ch.cfd,list[i].tig_trig,list[i].csi_trig,list[i].trig_tsns,list[i].trig);
  
  return 0;
}
/*================================================================*/
int store_list(int limit, node* list,FILE* out)
{
  int i;
  size_t son;
  son=sizeof(node);
  for(i=0;i<limit;i++)
    fwrite(&list[i],son,1,out);
  
  return 0;
}
/*================================================================*/
int same_HPGe(node* a, node* b, gmap* map)
{
  if(a->chan>=map->tig_min)
    if(a->chan<=map->tig_max)
      if((a->ch.timestamp|a->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[a->chan-map->tig_min].pos>0)//valid position for a
	  if(map->hpge_lt[a->chan-map->tig_min].pos<NPOSTIGR)//valid position for a
	    if(b->chan>=map->tig_min)
	      if(b->chan<=map->tig_max)
		if((b->ch.timestamp|b->ch.timestamp_up)!=0)//ignore bad events at the start
		  if(map->hpge_lt[b->chan-map->tig_min].pos>0)//valid position for b
		    if(map->hpge_lt[b->chan-map->tig_min].pos<NPOSTIGR)//valid position for b
		      if(map->hpge_lt[a->chan-map->tig_min].pos==map->hpge_lt[b->chan-map->tig_min].pos)//same position
			if(map->hpge_lt[a->chan-map->tig_min].col==map->hpge_lt[b->chan-map->tig_min].col)//same color		      
			  return 1;
  
  return 0;	      
}
/*================================================================*/
int Seg_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[curr->chan-map->tig_min].seg>0)//channel is a segment
	  if(map->hpge_lt[curr->chan-map->tig_min].seg<NSEGTIGR)//channel is a segment 
	    if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//valid position
	      if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid position
		return 1;
  
  return 0;	      
}
/*================================================================*/
int CC_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	  if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//valid position
	    if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid position
	      if(map->hpge_lt[curr->chan-map->tig_min].col>=0)//valid color
		if(map->hpge_lt[curr->chan-map->tig_min].col<NCOL)//valid color      
	      return 1;
  
  return 0;	      
}
/*================================================================*/
int Sup_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->supp_lt[curr->chan-map->tig_min].seg>0)//channel is a BGO suppressor
	  if(map->supp_lt[curr->chan-map->tig_min].seg<NSUP)//channel is a BGO suppressor
	    if(map->supp_lt[curr->chan-map->tig_min].col>=0)//valid color
	      if(map->supp_lt[curr->chan-map->tig_min].col<NCOL)//valid color  
		if(map->supp_lt[curr->chan-map->tig_min].pos>0)//valid TIGRESS position
		  if(map->supp_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid TIGRESS position
		    return 1;
  
  return 0;	      
}
/*================================================================*/
int TIP_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->csiarray_min)
    if(curr->chan<=map->csiarray_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->csi_lt[curr->chan-map->csiarray_min]>0)//channel is a valid TIP position
	  if(map->csi_lt[curr->chan-map->csiarray_min]<NCSI)//channel is a valid TIP position 
		return 1;
  
  return 0;	      
}
