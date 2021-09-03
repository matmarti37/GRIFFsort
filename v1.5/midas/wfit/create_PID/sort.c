#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
  int d;
  WaveFormPar wpar;
  int type;
  long double ratio, charge;
  
  if((((ptr->chan)>=1024) && ((ptr->chan)<=1090) ) || ( ((ptr->chan)>=1280) && ((ptr->chan)<=1344)))
   {
    if((d=ptr->waveform_length)!=0)
     {
      fit_CsI_waveform(d,waveform,par,&wpar);
      type=par->type;
      if(type==1)
       {
        ratio=100*(par->am[3]/par->am[2])+100; //ratio = 100*amplitude_slow / amplitude_fast
        charge=(double)(ptr->energy)/125.;
        //full_h->Fill(charge,ratio);
        //full_h->Fill(par->am[3],ratio);
        full_h->Fill(par->am[3],par->am[2]);
        if((par->chisq/par->ndf)<=chi_sq_cutoff)
         {
          //accepted_h->Fill(charge,ratio);
          //accepted_h->Fill(par->am[3],ratio);
          accepted_h->Fill(par->am[3],par->am[2]);
         }
        else
         {
          //rejected_h->Fill(charge,ratio);
          //rejected_h->Fill(par->am[3],ratio);
          rejected_h->Fill(par->am[3],par->am[2]);
         }
       }
     }
   }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  //TApplication *theApp;
  //char runFile[132];
  int ac=0;
  char *av[1];

  full_h=NULL;
  if(argc!=8)
    {
      printf("wfit_test_CsIFit_chisq midas_input_data tRC tF tS tGamma output_directory chi_sq_cutoff\n");
      exit(-1);
    }
  theApp=new TApplication("App", &ac, av);
  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  printf("Program creates PID plots.\n");

  par->t[1]=atof(argv[2]); //set tRC
  par->t[2]=atof(argv[3]); //set tF
  par->t[3]=atof(argv[4]); //set tS
  par->t[4]=atof(argv[5]); //set tGamma
  
  // Takes the last argument as the output file
  output_dir=argv[6];
  chi_sq_cutoff=atof(argv[7]);
  
  //full_h=new TH2D("All","All",S16K,0,S16K,150,100,250);
  //full_h=new TH2D("All","All",S2K,0,S2K,150,100,250);
  full_h=new TH2D("All","All",S2K,0,S2K,S2K,0,S2K);
  full_h->Reset();
  //accepted_h=new TH2D("Accepted","Accepted",S16K,0,S16K,150,100,250);
  //accepted_h=new TH2D("Accepted","Accepted",S2K,0,S2K,150,100,250);
  accepted_h=new TH2D("Accepted","Accepted",S2K,0,S2K,S2K,0,S2K);
  accepted_h->Reset();
  //rejected_h=new TH2D("Rejected","Rejected",S16K,0,S16K,150,100,250);
  //rejected_h=new TH2D("Rejected","Rejected",S2K,0,S2K,150,100,250);
  rejected_h=new TH2D("Rejected","Rejected",S2K,0,S2K,S2K,0,S2K);
  rejected_h->Reset();
  
  // This block loops through multiple midas files
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
  // End of block for looping through midas files
  
  // Trying to write the data to a root file
  char title[132];
  sprintf(title, "%s/%d_fits.root",output_dir,chi_sq_cutoff);
  TFile f(title, "recreate");

  //full_h->GetXaxis()->SetTitle("Energy");
  full_h->GetXaxis()->SetTitle("A_S");
  full_h->GetXaxis()->CenterTitle(true);
  //full_h->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  full_h->GetYaxis()->SetTitle("A_F");
  full_h->GetYaxis()->CenterTitle(true);
  full_h->GetYaxis()->SetTitleOffset(1.5);
  full_h->SetOption("COLZ");
  full_h->Write();  
  //accepted_h->GetXaxis()->SetTitle("Energy");
  accepted_h->GetXaxis()->SetTitle("A_S");
  accepted_h->GetXaxis()->CenterTitle(true);
  //accepted_h->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  accepted_h->GetYaxis()->SetTitle("A_F");
  accepted_h->GetYaxis()->CenterTitle(true);
  accepted_h->GetYaxis()->SetTitleOffset(1.5);
  accepted_h->SetOption("COLZ");
  accepted_h->Write();  
  //rejected_h->GetXaxis()->SetTitle("Energy");
  rejected_h->GetXaxis()->SetTitle("A_S");
  rejected_h->GetXaxis()->CenterTitle(true);
  //rejected_h->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  rejected_h->GetYaxis()->SetTitle("A_F");
  rejected_h->GetYaxis()->CenterTitle(true);
  rejected_h->GetYaxis()->SetTitleOffset(1.5);
  rejected_h->SetOption("COLZ");
  rejected_h->Write();  
  return 0;
}
