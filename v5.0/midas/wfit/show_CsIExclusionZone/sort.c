#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;
 
  if(ptr->chan==chn)
    if((d=ptr->waveform_length)!=0)
    {
      print_fragment_info(ptr);
      get_exclusion_zone_for_CsI(d,waveform,&wpar);
      print_WavePar(&wpar);
      show_CsI_exclusion_zone(d,waveform,&wpar,theApp);
    }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  char runFile[132];
  int ac=0;
  char *av[1];
 
  if(argc!=3)
    {
      printf("wfit_test_CsIExclusionZone midas_input_data channel\n");
      exit(-1);
    }
  
  printf("Program tests exclusion zone for CsI waveforms.\n");
  strcpy(runFile,argv[1]);
  chn=atoi(argv[2]);

  theApp=new TApplication("App", &ac, av);

  sort_but_not_assemble(runFile);
}
