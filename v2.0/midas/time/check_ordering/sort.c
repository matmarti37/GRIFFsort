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
 
 int time=ptr->timestamp;
 if(time<prev_timestamp) {out_of_order++;}
 prev_timestamp=time;
 
 tot_events++;
 return 0;
}
 
/*================================================================*/
int main(int argc, char *argv[])
{
 // Checks command line arguments
 if(argc!=2) {printf("TIP_cal_PID data_file\n"); exit(-1);}
 
 // Initializes parameters for waveform fitting
 par=(ShapePar*)malloc(sizeof(ShapePar)); memset(par,0,sizeof(ShapePar));
 
 // Reads parameter file
 char* param_filename=argv[1];
 read_parameter_file(param_filename);
 
 // Reads map files
 read_csi_map(csi_map_filename);
 read_tig_map(tig_map_filename);
 read_sup_map(sup_map_filename);
 
 
 //char* data_filename=argv[1];
 prev_timestamp=0; out_of_order=0; bad_channel=0;
 double fraction;
 
 // Read data files and perform sort
 sort_data(data_filename);
 
 printf("Number of out of order timestamps:        %d\n",out_of_order);
 printf("Total number of fragments                 %d\n",tot_events);
 fraction=(double)out_of_order / (double)tot_events;
 printf("Fraction of out of order fragments:       %2.2e\n",fraction);
 printf("\n\nNumber of bad channel numbers:            %d\n",bad_channel);
 
 return 0;
}
