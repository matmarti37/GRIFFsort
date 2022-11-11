#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  int ID;

  if(ptr->chan>=map->tig_min)
    if(ptr->chan<=map->tig_max)
      {
	//if((ptr->ch.timestamp|ptr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[ptr->chan-map->tig_min].seg==0)//channel is the central contact
	  if(map->hpge_lt[ptr->chan-map->tig_min].pos>0)//valid position
	    if(map->hpge_lt[ptr->chan-map->tig_min].pos<NPOSTIGR)//valid position
	      if(map->hpge_lt[ptr->chan-map->tig_min].col>=0)//valid color
		if(map->hpge_lt[ptr->chan-map->tig_min].col<NCOL)//valid color
		  {
		    ID = 4*(map->hpge_lt[ptr->chan-map->tig_min].pos-1) + map->hpge_lt[ptr->chan-map->tig_min].col;
		    hist[ID]++;
		    h->Fill(ID);
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
  if(argc!=3)
    {
      printf("midas_project_channelHP_CC midas_data_file map\n");
      exit(-1);
    }
  printf("Program sorts DAQ channel hit pattern.\n");

  map=(gmap*)malloc(sizeof(gmap));
  h=new TH1D("Fold","Fold",S2K,0,S2K);
  h->Reset();
  memset(&hist,0,sizeof(hist));
  
  read_map(argv[2], map);
  
  sort_but_not_assemble(argv[1]);
  
  if((output=fopen("midas_project_channelHP_CC.spn","w"))==NULL)
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
  h->GetXaxis()->SetTitle("Detector");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  theApp->Run(kTRUE);
}
