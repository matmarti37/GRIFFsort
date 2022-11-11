#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  WaveFormPar wpar;
  double charge;
  double ampl;  
  int channel;

  channel=ptr->chan;

  if(channel>=csi_low && channel<=csi_high)
    if(ptr->waveform_length!=0)
      {
	wpar.baseline_range=CSI_BASELINE_RANGE;
	get_baseline(wpar.baseline_range,waveform,&wpar);
	get_tmax(ptr->waveform_length,waveform,&wpar);
	  
	charge=(double)(ptr->energy)/125.;
	ampl=wpar.max-wpar.baseline;
	  
	h[channel]->Fill(ampl,charge);
	hcsi->Fill(ampl,charge);
      }
   
 
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  char HistName1[132];
  char title[132];

  if(argc!=4)
    {
      printf("wfit_amplitude midas_input_data csi_low csi_high\n");
      exit(-1);
    }

  printf("Program plots tmax-baseline vs charge for waveforms.\n");
  printf("Results are stored in file amplitude.root\n");
  printf("Results can be inspected using root TBrowser\n");
  csi_low=atoi(argv[2]);
  csi_high=atoi(argv[3]);

  for(int i=0;i<S2K;i++)
    {
      sprintf(HistName1,"amplitude_%04d",i);
      h[i]=new TH2D(HistName1,HistName1,512,0,S4K,512,0,S16K);
      h[i]->Reset();
    }

  hcsi=new TH2D("CsI Sum","CsI Sum",512,0,S4K,512,0,S16K);
  hcsi->Reset();
  
  sort_but_not_assemble(argv[1]);

  sprintf(title,"amplitude.root");
  TFile f(title, "recreate");
  
  for(int i=0;i<S2K;i++)
    {
      /* only write if hitogram is not empty */
      if(h[i]->GetEntries())
	{
	  sprintf(HistName1, "amplitude_%04d",i);
	  h[i]->GetXaxis()->SetTitle("amplitude");
	  h[i]->GetXaxis()->CenterTitle(true);
	  h[i]->GetYaxis()->SetTitle("charge");
	  h[i]->GetYaxis()->CenterTitle(true);
	  h[i]->GetYaxis()->SetTitleOffset(1.5);
	  h[i]->SetOption("COLZ");
	  h[i]->Write();
	}
    }


  if(hcsi->GetEntries())
    {
      hcsi->GetXaxis()->SetTitle("amplitude");
      hcsi->GetXaxis()->CenterTitle(true);
      hcsi->GetYaxis()->SetTitle("charge");
      hcsi->GetYaxis()->CenterTitle(true);
      hcsi->GetYaxis()->SetTitleOffset(1.5);
      hcsi->SetOption("COLZ");
      hcsi->Write();  
    }
  
  return 0;
}
