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
  
  if(argc!=5)
    {
      printf("list_add_trigger_to_Sup fragment_list map gate_low[ns] gate_high[ns]\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to HPGe suppressors based on HPGe central contact trigger number on a list of fragments created from GRIF3/GRIF4 midas file.\n");

  son=sizeof(node);
  read_map(argv[2],&map);
    
  if((inp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }
  
  gate_low=atoi(argv[3]);
  gate_high=atoi(argv[4]);

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      if(CC_channel(&current,&map)==1)
	{
	  if(current.tig_trig<1)
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
	      if(dt>S16K)
		break;

	      if(Sup_channel(&next,&map)==1)
		//if(same_HPGe(&current,&next,&map)==1)
		  if(dt>gate_low && dt<gate_high)
		    {
		      next.tig_trig=current.tig_trig;
		      next.trig_tsns=current.trig_tsns;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		    }
		  /* { */
		  /*   if(dt<gate_low || dt>gate_high) */
		  /*     continue; */
		  /*   next.tig_trig=current.tig_trig; */
		  /*   fseek(inp,-son,SEEK_CUR); */
		  /*   fwrite(&next,son,1,inp); */
		  /*   //break; */
		  /* } */
	    }
	  
	  fseek(inp,pos,SEEK_SET);
	}

      
      if(Sup_channel(&current,&map)==1)
	{
	  pos=ftell(inp);//save current position
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      dt=next.tsns-current.tsns;
	      if(dt>S16K)
		break;
	      if(CC_channel(&next,&map)==1)
		//if(same_HPGe(&next,&current,&map)==1){printf("%s\n","here");
		  if((-dt)>gate_low && (-dt)<gate_high)
		    {
		      current.tig_trig=next.tig_trig;
		      current.trig_tsns=next.trig_tsns;
		      fseek(inp,pos,SEEK_SET);
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&current,son,1,inp);
		      break;
		    }
		  /* { */
		  /*   if(-dt<gate_low || -dt>gate_high) */
		  /*     continue; */
		  /*   current.tig_trig=next.tig_trig; */
		  /*   fseek(inp,pos,SEEK_SET); */
		  /*   fseek(inp,-son,SEEK_CUR); */
		  /*   fwrite(&current,son,1,inp);	 */
		  /*   //break; */
		  /* }	      	       */
	    }
	  fseek(inp,pos,SEEK_SET);
	}
    }

  fclose(inp);  
}
