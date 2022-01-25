#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  float v;
  if(ptr->chan==channel)
      {
	v=(float)ptr->energy/(float)divider;
	h->Fill(v);
      }
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  TCanvas *c;
  TApplication *theApp;
  int ac=0;
  char *av[1];
  char name[132];

  if(argc!=4)
    {
      printf("project_channel input_file channel divider\n");
      exit(-1);
    }
  channel=atoi(argv[2]);
  divider=atoi(argv[3]);
 
  h=new TH1D("","",S65K,0,S65K);
  sprintf(name,"ch. %s",argv[2]);
  h->Reset();
  h->SetName(name);
  h->SetTitle(name);

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

  printf("Program provides a 1D projection for a selected DAQ channel.\n");

  theApp=new TApplication("App", &ac, av);
  c = new TCanvas(name, name,10,10, 700, 500);
  c->cd();
  h->GetXaxis()->SetTitle("Charge");
  h->GetYaxis()->SetTitle("Counts");
  h->Draw("HIST");
  theApp->Run(kTRUE);
}
