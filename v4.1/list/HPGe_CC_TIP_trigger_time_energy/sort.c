#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig;
  unsigned long long dt;
  unsigned long pos;
  
  if(argc!=5)
    {
      printf("list_HPGe_CC_TIP_time_difference list_input_data map window_[ns] divider\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and TIP fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  son=sizeof(node);
  window=atoi(argv[3]);
  read_map(argv[2],&map);
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH2D("TSdiff","TSdiff",S16K,0,S16K,S2K,-S4K,S4K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  divider=atoi(argv[4]);
  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
      	break;
      if((current.ch.timestamp|current.ch.timestamp_up)!=0)//ignore bad events at the start

      if(CC_channel(&current,&map)==1)
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
	      if(TIP_channel(&next,&map)==1)
		if(next.wfit.type==1)
		{
		  dt=next.trig_tsns-current.trig_tsns;
		  if(dt>window)
		    break;
		  h->Fill(current.ch.charge/divider,(int)dt);
		}
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      if(TIP_channel(&current,&map)==1)
	if(current.wfit.type==1)
	{
	  if((trig=current.csi_trig)<1)
	    {
	      printf("Incorrect TIP trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
	      exit(0);
	    }
	  pos=ftell(inp);//save current position
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      if(CC_channel(&next,&map)==1)
		{
		  dt=next.trig_tsns-current.trig_tsns;
		  if(dt>window)
		    break;
		  h->Fill(next.ch.charge/divider,-(int)dt);
		}	      
	      
	    }
	  fseek(inp,pos,SEEK_SET);	  
	}
    }

  fclose(inp);
  //theApp->Run(kTRUE);

  TFile f("tsdiff_vs_charge_cc-tip.root","recreate");
  
  h->GetYaxis()->SetTitle("TSdiff");
  h->GetXaxis()->SetTitle("CC Charge");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
  h->SetOption("COLZ");
  h->Write();
  
}
