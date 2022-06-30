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
  unsigned long long dt;
  unsigned long pos;
  
  if(argc!=4)
    {
      printf("list_HPGe_CC_TIP_time_difference list_input_data map window_[ns]\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and TIP fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  // Makes histograms
  for(int i=0;i<5;i++)
    {
      PID[i]=new TH2D("PID","PID",S1K,0,S4K,150,100,250); PID[i]->Reset();
      TIME[i]=new TH1D("TS","TS",S32K,-S16K,S16K); TIME[i]->Reset();
      chHP[i]=new TH1D("HP","HP",S2K,0,S2K); chHP[i]->Reset();
      tgHP[i]=new TH1D("tgHP","tgHP",S1K,0,S1K); tgHP[i]->Reset();
    }

  son=sizeof(node);
  window=atoi(argv[3]);
  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  double amp,ratio;

  while(1)
    {
      if(fread(&current,son,1,inp)!=1)
      	break;

      if(CC_channel(&current,&map)==1)
      	{
      	  if((trig=current.trig)<1)
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
      	      if(TIP_channel(&next,&map)==1)
      		if(next.wfit.type==1)
      		{
      		  h->Fill((int)dt);
      		  if(dt<S16K)
      		    hist[S16K+dt]++;
      		  amp=next.wfit.am[2]+next.wfit.am[3];
      		  ratio=100*(next.wfit.am[3]/next.wfit.am[2])+100;
      		  PID[0]->Fill(amp,ratio);
      		  PID[1]->Fill(amp,ratio);
      		  TIME[0]->Fill((int)dt);
      		  TIME[1]->Fill((int)dt);
      		  chHP[0]->Fill(next.chan);
      		  chHP[1]->Fill(next.chan);
      		  tgHP[0]->Fill(current.chan);
      		  tgHP[1]->Fill(current.chan);
      		}
      	    }
      	  fseek(inp,pos,SEEK_SET);
      	}

      if(TIP_channel(&current,&map)==1)
      	if(current.wfit.type==1)
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
      		  h->Fill(-(int)dt);
      		  if(dt<S16K)
      		    hist[S16K-dt]++;
		  amp=current.wfit.am[2]+current.wfit.am[3];
		  ratio=100*(current.wfit.am[3]/current.wfit.am[2])+100;
		  PID[0]->Fill(amp,ratio);
		  TIME[0]->Fill(-(int)dt);
		  chHP[0]->Fill(current.chan);
		  tgHP[0]->Fill(next.chan);
		  if(dt>1500)
		    {
		      PID[1]->Fill(amp,ratio);
		      TIME[1]->Fill(-(int)dt);
		      chHP[1]->Fill(current.chan);
		      tgHP[1]->Fill(next.chan);
		    }
		  if(dt<=1500 && dt>1000)
		    {
		      PID[2]->Fill(amp,ratio);
		      PID[4]->Fill(amp,ratio);
		      TIME[2]->Fill(-(int)dt);
		      TIME[4]->Fill(-(int)dt);
		      chHP[2]->Fill(current.chan);
		      chHP[4]->Fill(current.chan);
		      tgHP[2]->Fill(next.chan);
		      tgHP[4]->Fill(next.chan);
		    }
		  if(dt<=1000 && dt>500)
		    {
		      PID[2]->Fill(amp,ratio);
		      PID[3]->Fill(amp,ratio);
		      TIME[2]->Fill(-(int)dt);
		      TIME[3]->Fill(-(int)dt);
		      chHP[2]->Fill(current.chan);
		      chHP[3]->Fill(current.chan);
		      tgHP[2]->Fill(next.chan);
		      tgHP[3]->Fill(next.chan);
		    }
		  if(dt<=500)
		    {
		      PID[1]->Fill(amp,ratio);
		      TIME[1]->Fill(-(int)dt);
		      chHP[1]->Fill(current.chan);
		      tgHP[1]->Fill(next.chan);
		    }
      		}
	      
      	    }
      	  fseek(inp,pos,SEEK_SET);
	}
    }

  fclose(inp);

  if((output=fopen("HPGe_CC_TIP_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  //h->Draw("HIST");
  //theApp->Run(kTRUE);

  TFile f("SeparatePID.root","recreate");
  for(int i=0;i<5;i++)
    {
      PID[i]->GetXaxis()->SetTitle("Amplitude [arb.]");
      PID[i]->GetXaxis()->CenterTitle(true);
      PID[i]->GetYaxis()->SetTitle("$A_S/A_F \\times 100 + 100$");
      PID[i]->GetYaxis()->CenterTitle(true);
      PID[i]->GetYaxis()->SetTitleOffset(0);
      PID[i]->SetOption("COLZ");
      PID[i]->Write();

      TIME[i]->GetXaxis()->SetTitle("Time Difference [ns]");
      TIME[i]->GetXaxis()->CenterTitle(true);
      TIME[i]->GetYaxis()->SetTitle("Counts");
      TIME[i]->GetYaxis()->CenterTitle(true);
      TIME[i]->GetYaxis()->SetTitleOffset(0);
      TIME[i]->Write();

      chHP[i]->GetXaxis()->SetTitle("Channel");
      chHP[i]->GetXaxis()->CenterTitle(true);
      chHP[i]->GetYaxis()->SetTitle("Counts");
      chHP[i]->GetYaxis()->CenterTitle(true);
      chHP[i]->GetYaxis()->SetTitleOffset(0);
      chHP[i]->Write();

      tgHP[i]->GetXaxis()->SetTitle("Channel");
      tgHP[i]->GetXaxis()->CenterTitle(true);
      tgHP[i]->GetYaxis()->SetTitle("Counts");
      tgHP[i]->GetYaxis()->CenterTitle(true);
      tgHP[i]->GetYaxis()->SetTitleOffset(0);
      tgHP[i]->Write();
    }
}
