#include "sort.h"
int analyze_list(int limit,int offset,node* curr,gmap* map)
{
  /* long long diff; */
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//channel present on the CC list
	  if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//channel present on the CC list   
	    {
	      
	      /* if(offset==0) */
	      /* 	return 0; */
	      /* printf("position is %d\n",map->hpge_lt[curr->chan-map->tig_min].pos); */
	      h->Fill(curr->ch.charge/divisor,map->hpge_lt[curr->chan-map->tig_min].pos);
	    }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  /* FILE* output; */
  int i;
  size_t son;
  node nd;
  /* int ac; */
  /* char* av[1]; */
  static gmap map;
  
  /* ac=0; */
  /* av[0]=0; */
  son=sizeof(node);
  
  if(argc!=4)
    {
      printf("list_HPGe_CC_energy_crystal list_input_data map divisor\n");
      exit(-1);
    }
  divisor=atoi(argv[3]);
 
  printf("Program sorts time difference histogram between consecutive HPGe CC fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  read_map(argv[2],&map);
  /* memset(&hist,0,sizeof(hist)); */
  /* theApp=new TApplication("App", &ac, av); */
  /* if(h!=NULL) delete h; */
  h=new TH2D("Ch_v_Det","Ch_v_Det",65536,0,65536,NPOSTIGR,0,NPOSTIGR);
  /* if(c!=NULL) delete c; */
  /* c = new TCanvas("TS", "TS",10,10, 700, 500); */

  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);

  TFile f("ch_v_det.root","recreate");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Detector");
  h->SetOption("COLZ");
  h->Write();
  f.Close();

  /* if((output=fopen("HPGe_CC_E.spn","w"))==NULL) */
  /*   { */
  /*     printf("ERROR!!! I cannot open the spn file.\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
  /* fwrite(hist,sizeof(hist),1,output); */
  /* fclose(output); */

  /* h->Draw("HIST"); */
  /* theApp->Run(kTRUE); */

  
}
