#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
 int d, type;
 WaveFormPar wpar;
 int detector=det_map[ptr->chan];
 long double ratio, charge;
 double fast, slow, red_chisq;
 
 if(detector>=det_low && detector<=det_high)
  {
   if((d=ptr->waveform_length)!=0)
    {
     fit_CsI_waveform(d,waveform,par,&wpar);
     type=par->type;
     if(type==1)
      {
       fast=par->am[2];
       slow=par->am[3];
       red_chisq=par->chisq/par->ndf;
       ratio=100*(slow/fast)+100; //ratio=100*a_s/a_f + 100
       charge=(double)(ptr->energy)/50.; //scaling the energy -- will change when calibrated
       
       all_e_r->Fill(charge,ratio);
       all_s_f->Fill(slow,fast);
       all_s_r->Fill(slow,ratio);
       
       if(red_chisq < chi_sq_cutoff)
        {
         acc_e_r->Fill(charge,ratio);
         acc_s_f->Fill(slow,fast);
         acc_s_r->Fill(slow,ratio);
        }
       else if(red_chisq > chi_sq_cutoff)
        {
         rej_e_r->Fill(charge,ratio);
         rej_s_f->Fill(slow,fast);
         rej_s_r->Fill(slow,ratio);
        }
      }
    }
  }
 return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  // Checks the number of arguments
  if(argc!=11)
    {
      printf("wfit_test_CsIFit_chisq midas_input_data map_file tRC tF tS tGamma output_directory chi_sq_cutoff det_low det_high\n");
      exit(-1);
    }
  
  // Creates variables and reads arguments
  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));

  par->t[1]=atof(argv[3]); //set tRC
  par->t[2]=atof(argv[4]); //set tF
  par->t[3]=atof(argv[5]); //set tS
  par->t[4]=atof(argv[6]); //set tGamma
  
  output_dir=argv[7];
  chi_sq_cutoff=atof(argv[8]);
  
  det_low=atoi(argv[9]);
  det_high=atoi(argv[10]);
  
  printf("Program creates PID plots.\n");
  
  // Reads the detector map file
  int i,j=0;
  FILE *det_mapfile;
  char* det_mapfilename=argv[2];
  det_mapfile=fopen(det_mapfilename,"r");
  if(det_mapfile==NULL)
   {
    printf("\n Error in opening det map file \n");
    exit(-1);
   }
  for(i=0;i<S2K;i++)
   {
    det_map[i]=-1;
   }
  char * map_line=NULL;
  size_t len=0;
  ssize_t read;
  int num_items=0;
  int buffer=0,buffer2=0;
  while((read=getline(&map_line,&len,det_mapfile))!=-1)
   {
    num_items=sscanf(map_line,"%d\t%d",&j,&buffer);
    num_items=sscanf(map_line,"%d\t%d",&buffer2,&det_map[j]);
    if(num_items!=2)
     {
      printf("Fix map file\n");
      exit(-1);
     }
   }
  
  // Creates and initializes the histograms
  // e->energy, r->ratio, s->slow, f->fast
  // acc->accepted, rej->rejected, all->all
  acc_e_r=new TH2D("Accept_Energy_Ratio","Accepted",S65K,0,S65K,150,100,250); acc_e_r->Reset();
  acc_s_f=new TH2D("Accept_Slow_Fast","Accepted",S2K,0,S2K,S2K,0,S2K); acc_s_f->Reset();
  acc_s_r=new TH2D("Accept_Slow_Ratio","Accepted",S2K,0,S2K,150,100,250); acc_s_r->Reset();
  
  rej_e_r=new TH2D("Reject_Energy_Ratio","Rejected",S65K,0,S65K,150,100,250); rej_e_r->Reset();
  rej_s_f=new TH2D("Reject_Slow_Fast","Rejected",S2K,0,S2K,S2K,0,S2K); rej_s_f->Reset();
  rej_s_r=new TH2D("Reject_Slow_Ratio","Rejected",S2K,0,S2K,150,100,250); rej_s_r->Reset();
  
  all_e_r=new TH2D("All_Energy_Ratio","All",S65K,0,S65K,150,100,250); all_e_r->Reset();
  all_s_f=new TH2D("All_Slow_Fast","All",S2K,0,S2K,S2K,0,S2K); all_s_f->Reset();
  all_s_r=new TH2D("All_Slow_Ratio","All",S2K,0,S2K,150,100,250); all_s_r->Reset();
  
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
  sprintf(title, "%s/d%d-d%d_chisq%d_PID.root",output_dir,det_low,det_high,chi_sq_cutoff);
  TFile f(title, "recreate");
  
  //Setting options for accepted plots
  acc_e_r->GetXaxis()->SetTitle("Energy");
  acc_e_r->GetXaxis()->CenterTitle(true);
  acc_e_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  acc_e_r->GetYaxis()->CenterTitle(true);
  acc_e_r->GetYaxis()->SetTitleOffset(1.5);
  acc_e_r->SetOption("COLZ");
  acc_e_r->Write();
  
  acc_s_f->GetXaxis()->SetTitle("A_S");
  acc_s_f->GetXaxis()->CenterTitle(true);
  acc_s_f->GetYaxis()->SetTitle("A_F");
  acc_s_f->GetYaxis()->CenterTitle(true);
  acc_s_f->GetYaxis()->SetTitleOffset(1.5);
  acc_s_f->SetOption("COLZ");
  acc_s_f->Write();
  
  acc_s_r->GetXaxis()->SetTitle("A_S");
  acc_s_r->GetXaxis()->CenterTitle(true);
  acc_s_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  acc_s_r->GetYaxis()->CenterTitle(true);
  acc_s_r->GetYaxis()->SetTitleOffset(1.5);
  acc_s_r->SetOption("COLZ");
  acc_s_r->Write();
  
  
  //Setting options for rejected plots
  rej_e_r->GetXaxis()->SetTitle("Energy");
  rej_e_r->GetXaxis()->CenterTitle(true);
  rej_e_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  rej_e_r->GetYaxis()->CenterTitle(true);
  rej_e_r->GetYaxis()->SetTitleOffset(1.5);
  rej_e_r->SetOption("COLZ");
  rej_e_r->Write();
  
  rej_s_f->GetXaxis()->SetTitle("A_S");
  rej_s_f->GetXaxis()->CenterTitle(true);
  rej_s_f->GetYaxis()->SetTitle("A_F");
  rej_s_f->GetYaxis()->CenterTitle(true);
  rej_s_f->GetYaxis()->SetTitleOffset(1.5);
  rej_s_f->SetOption("COLZ");
  rej_s_f->Write();
  
  rej_s_r->GetXaxis()->SetTitle("A_S");
  rej_s_r->GetXaxis()->CenterTitle(true);
  rej_s_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  rej_s_r->GetYaxis()->CenterTitle(true);
  rej_s_r->GetYaxis()->SetTitleOffset(1.5);
  rej_s_r->SetOption("COLZ");
  rej_s_r->Write();
  
  
  //Setting options for "all" plots
  all_e_r->GetXaxis()->SetTitle("Energy");
  all_e_r->GetXaxis()->CenterTitle(true);
  all_e_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  all_e_r->GetYaxis()->CenterTitle(true);
  all_e_r->GetYaxis()->SetTitleOffset(1.5);
  all_e_r->SetOption("COLZ");
  all_e_r->Write();
  
  all_s_f->GetXaxis()->SetTitle("A_S");
  all_s_f->GetXaxis()->CenterTitle(true);
  all_s_f->GetYaxis()->SetTitle("A_F");
  all_s_f->GetYaxis()->CenterTitle(true);
  all_s_f->GetYaxis()->SetTitleOffset(1.5);
  all_s_f->SetOption("COLZ");
  all_s_f->Write();
  
  all_s_r->GetXaxis()->SetTitle("A_S");
  all_s_r->GetXaxis()->CenterTitle(true);
  all_s_r->GetYaxis()->SetTitle("100 A_S/A_F + 100");
  all_s_r->GetYaxis()->CenterTitle(true);
  all_s_r->GetYaxis()->SetTitleOffset(1.5);
  all_s_r->SetOption("COLZ");
  all_s_r->Write();
  
  return 0;
}

























