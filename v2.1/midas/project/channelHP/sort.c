#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  if((ptr->chan>=0) && (ptr->chan<=S2K))
    {
      hist[ptr->chan]++;
      h->Fill(ptr->chan);
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
  if(argc!=2)
    {
      printf("trig_channelHP midas_data_file\n");
      exit(-1);
    }
  printf("Program sorts DAQ channel hit pattern.\n");

  h=new TH1D("Hit Pattern","Hit Pattern",S2K,0,S2K);
  h->Reset();
  memset(&hist,0,sizeof(hist));
  
  sort_but_not_assemble(argv[1]);
  
  if((output=fopen("channelHP.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);
  
  theApp=new TApplication("App", &ac, av);
  c = new TCanvas("Hit Pattern", "Hit Pattern",10,10, 700, 500);
  c->cd();
  gPad->SetLogy();
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  theApp->Run(kTRUE);
}
