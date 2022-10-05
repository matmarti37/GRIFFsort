#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  if((ptr->chan>=0) && (ptr->chan<=S2K))
    {
      hist[ptr->chan]++;
      h->Fill(ptr->chan);
    }

  return 0;
}


/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;
  TCanvas *c;
  TApplication *theApp;
  int ac;
  char *av[1];

  ac=0;
  av[0]=(char*) malloc(sizeof(char));
  if(argc!=2)
    {
      printf("midas_project_channelHP midas_data_file\n");
      exit(-1);
    }
  printf("Program sorts DAQ channel hit pattern.\n");

  h=new TH1D("Fold","Fold",S2K,0,S2K);
  h->Reset();
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
  
  if((output=fopen("channelHP.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);
  
  theApp=new TApplication("App", &ac, av);
  c = new TCanvas("Fold", "Fold",10,10, 700, 500);
  c->cd();
  gPad->SetLogy();
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw();
  theApp->Run(kTRUE);
}
