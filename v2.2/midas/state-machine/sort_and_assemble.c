#include "sort_and_assemble.h"
/*================================================================*/
int add_fragment(long tag, data_pointers* dp, node* list)
{
  int i;
  for(i=dp->last-1;i>=0;i--)
    if(list[i].tag==tag)
      {
	list[i].fold++;
	return 1;
      }
  return 0;
}
/*================================================================*/
int print_list(data_pointers* dp, node* list, gmap* map)
{
  int i;

  for(i=0;i<dp->last;i++)
    printf("Trig %8d Tag %16ld Tag 0x %16lx Ts[ns] %16ld Fold %16d\n",i,list[i].tag,list[i].tag,list[i].tag*map->div,list[i].fold);
  
  return 0;
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
      if(list[i].tag>list[i-1].tag)
	return 1;
      else
	{
	  memcpy(&store,&list[i-1],sizeof(node));
	  memcpy(&list[i-1],&list[i],sizeof(node));
	  memcpy(&list[i],&store,sizeof(node));
	  i--;
	}
      if(i<0)
	return 0;
    }
  
  return 0;
}
/*================================================================*/
int add_node(long tag, data_pointers* dp, node* list)
{
  if(dp->last<DEPTH)
    {
      list[dp->last].tag=tag;
      dp->last++;
      sort_list(dp,list);
      return 1;
    }
 
  return 0;
}
/*================================================================*/
int tag_on_list(long tag,data_pointers* dp, node* list)
{
  int i;
  
  if(dp->last==0)
    return 0;

  for(i=dp->last-1;i>=0;i--)
    if(list[i].tag==tag)
      return 1;
  
  return 0;
}
/*================================================================*/
int analyze_fragment_for_assembly(Grif_event* ptr, short* waveform,data_pointers* dp, node* list, gmap* map)
{
  long tsns,tag;

  
  tsns=(ptr->timestamp&0xfffffffffffc0000)<<4;
  tsns+=ptr->cfd;
  tsns*=10;
  tsns/=16;
  tag=tsns/map->div;

  //ignore large tags at the start of the list
  if(dp->last==0)
    if(tag>START_TAG)
      return 0;
  
  if(tag_on_list(tag,dp,list)==0)
    {
      //      printf("Tag not on the list\n");
      if(add_node(tag,dp,list)!=1)
	{
	  printf("List is full, exiting\n");
	  print_list(dp,list,map);
	  exit(0);
	}
    }

  add_fragment(tag,dp,list);
 
  
  /* printf("Time stamp in nanoseconds is %16ld\n",tsns); */
  /* printf("                      Tag is %16ld\n",tag); */
  /* print_list(dp,list,map); */
  /* printf("              List length is %16ld\n",dp->last); */
  /* printf("Press enter to continue\n"); */
  /* getc(stdin); */
 return 0;
}
/*================================================================*/
int get_fragments_for_assembly(data_pointers* dp, node* list, gmap* map)
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
void sort_and_assemble(char* inp_name,char* map_name)
{
  FILE* input;
  int state=END_OF_RECORD;
  int stop=0;
  static gmap    map; 
  int i;
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
  
  list=(node*) malloc(DEPTH*dp->son);

  for(i=0;i<DEPTH;i++)
    {
      list[i].tag=-1;
      list[i].fold=0;   
    }
  
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
      printf("\n Number of analyzed fragments is %8ld\n",dp->proc);
      printf("\n");
      print_list(dp,list,&map);
      stop=1;
      break;
    default:
      printf("Unknown case\n");
      exit(0);
      break;
    }
  }
}
  
