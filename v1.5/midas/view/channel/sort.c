#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  if(ptr->chan==chn)
    {
      printf("=========================================================\n");
      printf("      Time Stamp :   %8ld 0x%8.8lx\n",ptr->timestamp,ptr->timestamp);
      printf("  Trigger number :   %8d\n",ptr->trigger_num&0x0fffffff);
      printf(" Trigger request :   %8d\n",ptr->trig_req&0x0fffffff);
      printf("  Trigger accept :   %8d\n",ptr->trig_acc&0x0fffffff);
      printf("         Address :   %8d\n",ptr->address);
      printf("         Channel :   %8d\n",ptr->chan);
      printf("          H-Type :   %8d\n",ptr->htype);
      printf("          D-Type :   %8d\n",ptr->dtype);
      printf("          Net ID : 0x%8.8x\n",ptr->net_id);
      printf("       Master ID : 0x%8.8x\n",ptr->master_id);
      printf("  Master pattern : 0x%8.8x\n",ptr->master_pattern);
      printf("          Energy :   %8d\n",ptr->energy); 
      printf("             CFD :   %8d\n",ptr->cfd); 
      printf("Waveform present :   %8d\n",ptr->wf_present);
      printf(" Waveform length :   %8d\n",ptr->waveform_length);
 
      if(ptr->waveform_length!=0)
	{
	  if(h!=NULL) delete h;
	  h=new TH1D("Waveform","Waveform",ptr->waveform_length,0,ptr->waveform_length);
	  if(c!=NULL) delete c;
	  c = new TCanvas("Waveform", "Waveform",10,10, 700, 500);
	  
	  for(Int_t i=0;i<ptr->waveform_length;i++)
	    h->Fill(i,waveform[i]);
	  
	  h->Draw("HIST");
	  theApp->Run(kTRUE);
	}}
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  int ac;
  char* av[1];

  ac=1;
  av[0]=(char*)malloc(sizeof(char));
  if(argc!=3)
    {
      printf("view_channel midas_data_file channel\n");
      exit(-1);
    }
  
  chn=atoi(argv[2]);
  theApp=new TApplication("App", &ac, av);
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  /* display results */
  printf("Program provides information on selected channel.\n");
}
