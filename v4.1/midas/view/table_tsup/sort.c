#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  //Upper bits of the time stamp
  int tsup; 
  tsup=(int)((ptr->timestamp>>32)&0xffff);

  h[tsup]++;  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  char in_filename[132];
  char out_filename[132];
  FILE* output;
  int low=0,high=max_tsup;
  int check=0;

  if(argc!=3)
    {
      printf("midas_view_hist_tsup midas_input_data table_output_file\n");
      exit(-1);
    }

  memset(&h,0,sizeof(h));
  strcpy(in_filename,argv[1]);
 
  /* do sorting */
  sort_but_not_assemble(in_filename);
  

  strcpy(out_filename,argv[2]);
  if((output=fopen(out_filename,"a"))==NULL)
    {
      printf("ERROR!!! I cannot open the output file.\n");
      exit(EXIT_FAILURE);
    }

  for(int i=0;i<max_tsup;i++)
    {
      if(h[i]!=0 && check==1) {low=i-1; break;}
      if(h[i]!=0 && check==0) {check=1;}
      if(h[i]==0) {check=0;}
    }
  check=0;
  for(int i=max_tsup;i>0;i--)
    {
      if(h[i]!=0 && check==1) {high=i+1; break;}
      if(h[i]!=0 && check==0) {check=1;}
      if(h[i]==0) {check=0;}
    }
  
  fprintf(output,"%s;%d;%d;",in_filename,low,high);
  for(int i=0;i<max_tsup;i++)
    if(h[i]!=0)
      fprintf(output,"%d-%d\t",i,h[i]);
  fprintf(output,"\n");

  
  fclose(output);
}
