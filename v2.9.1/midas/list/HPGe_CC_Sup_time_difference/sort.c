#include "sort.h"

/*================================================================*/
int Sup_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->supp_lt[curr->chan-map->tig_min].seg>0)//channel is a BGO suppressor
	  if(map->supp_lt[curr->chan-map->tig_min].seg<NSUP)//channel is a BGO suppressor 
	    if(map->supp_lt[curr->chan-map->tig_min].pos>0)//valid TIGRESS position
	      if(map->supp_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid TIGRESS position
		return 1;
  
  return 0;	      
}
/*================================================================*/
int CC_channel(node* curr, gmap* map)
{
  if(curr->chan>=map->tig_min)
    if(curr->chan<=map->tig_max)
      if((curr->ch.timestamp|curr->ch.timestamp_up)!=0)//ignore bad events at the start
	if(map->hpge_lt[curr->chan-map->tig_min].seg==0)//channel is the central contact
	  if(map->hpge_lt[curr->chan-map->tig_min].pos>0)//valid position
	    if(map->hpge_lt[curr->chan-map->tig_min].pos<NPOSTIGR)//valid position 
	      return 1;
  
  return 0;	      
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  int   trig;
  unsigned long long  dt;
  unsigned long pos;
  
  if(argc!=4)
    {
      printf("list_HPGe_CC_Sup_time_difference list_input_data map window_[ns]\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between HPGe CC and BGO suppressor fragments within a time window on the list\n");


  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
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
	      if(Sup_channel(&next,&map)==1)
		{
		  h->Fill((int)dt);
		  if(dt<S16K)
		    hist[S16K+dt]++;
		}
	    }
	  fseek(inp,pos,SEEK_SET);
	}

      
      if(Sup_channel(&current,&map)==1)
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

		  if((trig=next.trig)<1)
		    {
		      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",trig,current.tsns,current.chan);
		      exit(0);
		    }
		  h->Fill(-(int)dt);
		  if(dt<S16K)
		    hist[S16K-dt]++;
		}	      
	      
	    }
	  fseek(inp,pos,SEEK_SET);	  
	}
      
     
    }

  fclose(inp);

  if((output=fopen("HPGe_CC_Sup_dt.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
