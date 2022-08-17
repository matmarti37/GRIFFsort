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
  max_TSUP = -1;
  if(argc!=4&&argc!=5)
    {
      printf("midas2list midas_input_data list_output_data map\n");
      printf("OR\n");
      printf("midas2list midas_input_data list_output_data map max_TSUP\n");
      printf("This code aims to convert and clean .mid files into .list");
      exit(-1);
    }

  if(argc==5)
    max_TSUP=atoi(argv[4]);  

  if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");

  start=clock();
  sort_and_assemble(argv[1],argv[3]);
  end=clock();
  time=(double)(end-start)/CLOCKS_PER_SEC;

  printf("Sorting time %8.2f seconds\n",time);
  fclose(out);
}
