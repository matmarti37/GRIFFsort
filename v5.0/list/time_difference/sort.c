#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{
  long long diff;

  if(offset==0)
    {
      tsstore=list->tsns;
      return 0;
    }
  
  diff=list->tsns-tsstore;


  if(diff<0)
    {
      printf("current %16lld stored %16lld\n",list->tsns,tsstore);
      printf("list disordered, diff is %16lld\n",diff);
      printf("Exiting\n");
      exit(0);
    }
  h->Fill(diff);
  
  tsstore=list->tsns;
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  int i;
  size_t son;
  node nd;
  int ac;
  char* av[1];

  ac=0;
  av[0]=0;
  son=sizeof(node);
  
  if(argc!=2)
    {
      printf("list_time_difference list_input_data\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  theApp=new TApplication("App", &ac, av);
  if(h!=NULL) delete h;
  h=new TH1D("TSdiff","TSdiff",65536,0,65536);
  if(c!=NULL) delete c;
  c = new TCanvas("TS", "TS",10,10, 700, 500);

  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd);
      i++;
    };

  fclose(inp);
  
  h->Draw("HIST");
  theApp->Run(kTRUE);

  
}
