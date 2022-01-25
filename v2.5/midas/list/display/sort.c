#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  print_list(limit,offset,list);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  if(argc!=2)
    {
      printf("display_list midas_input_data\n");
      exit(-1);
    }
  
  sort_and_assemble(argv[1]);

  printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");

 
 
 
}
