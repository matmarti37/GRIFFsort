#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;
  int type;
  
  // Opens the output file for appending to it
  FILE *pFile;
  pFile=fopen(textfilename,"a");
  if(pFile==NULL)
   {
    perror("Error opening file.");
   }
  else
   {

 
    //if( (ptr->chan) >= chn_low) 
    if( ( ((ptr->chan)>=1024) && ((ptr->chan)<=1090) ) || ( ((ptr->chan)>=1280) && ((ptr->chan)<=1344) ) )
      //if( (ptr->chan) <= chn_high)
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
		  // Appends the chisq/ndf to the end of the output file
		  fprintf(pFile,"%2.13f\n",par->chisq/par->ndf);
		}
	  }

   }
  fclose(pFile);
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  //TApplication *theApp;
  //char runFile[132];
  int ac=0;
  char *av[1];

  h=NULL;
  if(argc!=10)
    {
      printf("wfit_test_CsIFit_chisq midas_input_data tRC tF tS tGamma type_low type_high output_directory output_filename\n");
      exit(-1);
    }
  theApp=new TApplication("App", &ac, av);
  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  printf("Program tests chi square for CsI waveform fits.\n");
  //strcpy(runFile,argv[1]);

  //chn_low=atoi(argv[2]);
  //chn_high=atoi(argv[3]);
  //chn_low=1000;1280->1344, 1024->1090
  //chn_high=1400;

  par->t[1]=atof(argv[2]); //set tRC
  par->t[2]=atof(argv[3]); //set tF
  par->t[3]=atof(argv[4]); //set tS
  par->t[4]=atof(argv[5]); //set tGamma
  /* counter=atoi(argv[8]); */
  type_low=atoi(argv[6]);
  type_high=atoi(argv[7]);
  
  // Takes the last argument as the output file for chisq/ndf values
  output_dir=argv[8];
  outputfile=argv[9];
  
  strcpy(textfilename,output_dir);
  strcat(textfilename,"/");
  strcat(textfilename,outputfile);
  strcat(textfilename,".txt");
  
  strcpy(rootfilename,output_dir);
  strcat(rootfilename,"/");
  strcat(rootfilename,"rootfiles/");
  strcat(rootfilename,outputfile);
  strcat(rootfilename,".root");
  
  // Clears the file which exists with that name
  FILE *pFile;
  pFile=fopen(textfilename,"w");
  fclose(pFile);

  h=new TH1D("Chisq","Chisq",1000000,-10,1000000-10);
  h->Reset();
  
  // This is where I started adding my own code to loop through files
  FILE *inputfile;
  char* inputfilename=argv[1];
  inputfile=fopen(inputfilename,"r+");
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
  
  
  // This is where I ended -- i.e. the line I replaced
  //sort_but_not_assemble(runFile);
  
  // Trying to write the data to a root file
  char title[256];
  sprintf(title, "%s", rootfilename);
  TFile f(title, "recreate");
  
  if(h->GetEntries())
   {
    h->GetXaxis()->SetTitle("chisq");
    h->GetXaxis()->CenterTitle(true);
    h->GetYaxis()->SetTitle("Counts");
    h->GetYaxis()->CenterTitle(true);
    h->GetYaxis()->SetTitleOffset(1.5);
    h->Write();
   }
  return 0;
  
  //h->Draw("HIST");
  //theApp->Run();
}
