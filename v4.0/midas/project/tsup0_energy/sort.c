#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  if(((int)((ptr->timestamp>>32)&0xffff))==0)
    {
      if(((ptr->energy)>=0) && ((ptr->energy)<=S32K))
	{
	  hist_tsup0[(int)(ptr->energy)]++;
	}
    }
  else
    {
      if(((ptr->energy)>=0) && ((ptr->energy)<=S32K) && (ptr->chan<1024))
	{
	  hist_not_tsup0[(int)(ptr->energy)]++;
	}
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;

  if(argc!=2)
    {
      printf("midas_project_tsup0_energy midas_data_file\n");
      printf("Program sorts energy of events with and without tsup = 0.\n");
      exit(-1);
    }
  printf("Program sorts energy of events with tsup = 0.\n");
  
  sort_but_not_assemble(argv[1]);
  
  if((output=fopen("tsup0_energy.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist_tsup0,sizeof(hist_tsup0),1,output);
  fclose(output);

  if((output=fopen("not_tsup0_energy.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist_not_tsup0,sizeof(hist_not_tsup0),1,output);
  fclose(output);
  
  }
