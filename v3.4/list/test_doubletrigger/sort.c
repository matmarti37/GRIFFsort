#include "sort.h"
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  static gmap map;
  size_t son;
  node  current,next;
  unsigned long long dt;
  unsigned long pos;
  int chan1,chan2;
  
  if(argc!=6)
    {
      printf("list_test_doubletrigger list_input_data map window_[ns] ch1 ch2\n");
      exit(-1);
    }

  chan1=atoi(argv[4]);
  chan2=atoi(argv[5]);

  printf("Program sorts time difference between HPGe CC hits for the SAME channel within a time window on the list\n");

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
  h=new TH1D("TSdiff","TSdiff",S32K,0,S32K);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  while(1)
    {
      // Reads a fragment
      if(fread(&current,son,1,inp)!=1)
      	break;

      // If CC channel, move forward
      //if(CC_channel(&current,&map)==1)
      if(current.chan==chan1)
      	{
      	  pos=ftell(inp);//save current position

      	  while(1)
      	    {
	      // Reads a fragment
      	      if(fread(&next,son,1,inp)!=1)
      		break;
	      
		  // Calculate time difference
      		  dt=next.tsns-current.tsns;
		  // If dt too big, move on
      		  if(dt>window)
      		    break;
	      // If CC channel, move forward
      	      //if(CC_channel(&next,&map)==1)
	      if(next.chan==chan2)
      		{
		  // Compare channel, only move forward if they're the same
		  //if(next.chan==current.chan)
		    {
		      //printf("%d\t%d\n",next.chan,current.chan);
		      h->Fill((int)dt);
		      if(dt<S32K)
			hist[dt]++;
		    }
      		}
      	    }
	  // Go back to original fragment and move forward
      	  fseek(inp,pos,SEEK_SET);
      	}
    }

  fclose(inp);

  if((output=fopen("HPGe_CC_dt_doubletriggertest.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
