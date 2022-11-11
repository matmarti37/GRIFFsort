#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  //Upper bits of the time stamp.
  int tsup;
  tsup=(int)((ptr->timestamp>>32)&0xffff);

  //Collect channel hits for the user specified range of tsup.
  if((tsup>=min_TSUP) && (tsup<=max_TSUP))
    {
      if((ptr->chan>=0) && (ptr->chan<=S2K))
	{
	  hist[ptr->chan]++;
	  h->Fill(ptr->chan);
	}
    }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;
  TCanvas *c;
  TApplication *theApp;
  int ac;
  char *av[1];

  ac=0;
  av[0]=(char*) malloc(sizeof(char));
  if(argc!=4)
    {
      printf("midas_project_channelHP_tsupRange midas_data_file min_TSUP max_TSUP\n");
      exit(-1);
    }
  min_TSUP = atoi(argv[2]);
  max_TSUP = atoi(argv[3]);

  printf("Program sorts DAQ channel hit pattern for a specific range of timestamp ups.\n");
  printf("Range was input as: %d <= tsup <= %d\n", min_TSUP, max_TSUP);
  
  h=new TH1D("Fold","Fold",S2K,0,S2K);
  h->Reset();
  memset(&hist,0,sizeof(hist));
  
  sort_but_not_assemble(argv[1]);
  
  if((output=fopen("channelHP_tsupRange.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);
  
  theApp=new TApplication("App", &ac, av);
  c = new TCanvas("Fold", "Fold",10,10, 700, 500);
  c->cd();
  gPad->SetLogy();
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  theApp->Run(kTRUE);
}
