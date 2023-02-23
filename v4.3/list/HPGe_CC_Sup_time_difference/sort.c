#include "sort.h"


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig;
  unsigned long long  dt;
  unsigned long pos;
  
  if(argc!=7)
    {
      printf("list_HPGe_CC_Sup_time_difference list_input_data map window_[ns] Egate_low Egate_high Edivisor\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and BGO suppressor fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  son=sizeof(node);
  window=atoi(argv[3]);
  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));

  int Egate_low=atoi(argv[4]);
  int Egate_high=atoi(argv[5]);
  int E_divisor=atoi(argv[6]);
  
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  //printf("%d %d %d\n",Egate_low,Egate_high,E_divisor);
  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

      /* if(CC_channel(&current,&map)==1) */
      /* 	{ */
      /* 	  printf("charge: %d\n",current.ch.charge); */
      /* 	  if(current.ch.charge/E_divisor>=Egate_low) */
      /* 	    if(current.ch.charge/E_divisor<=Egate_high) */
      /* 	      printf("made through\n"); */
      /* 	  getc(stdin); */
      /* 	} */
      if(CC_channel(&current,&map)==1)
	if(current.ch.charge/E_divisor>=Egate_low)
	  if(current.ch.charge/E_divisor<=Egate_high)
	{
	  if((trig=current.tig_trig)<1)
	    {
	      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
	      exit(0);
	    }
	  pos=ftell(inp);//save current position

	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      dt=next.tsns-current.tsns;
	      if(dt>window)
		break;
	      if(Sup_channel(&next,&map)==1)
		{
		  h->Fill((int)dt);
		  if(dt<S16K)
		    hist[S16K+dt]++;
		}
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
	      if(dt>window)
		break;
	      if(CC_channel(&next,&map)==1)
		if(next.ch.charge/E_divisor>=Egate_low)
		  if(next.ch.charge/E_divisor<=Egate_high)
		{
		  if((trig=next.tig_trig)<1)
		    {
		      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
		      exit(0);
		    }
		  h->Fill(-(int)dt);
		  if(dt<S16K)
		    hist[S16K-dt]++;
		}	      
	      
	    }
	  fseek(inp,pos,SEEK_SET);	  
	}
      
     
    }

  fclose(inp);

  if((output=fopen("HPGe_CC_Sup_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
