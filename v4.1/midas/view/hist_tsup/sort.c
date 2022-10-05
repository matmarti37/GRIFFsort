#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  //Upper bits of the time stamp
  int tsup; 
  tsup=(int)((ptr->timestamp>>32)&0xffff);

  h[tsup]++;

  //Records the first thousand tsup values to help track buffer issues.
  //The two histograms can be used to select a good max_TSUP value for midas2list
  if(counter<S32K)
    {
      h2[counter]+=tsup;
      counter++;      
    }  
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;

  if(argc!=2)
    {
      printf("midas_view_hist_tsup midas_input_data\n");
      exit(-1);
    }

  memset(&h,0,sizeof(h));
  memset(&h2,0,sizeof(h2));
  counter=0;
 
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides histograms for the upper bits of the timestamp.\n");

  if((output=fopen("TSUP_HIST.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(h,sizeof(h),1,output);
  fclose(output);

  if((output=fopen("TSUP_HISTORY.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(h2,sizeof(h2),1,output);
  fclose(output);
}
