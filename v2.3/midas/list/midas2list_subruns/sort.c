#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  store_list(limit,list,out);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  if(argc!=3)
    {
      printf("midas2list_subruns midas_subrun_list list_output_data\n");
      exit(-1);
    }

    if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
 
  sort_and_assemble_subruns(argv[1]);

  fclose(out);
}
