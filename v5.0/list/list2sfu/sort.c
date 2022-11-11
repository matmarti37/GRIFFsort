#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* out;
  int   trigger,pos,i;
  gmap map;
  raw_event *evt;
  node *nd;
  size_t son,soe;
  int *eb;
  
  if(argc!=4)
    {
      printf("list2sfu input_list_name output_sfu_name map\n");
      exit(-1);
    }

  printf("Program generates a data file in SFU format from an ordered list with trigger numbers.\n");

  son=sizeof(node);
  soe=sizeof(raw_event);
 
  nd=(node*)malloc(son);
  memset(nd,0,son);

  evt=(raw_event*)malloc(DB*soe);
   memset(evt,0,DB*soe);

   eb=(int*)malloc(BUFFSIZE*sizeof(int));
   memset(eb,0,BUFFSIZE*sizeof(int));
  
 
  eb[0]=BUFFER_TAG;
  eb[1]++;
  eb[1]++;


  read_map(argv[3],&map);
 
  
   if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }
 
  trigger=1;
 
  while(fread(nd,son,1,inp)==1)
    if(nd->trig>0)
    {
      pos=nd->trig-trigger;

      if(pos<0)
	{
	  printf("Reconstruction error, fragment with trigger %d at %d\n",nd->trig,trigger);
	  printf("Exiting\n");
	  exit(0);
	}

      if(pos>=DB)
	  {
	    for(i=0;i<DS;i++)
	      {
		/* display_raw_event(&evt[i]); */
		/* getc(stdin); */
		encode(&evt[i],out,eb);
	      }
	    memmove(&evt[0],&evt[DS],(DB-DS)*soe);
	    memset(&evt[DS],0,DS*soe);
	    trigger+=DS;
	    pos=nd->trig-trigger;
	  }

      map_event(&evt[pos],nd,&map);
      
      if((trigger-1)%10000==0)
	printf("Processed %8d reconstructed events\r",trigger-1);
    }

  fclose(inp);

  for(i=0;i<DB;i++)
    if(evt[i].h.frag_fold>0)
    {
      trigger++;
      encode(&evt[i],out,eb);
    }
  fwrite(eb,sizeof(int),BUFFSIZE,out);

   fclose(out);
  printf("Processed %8d reconstructed events\n",trigger-1);
 
 
}

