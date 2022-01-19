#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;

  if(ptr->chan==chn)
    if((d=ptr->waveform_length)!=0)
    {

      get_tmax(ptr->waveform_length,waveform,&wpar);
 
      print_fragment_info(ptr);
      printf("Waveform (tmax,max): (%.2f,%.2f)\n",wpar.tmax,wpar.max);
      if(h!=NULL) delete h;
      h=new TH1D("Waveform","Waveform",ptr->waveform_length,0,ptr->waveform_length);
      if(c!=NULL) delete c;
      c = new TCanvas("Waveform", "Waveform",10,10, 700, 500);
      
      for(Int_t i=0;i<ptr->waveform_length;i++)
	h->Fill(i,waveform[i]);
      
      h->Draw("HIST");
      theApp->Run(kTRUE);
	    
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

  int ac=0;
  char *av[1];

 if(argc!=3)
    {
      printf("\n wfit_show_bad_tmax midas_input_data_file_name channel\n");
      exit(-1);
    }

  chn=atoi(argv[2]);
  theApp=new TApplication("App", &ac, av);
  printf("Program shows bad maximum fit events for selected channel\n");

/* do sorting */
  sort_but_not_assemble(argv[1]);
 /* display results */
 
}
