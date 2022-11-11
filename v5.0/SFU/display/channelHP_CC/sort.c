#include "sort.h"

/*================================================================*/
int analyze_data(raw_event *data)
{
  int pos,col,ID;
  
  if(data->tg.h.Gefold>0)
    for(pos=1;pos<NPOSTIGR;pos++)
      if((data->tg.h.GeHP&(1<<(pos-1)))!=0)
	if(data->tg.det[pos].h.Gefold>0)
	  for(col=0;col<NCOL;col++)
	    if((data->tg.det[pos].h.GeHP&(1<<col))!=0)
	      if(data->tg.det[pos].ge[col].h.Efold>0)
		if((data->tg.det[pos].ge[col].h.EHP&1)!=0)
		  {
		    ID = 4*(pos-1) + col;
		    hist[ID]++;
		    h->Fill(ID);		    
		  }
  return SEPARATOR_DISCARD;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;
  TCanvas *c;
  TApplication *theApp;
  input_names_type* name;
  int ac;
  char *av[1];

  ac=0;
  av[0]=(char*) malloc(sizeof(char));
  if(argc!=2)
    {
      printf("sfu_display_channelHP_CC sfu_data_file\n");
      exit(-1);
    }
  printf("Program sorts DAQ channel CC hit pattern.\n");

  h=new TH1D("Fold","Fold",S2K,0,S2K);
  h->Reset();
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  strcpy(name->fname.inp_data,argv[1]);
  memset(hist,0,sizeof(hist));
    
  sort(name);
  
  if((output=fopen("sfu_display_channelHP_CC.spn","w"))==NULL)
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
