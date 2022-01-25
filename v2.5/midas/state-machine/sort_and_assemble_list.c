#include "sort_and_assemble_list.h"
/*================================================================*/
void sort_and_assemble_subruns(char* subrun_list_name)
{
  FILE* subrun_list;
  FILE* input;
  char name[132];
  int state=END_OF_RECORD;
  int stop=0; 
  data_pointers* dp=NULL;
  node*          list;

 /* open the list of subrun midas files */
  if((subrun_list=fopen(subrun_list_name,"r"))==NULL)
    {
      printf("ERROR!!! I can't open the surun midas file list!\n");
      exit(-2);
    }

  /* read name of first input file */
  if(fscanf(subrun_list,"%s",name)==EOF)
    {
      printf("ERROR!!! the subrun file name not read properly!\n");
      exit(-2);
    }

 /* open the first input file*/
  if((input=fopen(name,"r"))==NULL)
    {
      printf("\nI can't open input file %s\n",name);
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
      if( get_fragments_for_assembly(dp,list) < 0 )
	{ state = NEXT_EVENT;}
      else { state = GET_FRAGMENTS;  }
      break;
    case END_OF_FILE:
      fclose(input);
      printf("\n Number of analyzed midas banks is %8ld\n",dp->proc);
      printf("\n");
      /* read the name of the next input file */
      if(fscanf(subrun_list,"%s",name)==EOF){ state = END_OF_SORT; }
      else
	{
	  /* open the next file */
	  if((input=fopen(name,"r"))==NULL)
	    {
	      printf("\nI can't open input file %s\n",name);
	      exit(-2);
	    }
	  /* sort next file */
	  state = END_OF_RECORD;
	}
      break;
    case END_OF_SORT:
      /* close the midas list */
      fclose(subrun_list);
      /* analyze the last data assembly buffer */
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
	printf("Tsns  %16ld  first tsns on list %16ld last tsns on the list %16ld\n",nd->tsns,list[0].tsns,list[dp->last-1].tsns);
	printf("Correct DEPTH and SHIFT, recompile, try again\n");
	printf("Exiting\n");
	exit(0);
      }
 

  memcpy(&list[dp->last],nd,dp->son);
  dp->last++;
  sort_list(dp,list);


  return 0;
}

/*================================================================*/
int analyze_fragment_for_assembly(Grif_event* ptr, short* waveform,data_pointers* dp, node* list)
{
  long tsns;
  node nd;
  
  tsns=(ptr->timestamp&0xfffffffffffc0000)<<4;
  tsns+=ptr->cfd;
  tsns*=10;
  nd.tsns=tsns/=16;

  nd.ts=ptr->timestamp;
  nd.cfd=ptr->cfd;
  nd.chan=ptr->chan;
  //ignore large tsns at the start of the list
  if(dp->last==0)
    {
      if(tsns>START_TSNS)
	return 0;
    }
  
   add_node(&nd,dp,list);
 
  
 return 0;
}

/*================================================================*/
void sort_and_assemble(char* inp_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0; 
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
      if( get_fragments_for_assembly(dp,list) < 0 )
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
int sort_list(data_pointers* dp, node* list)
{
  int i;
  node store;
  //position the last element in the right spot

  i=dp->last-1;//pointer to the last added element
  if(i==0)
    return 1;
  
  while(1)
    {
      if(list[i].tsns>list[i-1].tsns)
	return 1;
      else
	{
	  memcpy(&store,&list[i-1],sizeof(node));
	  memcpy(&list[i-1],&list[i],sizeof(node));
	  memcpy(&list[i],&store,sizeof(node));
	  i--;
	}
      if(i==0)
	return 1;
    }
  
  return 0;
}
/*================================================================*/
int get_fragments_for_assembly(data_pointers* dp, node* list)
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
	  
	  unpack_grif_bank_for_assembly( bank_data, items, dp, list);
	  
	  if((dp->proc%10000)==0){printf("Number of analyzed GRF3/GRF4 banks is %8ld\r",dp->proc);}    
	  dp->proc++;
	}
    }
   return(-1); /* go to next event */
}

/*================================================================*/
int unpack_grif_bank_for_assembly(int *data, int length, data_pointers* dp, node* list)
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
	   analyze_fragment_for_assembly(&grif_event,waveform,dp,list);
	   
	 evntbuf=ptr;

       }
   

   return(0); 
}

/*================================================================*/
int print_list(int limit, int offset, node* list)
{
  int i;

  for(i=0;i<limit;i++)
    printf("Frag: %9d Ts[ns] %16ld Ch %4d Ts %16ld CFD %8d\n",i+offset,list[i].tsns,list[i].chan,list[i].ts,list[i].cfd);
  
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
