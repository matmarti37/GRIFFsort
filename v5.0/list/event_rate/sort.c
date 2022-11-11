#include "sort.h"
#include <stdio.h>
int analyze_list(int limit,int offset,node* list)
{
   int j;

   for(j=0;j<limit;j++)
     {
       if(list[j].tsns/binSize >= S32K)
	 {
	   printf("Probably going to seg fault! Use a bigger bin size!\n");
	   printf("Histogram bin accessed: %d > %d\n", list[j].tsns/binSize, S32K);
	   exit(-1);	   
	 }
       
       histogram[list[j].tsns/binSize]++;
     }  
  
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* output;
  int i;
  size_t son;
  node nd;
  
  son=sizeof(node);

  if(argc!=3)
    {
      printf("list_event_rate list_input_data bin_size\n");
      exit(-1);
    }

  binSize = atoi(argv[2]);
  memset(histogram,0,sizeof(histogram));
 
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
  
  if((output=fopen("list_event_rate.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(histogram,sizeof(histogram),1,output);
  fclose(output);
 
  
 

    fclose(inp);
}
