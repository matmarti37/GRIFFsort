#include "sort.h"
int analyze_list(int limit,int offset,node* curr,gmap* map)
{
  long long diff;
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//channel present on the CC list
	  if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//channel present on the CC list   
	    {
	      
	      if(offset==0)
		{
		  Estore=curr->ch.charge;
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

	      
	      
	      if((int)diff>=time_low)
		if((int)diff<=time_high)
		  if(curr->ch.charge>=Egate_low)
		    if(Estore>=Egate_low)
		      if(curr->ch.charge<=Egate_high)
			if(Estore<=Egate_high)
			  {
			    h->Fill(curr->ch.charge/divisor,Estore/divisor);
			    //h->Fill(Estore/divisor,curr->ch.charge/divisor);
			  }
	      
	      Estore=curr->ch.charge;
	      tsstore=curr->tsns;
	      //printf("Current energy: %lld\n",Estore);
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
  
  if(argc!=8)
    {
      printf("list_HPGe_CC_time_difference list_input_data map time_low time_high E_divisor E_gate_low E_gate_high\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive HPGe CC fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  time_low=atoi(argv[3]);
  time_high=atoi(argv[4]);
  divisor=atoi(argv[5]);
  Egate_low=atoi(argv[6]);
  Egate_high=atoi(argv[7]);
  read_map(argv[2],&map);
  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH2D("TSdiff","TSdiff",S1K,0,S32K,S1K,0,S32K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);


  gStyle->SetPalette(1);
  h->Draw("COLZ");
  theApp->Run(kTRUE);

  
}
