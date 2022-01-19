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
 
 long long csi=-1; long long tig=-1; long long sup=-1;
 
 //long long time=ptr->timestamp;
 //long long time=(10*ptr->cfd)/16;
 long long time=( (ptr->timestamp)&(~0x3ffff) )*10 + ((10*ptr->cfd)/16); // WITH x10 on TIMESTAMP
 if(time<0) {neg_time++;}
 if(csi_position!=-1) {csi=time;}
 else if(tig_position!=-1) {tig=time;}
 else if(sup_position!=-1) {sup=time;}
 
 tot_events++;
 
 FILE *outputfile; outputfile=fopen("timing_data.txt","a");
 fprintf(outputfile,"%lld\t%lld\t%lld\t%lld\n",tot_events,csi,tig,sup);
 fclose(outputfile);
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
 
 // Reads map files
 read_csi_map(csi_map_filename);
 read_tig_map(tig_map_filename);
 read_sup_map(sup_map_filename);
 
 //char* data_filename=argv[1];
 //double fraction;
 // clears data file
 printf("Clearing output file\n\n");
 FILE *outputfile; outputfile=fopen("timing_data.txt","w"); fclose(outputfile);
 
 // Read data files and perform sort
 sort_data(data_filename);
 printf("\n%d\n",neg_time);
 printf("\nLONG LONG:           %lu bytes = %lu bits\n",sizeof(long long),(8*sizeof(long long)));
 printf("\nINT:                 %lu bytes = %lu bits\n",sizeof(int),(8*sizeof(int)));
 return 0;
}
