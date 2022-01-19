#include "sort.h"

#include "functions.c"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
 int channel=ptr->chan;
 int csi_position=csi_pos[channel];
 int tig_position=tig_pos[channel];
 int sup_position=sup_pos[channel];
 
 if(csi_position==-1 && tig_position==-1 && sup_position==-1)
 {
  bad_channel++;
  return 0;
 }
 
 if(csi_position!=-1) {csi_count++;}
 
 //long long timestp=ptr->timestamp;
 
 long long time=( (ptr->timestamp)&(~0x3ffff) )*10 + ((10*ptr->cfd)/16); // WITH x10 on TIMESTAMP
 /* //This gives the same as above
 long long time=(ptr->timestamp&0xfffffffffffc0000)<<4;
 time+=ptr->cfd;
 time*=10;
 time/=16;
 */
 
 long long diff;
 
 
 if(csi_position!=-1)
  {
   diff=(time-prev_timestamp);
   time_diff->Fill(diff);
   prev_timestamp=time;
  }

 
 return 0;
}
 
/*================================================================*/
int main(int argc, char *argv[])
{
 // Checks command line arguments
 if(argc!=2) {printf("TIP_cal_PID parameter_file\n"); exit(-1);}
 
 // Initializes parameters for waveform fitting
 par=(ShapePar*)malloc(sizeof(ShapePar)); memset(par,0,sizeof(ShapePar));
 
 // Reads parameter file
 char* param_filename=argv[1];
 read_parameter_file(param_filename);
 
 time_diff=new TH1D("Time Differences","Time Differences",S4K,0,S4K); time_diff->Reset();
 
 // Reads map files
 read_csi_map(csi_map_filename);
 read_tig_map(tig_map_filename);
 read_sup_map(sup_map_filename);
 
 prev_timestamp=0; bad_channel=0; csi_count=0;
 
 // Read data files and perform sort
 sort_data(data_filename);
 
 TFile f("diff_file.root","recreate");
 time_diff->GetXaxis()->SetTitle("Time Difference");
 time_diff->GetXaxis()->CenterTitle(true);
 time_diff->GetYaxis()->SetTitle("Counts");
 time_diff->GetYaxis()->CenterTitle(true);
 time_diff->GetYaxis()->SetTitleOffset(1.5);
 time_diff->Write();
 
 printf("Bad Channels: %d\n",bad_channel);
 printf("CSI Channels: %d\n",csi_count);
 
 
 return 0;
}
