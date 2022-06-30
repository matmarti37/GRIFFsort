#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  static gmap map;
  size_t son;
  node  current,next;
  unsigned long long dt;
  unsigned long pos;
  int low, high;
  
  if(argc!=5)
    {
      printf("list_add_trigger_to_TIP fragment_list map low_limit_ns high_limit_ns\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to TIP detectors based on HPGe central contact trigger number on a list of fragments created from GRIF3/GRIF4 midas file.\n");

  son=sizeof(node);
  read_map(argv[2],&map);
    
  if((inp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
  
  low=atoi(argv[3]);
  high=atoi(argv[4]);
  
  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(CC_channel(&current,&map)==1)
	{
	  if(current.trig<1)
	    {
	      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",current.trig,current.tsns,current.chan);
	      exit(0);
	    }
	  pos=ftell(inp);//save current position
	  
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      dt=next.tsns-current.tsns;

	      if((int)dt>high) break;
	      if((int)dt<low) break;
	      
	      if(TIP_channel(&next,&map)==1)
		  {
		    next.trig=current.trig;
		    fseek(inp,-son,SEEK_CUR);
		    fwrite(&next,son,1,inp);
		    break;
		  }
	    }
	  
	  fseek(inp,pos,SEEK_SET);
	}

      if(TIP_channel(&current,&map)==1)
	{
	  pos=ftell(inp);//save current position
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      dt=next.tsns-current.tsns;	      

	      if(-(int)dt>high) break;
	      if(-(int)dt<low) break;
	      
	      if(CC_channel(&next,&map)==1)
		  {
		    current.trig=next.trig;
		    fseek(inp,pos,SEEK_SET);
		    fseek(inp,-son,SEEK_CUR);
		    fwrite(&current,son,1,inp);	
		    break;
		  }	      	      
	    }
	  fseek(inp,pos,SEEK_SET); //TEST
	}
    }

  fclose(inp);  
}
