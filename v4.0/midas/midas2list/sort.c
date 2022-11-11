#include "sort.h"

int analyze_list(int limit,int offset,node* list)
{

  store_list(limit,list,out);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  clock_t start,end;
  double time;
  prev_TSUP = 0;
  min_TSUP = -1;
  max_TSUP = -1;
  buffer_TSUP = 2147483647;

  buffer_DROPPED = 0;
  minmax_DROPPED = 0;
  prev_DROPPED = 0;
  pileup_DROPPED = 0;
  
  if(argc!=6&&argc!=7)
    {
      printf("midas2list midas_input_data list_output_data map min_TSUP max_TSUP\n");
      printf("OR\n");
      printf("midas2list midas_input_data list_output_data map min_TSUP max_TSUP buffer_TSUP\n");
      printf("This code aims to convert and clean .mid files into .list");
      exit(-1);
    }

  min_TSUP=atoi(argv[4]);
  max_TSUP=atoi(argv[5]);
  
  if(argc==7)
    buffer_TSUP=atoi(argv[6]);  

  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
  printf("Current parameters: min_TSUP = %d, max_TSUP = %d, and buffer_TSUP = %d\n", min_TSUP, max_TSUP, buffer_TSUP);

  start=clock();
  sort_and_assemble(argv[1],argv[3]);
  end=clock();
  time=(double)(end-start)/CLOCKS_PER_SEC;

  fclose(out);
  printf("Sorting time %8.2f seconds\n",time);

  printf("Total fragments counted: %d\n", total_FRAGMENTS);
  //printf("Total fragments dropped by buffer_TSUP: %d\n", buffer_DROPPED);
  printf("Total fragments dropped by minmax_TSUP: %d\n", minmax_DROPPED);
  //printf("Total fragments dropped by prev_TSUP: %d\n", prev_DROPPED);
  printf("Total fragments dropped by pileup != 1: %d\n", pileup_DROPPED);
  printf("Total fragments dropped: %d\n", (buffer_DROPPED+minmax_DROPPED+prev_DROPPED+pileup_DROPPED));
  printf("Percentage dropped: %f%%\n", (100*((float)(buffer_DROPPED+minmax_DROPPED+prev_DROPPED))/((float)(total_FRAGMENTS))));
}
