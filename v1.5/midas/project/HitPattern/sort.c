#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  if((ptr->chan>=1024) && (ptr->chan<=1380))
    {
     h_2D->Fill(x_vals[ptr->chan],y_vals[ptr->chan]);
     h_channel->Fill(ptr->chan);
     h_detector->Fill(det_map[ptr->chan]);
    }

  return 0;
}


/*================================================================*/
int main(int argc, char *argv[])
{
  //TCanvas *c;
  //TApplication *theApp;
  //int ac;
  //char *av[1];

  //ac=0;
  //av[0]=(char*) malloc(sizeof(char));
  if(argc!=4)
    {
      printf("project_channelHP midas_data_file map_ch_to_det map_ch_to_xy\n");
      exit(-1);
    }
  printf("Program sorts DAQ channel hit pattern.\n");
  

  // Creates the histogram to fill
  h_2D=new TH2D("2DHitPattern", "Hit Pattern",20,0,20,10,0,10);
  h_2D->Reset();
  
  h_channel=new TH1D("ChannelHitPattern","Hit Pattern",S2K,0,S2K);
  h_channel->Reset();
  
  h_detector=new TH1D("DetectorHitPattern","Hit Pattern",150,0,150);
  h_detector->Reset();
  
  h_mapping=new TH2D("Mapping","Mapping",20,0,20,10,0,10);
  h_mapping->Reset();
  
  
  // Reads the map file
  FILE *xy_mapfile;
  char* xy_mapfilename=argv[3];
  int i,j;
  xy_mapfile=fopen(xy_mapfilename,"r");
  if(xy_mapfile==NULL)
   {
    printf("\n Error in opening xy map file \n");
    exit(-1);
   }
  for(i=0;i<S2K;i++)
   {
    x_vals[i]=-1;
    y_vals[i]=-1;
   }
  char * xy_map_line=NULL;
  size_t len=0;
  ssize_t read;
  int num_items=0;
  while((read=getline(&xy_map_line,&len,xy_mapfile))!=-1)
   {
    num_items=sscanf(xy_map_line,"%d\t%d\t%d",&j,&x_vals[j],&y_vals[j]);
    if(num_items!=3)
     {
      printf("Fix XY map file\n");
      exit(-1);
     }
   }
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
  while((read=getline(&map_line,&len,det_mapfile))!=-1)
   {
    num_items=sscanf(map_line,"%d\t%d",&j,&det_map[j]);
    if(num_items!=2)
     {
      printf("Fix map file\n");
      exit(-1);
     }
   }
  
  for(i=0;i<S2K;i++)
   {
    for(j=0;j<det_map[i];j++)
     {
      h_mapping->Fill(x_vals[i],y_vals[i]);
     }
   }
  //exit(-1);
  
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
  //sort_but_not_assemble(argv[1]);
  
  
  // Creates the root file
  TFile f("HitPattern.root","recreate");
  if(h_2D->GetEntries())
   {
    h_2D->GetXaxis()->SetTitle("X");
    h_2D->GetXaxis()->CenterTitle(true);
    h_2D->GetYaxis()->SetTitle("Y");
    h_2D->GetYaxis()->CenterTitle(true);
    h_2D->GetYaxis()->SetTitleOffset(1.5);
    h_2D->SetOption("COLZ");
    h_2D->Write();
   }
  if(h_mapping->GetEntries())
   {
    h_mapping->GetXaxis()->SetTitle("X");
    h_mapping->GetXaxis()->CenterTitle(true);
    h_mapping->GetYaxis()->SetTitle("Y");
    h_mapping->GetYaxis()->CenterTitle(true);
    h_mapping->GetYaxis()->SetTitleOffset(1.5);
    h_mapping->SetOption("LEGO2");
    h_mapping->Write();
   }
  if(h_channel->GetEntries())
   {
    h_channel->GetXaxis()->SetTitle("Channel");
    h_channel->GetXaxis()->CenterTitle(true);
    h_channel->GetYaxis()->SetTitle("Counts");
    h_channel->GetYaxis()->CenterTitle(true);
    h_channel->GetYaxis()->SetTitleOffset(1.5);
    h_channel->Write();
   }
  if(h_detector->GetEntries())
   {
    h_detector->GetXaxis()->SetTitle("Detector");
    h_detector->GetXaxis()->CenterTitle(true);
    h_detector->GetYaxis()->SetTitle("Counts");
    h_detector->GetYaxis()->CenterTitle(true);
    h_detector->GetYaxis()->SetTitleOffset(1.5);
    h_detector->Write();
   }
  
  //theApp=new TApplication("App", &ac, av);
  //c = new TCanvas("2DHitPattern", "2D HitPattern",10,10, 700, 500);
  //c->cd();
  //h->Draw();
  //theApp->Run(kTRUE);
}
