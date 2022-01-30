#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  print_list(limit,offset,list);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  if(argc!=3)
    {
      printf("display_list_subruns midas_subrun_list map\n");
      exit(-1);
    }
  
   printf("Program generates an ordered list of fragments in GRIF3/GRIF4 format from a midas file.\n");
   sort_and_assemble_subruns(argv[1],argv[2]);
 
}
