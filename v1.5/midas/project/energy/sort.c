#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  float v;
  int detector=det_map[ptr->chan];
  if((detector>0)&&(detector<129))
   {
    v=(float)ptr->energy/(float)divider;
    h[detector-1]->Fill(v);
    h_2D->Fill(detector,v);
   }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  //TCanvas *c;
  //TApplication *theApp;
  //int ac=0;
  //char *av[1];

  if(argc!=4)
    {
      printf("project_channel input_file map_file divider\n");
      exit(-1);
    }
  divider=atoi(argv[3]);
  
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
  //for(i=0;i<128;i++)
  // {
  //  fscanf(det_mapfile,"%d",&j);
  //  fscanf(det_mapfile,"%d",&det_map[j]);
  // }
  // End of detector map file reading
  
  for(i=0;i<128;i++)
   {
    h[i]=new TH1D("Detector","Detector",S65K,0,S65K);
    h[i]->Reset();
   }
  h_2D=new TH2D("EnergySpectrum","EnergySpectrum",130,0,130,S65K,0,S65K);
  h_2D->Reset();

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
  
  TFile f("EnergySpectra.root","recreate");
  for(i=0;i<128;i++)
   {
    if(h[i]->GetEntries())
     {
      h[i]->GetXaxis()->SetTitle("Energy");
      h[i]->GetXaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitle("Counts");
      h[i]->GetYaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitleOffset(1.5);
      h[i]->Write();
     }
   }
  if(h_2D->GetEntries())
   {
    h_2D->GetXaxis()->SetTitle("Detector");
    h_2D->GetXaxis()->CenterTitle(true);
    h_2D->GetYaxis()->SetTitle("Energy");
    h_2D->GetYaxis()->CenterTitle(true);
    h_2D->GetYaxis()->SetTitleOffset(1.5);
    h_2D->SetOption("COLZ");
    h_2D->Write();
   }
  
  //sort_but_not_assemble(argv[1]);

  //printf("Program provides a 1D projection for a selected DAQ channel.\n");

  //theApp=new TApplication("App", &ac, av);
  //c = new TCanvas(name, name,10,10, 700, 500);
  //c->cd();
  //h->GetXaxis()->SetTitle("Charge");
  //h->GetYaxis()->SetTitle("Counts");
  //h->Draw("HIST");
  //theApp->Run(kTRUE);
}
