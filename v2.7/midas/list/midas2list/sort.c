#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  store_list(limit,list,out);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  if(argc!=4)
    {
      printf("midas2list midas_input_data list_output_data map\n");
      exit(-1);
    }

    if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
 
  sort_and_assemble(argv[1],argv[3]);

  fclose(out);
}
