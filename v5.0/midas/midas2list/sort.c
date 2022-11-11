#include "sort.h"

int analyze_list(int limit, node* list)
{

  store_list(limit,list,out);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  clock_t start,end;
  double time;
  min_TSUP = -1;
  max_TSUP = -1;

  minmax_DROPPED = 0;
  depth_DROPPED = 0;
  pileup_DROPPED = 0;
  
  if(argc!=6)
    {
      printf("midas2list midas_input_data list_output_data map min_TSUP max_TSUP\n");
      printf("This code aims to convert and clean .mid files into .list\n");
      exit(-1);
    }

  min_TSUP=atoi(argv[4]);
  max_TSUP=atoi(argv[5]);  

  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
  printf("Current parameters: min_TSUP = %d and max_TSUP = %d", min_TSUP, max_TSUP);

  start=clock();
  sort_and_assemble(argv[1],argv[3]);
  end=clock();
  time=(double)(end-start)/CLOCKS_PER_SEC;

  fclose(out);
  printf("Sorting time %8.2f seconds\n",time);

  printf("Total fragments counted: %d\n", total_FRAGMENTS);
  printf("Total fragments dropped by minmax_TSUP: %d\n", minmax_DROPPED);
  printf("Total fragments dropped by exceeding DEPTH: %d\n", depth_DROPPED);
  printf("Total fragments dropped by pileup != 1: %d\n", pileup_DROPPED);
  printf("Total fragments dropped: %d\n", (minmax_DROPPED+depth_DROPPED+pileup_DROPPED));
  printf("Percentage dropped: %f%%\n", (100*((float)(minmax_DROPPED+depth_DROPPED))/((float)(total_FRAGMENTS))));
}
