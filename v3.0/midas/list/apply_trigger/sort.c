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
  //window=atoi(argv[3]);
  read_map(argv[2],&map);
  /* memset(&hist,0,sizeof(hist)); */
  /* theApp=new TApplication("App", &argc, argv); */
  /* if(h!=NULL) delete h; */
  /* h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K); */
  /* if(c!=NULL) delete c; */
  /* c = new TCanvas("TS", "TS",10,10, 700, 500); */

  while(1)
    {
      if(fread(&curr,son,1,inp)!=1)
	break;
      if(curr.trig>0)
        continue;
      if(curr.csi_trig<0 && curr.tig_trig<0)
	continue;
      trigger++; //Got through conditions, so starting new event

      if(CC_channel(&curr,&map)==1)
	{
	  if(curr.tig_trig<1)
	    {
	      printf("Incorrect TIG trigger %d at tsns %16lld channel %d. Exiting\n",curr.tig_trig,curr.tsns,curr.chan);
	      exit(0);
	    }
	  pos=ftell(inp);
	  curr.trig=trigger;
	  fseek(inp,-son,SEEK_CUR);
	  fwrite(&curr,son,1,inp);

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      temp=ftell(inp);
	      if(next.trig_tsns<1)
		continue;
	      dt=next.trig_tsns-curr.trig_tsns;
	      if((int)dt>S16K)
		break;
	      if(CC_channel(&next,&map)==1)
		if((int)dt<50)
		  {
		    next.trig=trigger;
		    fseek(inp,-son,SEEK_CUR);
		    fwrite(&next,son,1,inp);
		  }
	      fseek(inp,temp,SEEK_SET);
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      if(TIP_channel(&curr,&map)==1)
	{
	  if(curr.csi_trig<1)
	    {
	      printf("Incorrect TIP trigger %d at tsns %16lld channel %d. Exiting\n",curr.csi_trig,curr.tsns,curr.chan);
	      exit(0);
	    }
	  pos=ftell(inp);

	  //Sets trigger to TIP event
	  curr.trig=trigger;
	  fseek(inp,-son,SEEK_CUR);
	  fwrite(&curr,son,1,inp);

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      temp=ftell(inp);
	      if(next.trig_tsns<1)
		continue;
	      dt=next.trig_tsns-curr.trig_tsns;
	      if((int)dt>S16K)
		break;
	      
	      if(TIP_channel(&next,&map)==1)
		{
		  if((int)dt<50)
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		    }
		}
	      else
		{
		  if((int)dt>t_low && (int)dt<t_high)
		    {
		      next.trig=trigger;
		      fseek(inp,-son,SEEK_CUR);
		      fwrite(&next,son,1,inp);
		    }
		}
	      fseek(inp,temp,SEEK_SET);
	    }
	  fseek(inp,pos,SEEK_SET);
	}


      /* if(CC_channel(&current,&map)==1) */
      /* 	{ */
      /* 	  pos=ftell(inp);//save current position */
      /* 	  while(1) */
      /* 	    { */
      /* 	      if(fread(&next,son,1,inp)!=1) */
      /* 		break; */
      /* 	      dt=next.tsns-current.tsns;	       */
      /* 	      if(dt>window) */
      /* 		break; */
	      
      /* 	      if(TIP_channel(&next,&map)==1) */
      /* 		{		   */
      /* 		  h->Fill(-(int)dt); */
      /* 		  if(dt<S16K) */
      /* 		    hist[S16K-dt]++; */
      /* 		}	       */
	      
      /* 	    } */
      /* 	  fseek(inp,pos,SEEK_SET);	   */
      /* 	} */
    }

  fclose(inp);

  
}
