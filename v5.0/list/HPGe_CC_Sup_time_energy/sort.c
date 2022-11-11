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

  int counter=0;
  int divider=32;
  
  if(argc!=4&&argc!=5)
    {
      printf("list_HPGe_CC_Sup_time_energy list_input_data map window_[ns] [energy_divider (default 32)]\n");
      exit(-1);
    }

  if(argc==5)
    divider=atoi(argv[4]);
 
  printf("Program sorts time difference histogram between HPGe CC and Sup fragments within a time window on the list\n");


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
  h=new TH2D("CC_Charge","CC_Charge",S4K,0,S16K,S1K,-S2K,S2K);
  h2=new TH2D("Sup_Charge","Sup_Charge",S4K,0,S16K,S1K,-S2K,S2K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
	break;

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
	      dt=next.tsns-current.tsns;
	      if(dt>window)
		break;
	      if(Sup_channel(&next,&map)==1)
		{
		  h->Fill(current.ch.charge/divider,(int)dt);
		  h2->Fill(next.ch.charge/divider,(int)dt);
		}
	      counter++;
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
		{
		  if((trig=next.tig_trig)<1)
		    {
		      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,next.tsns,next.chan);
		      exit(0);
		    }
		  h->Fill(next.ch.charge/divider,-(int)dt);
		  h2->Fill(current.ch.charge/divider,-(int)dt);
		}
	      counter++;
	    }
	  fseek(inp,pos,SEEK_SET);	  
	}
    }

  fclose(inp);

  TFile f("tsdiff_vs_charge_sup.root","recreate");
  
  h->GetYaxis()->SetTitle("TSdiff");
  h->GetXaxis()->SetTitle("CC Charge");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
  h->SetOption("COLZ");
  h->Write();

  h2->GetYaxis()->SetTitle("TSdiff");
  h2->GetXaxis()->SetTitle("Sup Charge");
  h2->GetXaxis()->CenterTitle(true);
  h2->GetYaxis()->CenterTitle(true);
  h2->SetOption("COLZ");
  h2->Write();
}
