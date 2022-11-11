#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  Int_t d;
  WaveFormPar wpar;
  double ch;
  int type;

 

  if((d=ptr->waveform_length)!=0)
    //if(ptr->chan==chn)
    if( ( ((ptr->chan)>=1024) && ((ptr->chan)<=1090) ) || ( ((ptr->chan)>=1280) && ((ptr->chan)<=1344) ) )
      {
	fit_CsI_waveform(d,waveform,par,&wpar);
	ch=par->chisq/par->ndf;
	
	type=par->type;
  
	
	if(ch>=chmin)
	  if(ch<=chmax)
	    if(type>=type_low)
	      if(type<=type_high)
	        //if((par->am[2]+par->am[3])>1200) // Checking to see if we have bad fits
		{
		  print_fragment_info(ptr);
		  show_CsI_Fit(d,waveform,par,&wpar,theApp);
		}
	
      }
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{

// int ac;
// char *av[10];

  char name[128];


 if(argc!=10)
    {
      printf("wfit_show_CsIFits midas_input_data tRC tF tS tGamma chisq_min chisq_max type_low type_high\n");
      printf("type 1 = 2 component, type 2 = slow only 3=PIN hit\n");
      exit(-1);
    }

  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  strcpy(name,argv[1]);
  //chn=atoi(argv[2]);
  par->t[1]=atof(argv[2]); //set tRC
  par->t[2]=atof(argv[3]); //set tF
  par->t[3]=atof(argv[4]); //set tS
  par->t[4]=atof(argv[5]); //set tGamma
  chmin=atof(argv[6]);
  chmax=atof(argv[7]);
  type_low=atoi(argv[8]);
  type_high=atoi(argv[9]);

  theApp=new TApplication("App", &argc, argv);

/* do sorting */
  FILE *inputfile;
  inputfile=fopen(name,"r+");
  int linelen;
  if(inputfile==NULL)
   {
    printf("\n Error in opening file \n");
    exit(-1);
   }
  char line[256];
  while(fgets(line,sizeof(line),inputfile))
   {
    printf("\n %s \n",line);
    linelen=strlen(line);
    if(line[linelen-1]=='\n')
     {
      line[linelen-1]=0;
     }
    sort_but_not_assemble(line);
   }
  fclose(inputfile);
  //sort_but_not_assemble(name);
 /* display results */
}
