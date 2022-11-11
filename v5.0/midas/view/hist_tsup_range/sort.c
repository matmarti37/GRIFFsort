#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{  

}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* input;
  int i;

  if(argc!=1)
    {
      printf("midas_view_hist_tsup_range\n");
      exit(-1);
    }

  printf("Takes the histogram of tsup values from midas_view_hist_tsup and determines the valid range.\n");
  
  //memset(&h,0,sizeof(h)); 

  if((input=fopen("TSUP_HIST.mca","r"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(-2);
    }

  for (i=0; i<S32K; i++)
    {
      fscanf(input, "%1d", &h[i]);
      printf("%d: %d",i,h[i]);
      getc(stdin);
    }

  fclose(input);
}
