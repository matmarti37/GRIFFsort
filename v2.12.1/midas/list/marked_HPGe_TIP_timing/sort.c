#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE *out;
  static gmap map;
  size_t son;
  node  curr,next;
  unsigned long long dt;
  unsigned long pos;

  
  if(argc!=3)
    {
      printf("list_marked_HPGe_TIP_timing fragment_list map\n");
      exit(-1);
    }
  
 
  printf("Program sorts HPGe CC to TIP timing based on triggers marked on the list of fragments created from GRIF3/GRIF4 midas file.\n");

    if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read access!\n",argv[1]);
      exit(-2);
    }
 
  son=sizeof(node);
  read_map(argv[2],&map);
  memset(&hist,0,sizeof(hist));
  theApp=new TApplication("App", &argc, argv);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",S32K,-S16K,S16K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);
  

  while(1)
    {
      if(fread(&curr,son,1,inp)!=1)
	break;

      if(CC_channel(&curr,&map)==1)
	{
	  if(curr.trig<1)
	    {
	      printf("Incorrect TIGRESS CC trigger %d at tsns %16lld channel %d. Exiting\n",curr.trig,curr.tsns,curr.chan);
	      exit(0);
	    }
	  pos=ftell(inp);//save current position
	  
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;

	      if(next.trig>curr.trig+DTRIG)
		break;
	      
	      if(TIP_channel(&next,&map)==1)
		if(next.trig==curr.trig)
		  {
		    dt=next.tsns-curr.tsns;
		    h->Fill((int)dt);
		    if(dt<S16K)
		      hist[S16K+dt]++;
		  }
	    }
	  
	  fseek(inp,pos,SEEK_SET);
	}

      if(TIP_channel(&curr,&map)==1)
	{
	  pos=ftell(inp);//save current position
	  while(1)
	    {
	      if(fread(&next,son,1,inp)!=1)
		break;

	      if(next.trig>curr.trig+DTRIG)
		break;

	      if(CC_channel(&next,&map)==1)
		if(next.trig==curr.trig)
		  {
		    dt=next.tsns-curr.tsns;
		    h->Fill(-(int)dt);
		    if(dt<S16K)
		      hist[S16K-dt]++;
		  }	      	      
	    }
	}
    }

  fclose(inp);

  if((out=fopen("HPGe_CC_TIP_timing.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,out);
  fclose(out);

  h->Draw("HIST");
  theApp->Run(kTRUE);

}
