#include "sort.h"
int analyze_list(int limit,int offset,node* list)
{

  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* out;
  size_t son;
  node nd;
  
  son=sizeof(node);
  
  if(argc!=5)
    {
      printf("list_separate_channels input_list output_list low high\n");
      exit(-1);
    }
  
 
  printf("Program reads an ordered list of fragments created from GRIF3/GRIF4 midas file.\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
   if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }
   low=atoi(argv[3]);
   high=atoi(argv[4]);
   
 
  while(fread(&nd,son,1,inp)==1)
    if(nd.chan>=low)
      if(nd.chan<=high)
	fwrite(&nd,son,1,out);
  
 
  fclose(inp);
  fclose(out);
    
}
