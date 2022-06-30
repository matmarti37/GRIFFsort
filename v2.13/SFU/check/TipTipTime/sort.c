#include "sort.h"

int analyze_data(raw_event *data)
{
  //int fold=data->csiarray.h.TSfold;
  uint64_t ts, tsup;
  uint64_t tsns;
  uint64_t ts1=0, ts2=0, diff;
  uint64_t one=1;

  if(data->csiarray.h.TSfold==2)
    {
      ts1=0;
      ts2=0;
      count++;
      for(int pos=0;pos<NCSI;pos++)
	{
	  if(((data->csiarray.h.TSHP[pos/64]&(one<<pos%64))!=0))
	    {
	      ts=(data->csiarray.csi[pos].timestamp)&(0xffffffff);
	      printf("Timestamp:   %ld\n",ts);
	      tsup=(data->csiarray.csi[pos].timestamp_up&0xffff);
	      printf("Timestamp up: %ld\n",tsup);
	      tsns=ts|(tsup<<32);
	      printf("Timestamp ns: %ld\n",tsns);

	      tsns*=10;
	      tsns+=(uint64_t)(10.*(data->csiarray.wfit[pos].t[0]));
	      tsns-=2000;
	      
	      if(ts1==0)
	      	ts1=tsns;
	      else
	      	ts2=tsns;
	    }
	}

      printf("TS 1:           %lu\n",ts1);
      printf("TS 2:           %lu\n",ts2);
      if(ts1<ts2)
	diff=ts2-ts1;
      else
	diff=ts1-ts2;
      printf("Difference:   %ld\n",diff);
      h->Fill(diff);
      getc(stdin);
    }
  return SEPARATOR_DISCARD;
}
/*====================================================================*/
int main(int argc, char *argv[])
{
  input_names_type* name;

  if(argc!=2)
    {
      printf("display_RawEvent sfu_input_data\n");
      exit(-1);
    }
  
  printf("Program displays raw events.\n");

  h=new TH1D("TDiff","TDiff",S4K,0,S4K); h->Reset();

  count=0;
  
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  strcpy(name->fname.inp_data,argv[1]);
  sort(name);

  TFile f("TIPDifferences.root","recreate");
  h->GetXaxis()->SetTitle("Time Difference [ns]");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("Counts");
  h->GetYaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitleOffset(0);
  h->Write();
  printf("Number of fold-2 events:  %d\n",count);
}
