#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  print_list(limit,offset,list);
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  int i;
  size_t son;
  node nd;
  
  son=sizeof(node);
  
  if(argc!=2)
    {
      printf("list_read list_input_data\n");
      exit(-1);
    }
  
 
  printf("Program reads an ordered list of fragments created from GRIF3/GRIF4 midas file.\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
 
  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd);
      i++;
    };
  
 

    fclose(inp);
}
