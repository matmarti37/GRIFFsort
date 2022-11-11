#include "sort.h"

#include "functions.c"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
 Int_t d;
 WaveFormPar wpar;
 double red_chisq, amplitude, energy;
 int detector,ring;
 
 detector=det_map[ptr->chan];
 ring=dets_ring[detector];
 
 if(detector>=det_low && detector<=det_high)
 {
  if((d=ptr->waveform_length)!=0)
  {
   fit_CsI_waveform(d,waveform,par,&wpar);
   red_chisq=par->chisq/par->ndf;
   if(red_chisq<=chisq_cutoff && par->type==1)
   {
    amplitude=par->am[2]+par->am[3]; // Amplitude = Fast + Slow
    energy=(TIP_cal_params[detector][0]+TIP_cal_params[detector][1]*amplitude); // Calibrated
    
    // Fill detector by detector histograms
    det_h[detector]->Fill(energy);
    if(ampl_flag==1) {uncal_det_h[detector]->Fill(amplitude);}
    
    ring_h[ring]->Fill(energy);
    if(ampl_flag==1) {uncal_ring_h[ring]->Fill(amplitude);}
   }
  }
 }
 return 0;
}
 
/*================================================================*/
int main(int argc, char *argv[])
{
 // Checks command line arguments
 if(argc!=2) {printf("midas_TIP_cal_amplitude parameter_file\n"); exit(-1);}
 
 // Initializes parameters for waveform fitting
 par=(ShapePar*)malloc(sizeof(ShapePar)); memset(par,0,sizeof(ShapePar));
 
 // Reads parameter file
 char* param_filename=argv[1];
 read_parameter_file(param_filename);
 
 // Reads detector map file
 read_map_file(map_filename);
 
 // Reads calibration file
 TIP_calibration(cal_filename);
 
 // Reads ring map and determines det_low and det_high
 read_ring_map(ring_filename);
 
 // Creates histograms
 create_histograms();
 
 // Read data files and perform sort
 sort_data(data_filename);
 
 // Save root files with histograms
 create_root_files(output_filename);
 
 return 0;
}
