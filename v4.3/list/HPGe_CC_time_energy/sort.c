#include "sort.h"
int analyze_list(int limit,int offset,node* curr,gmap* map)
{
  double energy;
  long long diff;
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//channel present on the CC list
	  if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//channel present on the CC list   
	    {
	      
	      if(offset==0)
		{
		  tsstore=curr->tsns;
		  return 0;
		}
	      
	      diff=curr->tsns-tsstore;
	      
	      
	      if(diff<0)
		{
		  printf("current %16lld stored %16lld\n",curr->tsns,tsstore);
		  printf("list disordered, diff is %16lld\n",diff);
		  printf("Exiting\n");
		  exit(0);
		}
	      energy=curr->ch.charge/divider;
	      //h->Fill(energy,diff);
	      h->Fill(diff,energy);
	      tsstore=curr->tsns;
	    }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  int i;
  size_t son;
  node nd;
  int ac;
  char* av[1];
  static gmap map;
  
  ac=0;
  av[0]=0;
  son=sizeof(node);
  
  if(argc!=4)
    {
      printf("list_HPGe_CC_time_difference list_input_data map divider\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive HPGe CC fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  read_map(argv[2],&map);
  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH2D("CC_Charge","CC_Charge",S1K,0,S4K,S4K,0,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  divider=atoi(argv[3]);
  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);

  TFile f("tsdiff_vs_charge.root","recreate");
  h->GetXaxis()->SetTitle("TSDiff");
  h->GetYaxis()->SetTitle("CC Charge");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->CenterTitle(true);
  h->SetOption("colz");
  h->Write();
  //h->Draw();
  //theApp->Run(kTRUE);

  
}
