#include "sort.h"
/*================================================================*/
int analyze_fragment(Grif_event* ptr,short* waveform)
{
 Int_t d;
 WaveFormPar wpar;
 double amplitude, red_chisq, charge;
 int detector,type,amp_int;
 
 detector=det_map[ptr->chan];
 
 if(detector>0 && detector<129)
  {
   if((d=ptr->waveform_length)!=0)
    {
     fit_CsI_waveform(d,waveform,par,&wpar);
     red_chisq=par->chisq/par->ndf;
     type=par->type;
     //if(red_chisq<=chi_sq_cutoff && type==1)
     if(red_chisq<=chi_sq_cutoff && type==1)
      {
       amplitude=par->am[2]+par->am[3]; //Amplitude = Fast amplitude + Slow amplitude
       charge=(double)ptr->energy/125.;
       h[detector]->Fill(amplitude);
       h2[detector]->Fill(amplitude,charge);
       hcsi->Fill(amplitude);
       
       amp_int=(int)(amplitude);
       hist[detector][amp_int]++;
      }
    }
  }
 return 0;
}
 
/*================================================================*/
int main(int argc, char *argv[])
{
  char HistName1[132];
  char HistName2[132];
  char title[132];

  if(argc!=8)
    {
      printf("wfit_amplitude midas_input_data map_file chi_sq_cutoff tRC tF tS tGamma\n");
      exit(-1);
    }
    
  par=(ShapePar*)malloc(sizeof(ShapePar));
  memset(par,0,sizeof(ShapePar));
  
  par->t[1]=atof(argv[4]); //set tRC
  par->t[2]=atof(argv[5]); //set tF
  par->t[3]=atof(argv[6]); //set tS
  par->t[4]=atof(argv[7]); //set tGamma

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
  printf("Read Map File\n");
  chi_sq_cutoff=atoi(argv[3]);
  printf("Read chi sq cutoff\n");
  for(int i=1;i<129;i++)
    {
      sprintf(HistName1,"amplitude_%04d",i);
      h[i]=new TH1D(HistName1,HistName1,512,0,S4K);
      h[i]->Reset();
      
      sprintf(HistName2,"amplitude_v_energy_%04d",i);
      h2[i]=new TH2D(HistName2,HistName2,512,0,S4K,S16K,0,S16K);
      h2[i]->Reset();
    }

  hcsi=new TH1D("CsI Sum","CsI Sum",512,0,S4K);
  hcsi->Reset();
  
  printf("Created histograms\n");
  
  FILE* output;
  memset(&hist,0,sizeof(hist));
  
  
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
  char line[512];
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

  sprintf(title,"amplitude.root");
  TFile f(title, "recreate");
  
  for(int i=1;i<129;i++)
    {
      /* only write if hitogram is not empty */
      if(h[i]->GetEntries())
	{
	  sprintf(HistName1, "amplitude_%04d",i);
	  h[i]->GetXaxis()->SetTitle("amplitude");
	  h[i]->GetXaxis()->CenterTitle(true);
	  h[i]->GetYaxis()->SetTitle("counts");
	  h[i]->GetYaxis()->CenterTitle(true);
	  h[i]->GetYaxis()->SetTitleOffset(1.5);
	  h[i]->Write();
	}
    }
    
  for(int i=1;i<129;i++)
    {
      /* only write if hitogram is not empty */
      if(h2[i]->GetEntries())
	{
	  sprintf(HistName2, "amplitude_v_energy_%04d",i);
	  h2[i]->GetXaxis()->SetTitle("Amplitude");
	  h2[i]->GetXaxis()->CenterTitle(true);
	  h2[i]->GetYaxis()->SetTitle("Energy");
	  h2[i]->GetYaxis()->CenterTitle(true);
	  h2[i]->GetYaxis()->SetTitleOffset(1.5);
	  h2[i]->SetOption("COLZ");
	  h2[i]->Write();
	}
    }


  if(hcsi->GetEntries())
    {
      hcsi->GetXaxis()->SetTitle("amplitude");
      hcsi->GetXaxis()->CenterTitle(true);
      hcsi->GetYaxis()->SetTitle("counts");
      hcsi->GetYaxis()->CenterTitle(true);
      hcsi->GetYaxis()->SetTitleOffset(1.5);
      hcsi->Write();  
    }
  
  if((output=fopen("spectra.spn","w"))==NULL)
   {
    printf("ERROR\n");
    exit(EXIT_FAILURE);
   }
  fwrite(hist,sizeof(hist[0]),256,output);
  fclose(output);
  return 0;
}
