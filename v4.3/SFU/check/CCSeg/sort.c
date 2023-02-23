#include "sort.h"

int analyze_data(raw_event *data)
{
  int pos,col,segm;
  int fold=0;
  if(data->tg.h.Gefold==0)
    return SEPARATOR_DISCARD;
  /* h->Fill(data->h.setupHP); */
  if(data->tg.h.Gefold>0)
    for(pos=1;pos<NPOSTIGR;pos++)
      if(pos!=5 && pos!=7 && pos!=8)
	if((data->tg.h.GeHP&(1<<(pos-1)))!=0)
	  if(data->tg.det[pos].h.Gefold>0)
	    for(col=0;col<NCOL;col++)
	      if((data->tg.det[pos].h.GeHP&(1<<col))!=0)
		{
		  fold=0;
		  for(segm=1;segm<NSEGTIGR;segm++)
		    if((data->tg.det[pos].ge[col].h.EHP&(1<<segm))!=0)
		      fold++;
		  hist[fold]++;
		  h->Fill(fold,4*(pos-1)+col);
		}
  return SEPARATOR_DISCARD;
}
/*=======================================================*/
int main(int argc, char *argv[])
{
  input_names_type* name;
  /* TCanvas *canvas; */
  /* TApplication *theApp; */
  FILE* output;
  int numcounts=0;
  char rootFile[132];
  
  if(argc!=2)
    {
      printf("sfu_check_CCSegFold SFU_data_file\n");
      exit(-1);
    }
  
  h = new TH2D("CCSegFold","CCSegFold",10,0,10,64,0,64);
  h->Reset();
  
  /* printf("Program sorts trigger bits histogram \n"); */

  memset(&hist,0,sizeof(hist));
  
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  strcpy(name->fname.inp_data,argv[1]);
  sort(name);

  if((output=fopen("CCSeg_Fold.spn","w"))==NULL)
    {
      printf("Cannot open file\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  
  for(int i=0;i<S4K;i++)
    numcounts+=hist[i];
  
  printf("\n================\n");
  for(int i=0;i<6;i++)
    printf("%d Seg: %9d       Fraction %.3f\n",i,hist[i],(double)hist[i]/numcounts);
  printf("================\n");

  strcpy(rootFile,"CCSegFold.root");
  TFile f(rootFile,"recreate");
  h->GetXaxis()->SetTitle("Segment Fold");
  h->GetYaxis()->SetTitle("Crystal ID");
  h->SetOption("COLZ");
  h->Write();
  f.Close();  

  /* theApp=new TApplication("App", &argc, argv); */
  /* canvas = new TCanvas("TrigBits", "TrigBits",10,10, 500, 300); */
  /* canvas->cd(); */
  /* gPad->SetLogy(1); */
  /* h->Draw(); */
  
  /* theApp->Run(kTRUE); */
}
