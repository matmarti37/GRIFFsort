#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  //FILE* output;
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
      printf("list_HPGe_CC_Seg_time_energy list_input_data map window_[ns] [energy_divider (default 32)]\n");
      exit(-1);
    }

  if(argc==5)
    divider=atoi(argv[4]);
 
  printf("Program sorts time difference histogram between HPGe CC and Seg fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  //int position,colour;
  son=sizeof(node);
  window=atoi(argv[3]);
  read_map(argv[2],&map);
  /* memset(&hist,0,sizeof(hist)); */
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH2D("CC_Charge","CC_Charge",S4K,0,S16K,S1K,-S2K,S2K);
  h2=new TH2D("Seg_Charge","Seg_Charge",S4K,0,S16K,S1K,-S2K,S2K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  /* current.chan=9; */
  /* printf("%d\n",CC_channel(&current,&map)); */
  /* getc(stdin); */

  while(1)
    {
      if(counter>100000000)
      	break;
      if(fread(&current,son,1,inp)!=1)
	break;

      if(CC_channel(&current,&map)==1)
	{
	  if((trig=current.tig_trig)<1)
	    {
	      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
	      /* print_map(&map); */
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
	      if(Seg_channel(&next,&map)==1)
		if(same_HPGe(&current,&next,&map)==1)
		  {
		    //position=map.hpge_lt[next.chan-map.tig_min].pos;
		    //colour=map.hpge_lt[next.chan-map.tig_min].seg;
		    h->Fill(current.ch.charge/divider,(int)dt);
		    h2->Fill(next.ch.charge/divider,(int)dt);
		    /* if(dt<S16K) */
		    /*   { */
		    /* 	hist[0][current.ch.charge][S16K+dt]++; */
		    /* 	hist[position][current.ch.charge][S16K+dt]++; */
		    /* 	//hist[8*(position-1)+colour][S16K+dt]++; */
		    /*   } */
		  }
	      counter++;
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      if(Seg_channel(&current,&map)==1)
	{
	  pos=ftell(inp);//save current position
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;
	      /* if(next.tsns>2682750000) */
	      /* 	printf("CHAN %d TSNS %16lld CCCHAN %d\n",next.chan,next.tsns,CC_channel(&next,&map)); */
	      dt=next.tsns-current.tsns;	      
	      if(dt>window)
		break;
	      if(CC_channel(&next,&map)==1)
		{
		  if((trig=next.tig_trig)<1)
		    {
		      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,next.tsns,next.chan);
		      /* print_map(&map); */
		      exit(0);
		    }
		  if(same_HPGe(&current,&next,&map)==1)
		    {
		      //position=map.hpge_lt[current.chan-map.tig_min].pos;
		      //colour=map.hpge_lt[current.chan-map.tig_min].seg;
		      h->Fill(next.ch.charge/divider,-(int)dt);
		      h2->Fill(current.ch.charge/divider,-(int)dt);
		      /* if(dt<S16K) */
		      /* 	{ */
		      /* 	  hist[0][next.ch.charge][S16K-dt]++; */
		      /* 	  hist[position][next.ch.charge][S16K-dt]++; */
		      /* 	  //hist[8*(position-1)+colour][S16K-dt]++; */
		      /* 	} */
		    }
		}
	      counter++;
	    }
	  fseek(inp,pos,SEEK_SET);	  
	}
    }

  fclose(inp);

  //"tsdiff_vs_charge.root";
  TFile f("tsdiff_vs_charge.root","recreate");
  
  h->GetYaxis()->SetTitle("TSdiff");
  h->GetXaxis()->SetTitle("CC Charge");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
  h->SetOption("COLZ");
  h->Write();

  h2->GetYaxis()->SetTitle("TSdiff");
  h2->GetXaxis()->SetTitle("CC Charge");
  h2->GetXaxis()->CenterTitle(true);
  h2->GetYaxis()->CenterTitle(true);
  h2->SetOption("COLZ");
  h2->Write();

  /* if((output=fopen("HPGe_CC_Seg_dt.mca","w"))==NULL) */
  /*   { */
  /*     printf("ERROR!!! I cannot open the mca file.\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
  /* fwrite(hist,sizeof(hist),1,output); */
  /* fclose(output); */

  /* h->Draw("HIST"); */
  /* theApp->Run(kTRUE); */

  /* print_map(&map); */

  printf("Histogram contains sum in channel 0 and each of the 16 detectors in channels 1-16\n");
  
}
