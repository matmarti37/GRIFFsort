#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{

  
  if(ptr->chan==target_channel)
    {
      hist[ptr->pileup]++;
      events++;
    }
    //if(ptr->chan>=map->tig_min)
    //if(ptr->chan<=map->tig_max)
    //	if(map->hpge_lt[ptr->chan-map->tig_min].seg==0)//channel is the central contact
    //	  if(map->hpge_lt[ptr->chan-map->tig_min].pos>0)//channel present on the CC list
    //	    if(map->hpge_lt[ptr->chan-map->tig_min].pos<NPOSTIGR)//channel present on the CC list 
  //	      hist[ptr->pileup]++;


  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;
  FILE* inp;
  //TCanvas *c;
  //TApplication *theApp;
  //int ac,i;
  //node nd;
  //char *av[1];
  //size_t son;
  //static gmap map;

  //ac=0;
  //av[0]=(char*) malloc(sizeof(char));
  if(argc!=3)
    {
      printf("midas_project_channel_pileup midas_data_file channel\n");
      exit(-1);
    }
  target_channel = atoi(argv[2]);
  events = 0;
  //  printf("Program sorts DAQ channel hit pattern for a specific range of timestamp ups.\n");
  //  printf("Range was input as: %d <= tsup <= %d\n", min_TSUP, max_TSUP);

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  memset(&hist,0,sizeof(hist));
  //read_map(argv[2],&map);

  sort_but_not_assemble(argv[1]);
  
  /* i=0; */
  /* while(fread(&nd,son,1,inp)==1) */
  /*   {      */
  /*     analyze_list(1,i,&nd,&map); */
  /*     i++; */
  /*   }; */
  printf("%d events counted.",events);
  
  if((output=fopen("channel_pileup.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the spn file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,sizeof(hist),1,output);
  fclose(output);

}
