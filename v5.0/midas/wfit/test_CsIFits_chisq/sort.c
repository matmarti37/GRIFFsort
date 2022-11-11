#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;
  int type;

 
    if( (ptr->chan) >= chn_low)  
      if( (ptr->chan) <= chn_high)
	if((d=ptr->waveform_length)!=0)
	  {
	    fit_CsI_waveform(d,waveform,par,&wpar);
	    /* print_WavePar(&wpar); */
	    /* print_ShapePar(par); */
	    /* getc(stdin); */
	    type=par->type;
	    /* printf("type %d\n",type); */
	    /* getc(stdin); */
	    if(type>=type_low)
	      if(type<=type_high)
		{
		  h->Fill(par->chisq/par->ndf);
		}
	  }

  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  TApplication *theApp;
  char runFile[132];
  int ac=0;
  char *av[1];

  h=NULL;
  if(argc!=10)
    {
      printf("wfit_test_CsIFit_chisq midas_input_data channel_low channel_high tRC tF tS tGamma type_low type_high\n");
      exit(-1);
    }
  theApp=new TApplication("App", &ac, av);
  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  printf("Program tests chi square for CsI waveform fits.\n");
  strcpy(runFile,argv[1]);

  chn_low=atoi(argv[2]);
  chn_high=atoi(argv[3]);

  par->t[1]=atof(argv[4]); //set tRC
  par->t[2]=atof(argv[5]); //set tF
  par->t[3]=atof(argv[6]); //set tS
  par->t[4]=atof(argv[7]); //set tGamma
  /* counter=atoi(argv[8]); */
  type_low=atoi(argv[8]);
  type_high=atoi(argv[9]);

  h=new TH1D("Chisq","Chisq",1000000,-10,1000000-10);
  h->Reset();
  
  sort_but_not_assemble(runFile);  
 
  h->GetXaxis()->SetTitle("chisq");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("Counts");
  h->GetYaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitleOffset(1.5);
  
  h->Draw("HIST");
  theApp->Run();
}
