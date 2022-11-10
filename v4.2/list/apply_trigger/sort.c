#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  static gmap map;
  size_t son;
  node  curr,next;
  int   trigger=0;
  unsigned long long dt;
  unsigned long pos;
  unsigned long temp;
  
  if(argc!=5)
    {
      printf("list_apply_trigger list_input_data map low[ns] high[ns]\n");
      //printf("list_TIP_CC_time_difference list_input_data map window_[ns]\n");
      exit(-1);
    }
  

  printf("Program applies triggers based on TIP-CC timing from the list\n");
  //printf("Program sorts time difference histogram between HPGe CC and TIP fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  son=sizeof(node);
  t_low=atoi(argv[3]);
  t_high=atoi(argv[4]);
  read_map(argv[2],&map);

  while(1)
    {
      if(fread(&curr,son,1,inp)!=1)
	break;
      if(curr.trig>0)
        continue;
      if(curr.csi_trig<0 && curr.tig_trig<0)
	continue;
      trigger++; //Got through conditions, so starting new event

      if(curr.csi_trig>0)
	{
	  if(curr.trig_tsns==0){printf("Fragment with TIP_TRIG %d has no TRIG_TSNS\n",curr.csi_trig); exit(0);}
	  if(curr.tig_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);}
	  
	  pos=ftell(inp);
	  curr.trig=trigger;
	  fseek(inp,-son,SEEK_CUR);
	  fwrite(&curr,son,1,inp);

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      if(next.trig>0)
		continue;
	      if(next.csi_trig<0 && curr.tig_trig<0)
		continue;
	      temp=ftell(inp);

	      dt=next.trig_tsns-curr.trig_tsns;
	      if((int)dt>S8K)
		break;

	      if(next.csi_trig>0)
		{
		  if(next.tig_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);} // Makes sure fragment doesn't have both
		  if(curr.csi_trig==next.csi_trig) // Adds csi frag if same event
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		      continue;
		    }
		}
	      if(next.tig_trig>0)
		{
		  if(next.csi_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);}
		  //dt=next.trig_tsns-curr.trig_tsns;
		  if(-(int)dt>t_low && -(int)dt<t_high)
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		    }
		}
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      if(curr.tig_trig>0)
	{
	  if(curr.trig_tsns==0){printf("Fragment with TIG_TRIG %d has no TRIG_TSNS\n",curr.tig_trig); exit(0);}
	  if(curr.csi_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);}
	  
	  pos=ftell(inp);
	  curr.trig=trigger;
	  fseek(inp,-son,SEEK_CUR);
	  fwrite(&curr,son,1,inp);

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      if(next.trig>0)
		continue;
	      if(next.csi_trig<0 && curr.tig_trig<0)
		continue;
	      temp=ftell(inp);

	      dt=next.trig_tsns-curr.trig_tsns;
	      if((int)dt>S8K)
		break;

	      if(next.tig_trig>0)
		{
		  if(next.csi_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);} // Makes sure fragment doesn't have both
		  if(curr.tig_trig==next.tig_trig) // Adds tig frag if same event
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		      continue;
		    }
		}
	      if(next.csi_trig>0)
		{
		  if(next.tig_trig>0){printf("Fragment with TIG_TRIG %d has both TIP and TIG triggers\n",curr.tig_trig); exit(0);}
		  //dt=next.trig_tsns-curr.trig_tsns;
		  if((int)dt>t_low && (int)dt<t_high)
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		    }
		}
	    }
	  fseek(inp,pos,SEEK_SET);
	}
    }
  fclose(inp);

  
}
