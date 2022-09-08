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
  fprintf(output,"%s\t",in_filename);
  /* for(int i=0;i<1024;i++) */
  /*   fprintf(output,"%d-%d\t",i,h[i]); */
  /* fprintf(output,"\n"); */
  /* fprintf(output,"\n"); */
  for(int i=0;i<1024;i++)
    if(h[i]!=0)
      fprintf(output,"%d-%d\t",i,h[i]);
  fprintf(output,"\n");

  
  fclose(output);
}
