#include "sort.h"
#include <stdio.h>
int analyze_list(int limit,int offset,node* list)
{ 
  int i;

  for(i=0;i<limit;i++)
    if((unsigned int)list[i].ch.timestamp_up==0)
      histogram_tsup0[list[i].chan]++;
    else
      histogram[list[i].chan]++; 
  
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

  if(argc!=2)
    {
      printf("list_channelHP_tsup list_input_data [number]\n");
      exit(-1);
    }
  
  
  printf("Program reads an ordered list of fragments created from GRIF3/GRIF4 midas file.\n");
  
  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }
  
  i=0;
  int tip_count=0;
  memset(histogram,0,sizeof(histogram));
  memset(histogram_tsup0,0,sizeof(histogram_tsup0));
  
  while(fread(&nd,son,1,inp)==1)
      {     
      analyze_list(1,i,&nd);
      if(nd.chan>1000 && nd.trig>0) tip_count++;
      i++;
    };
    printf("Number of TIP channels with TRIGGER:  %d\n",tip_count); 
    

  if((output=fopen("list_hitpattern.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(histogram,sizeof(histogram),1,output);
  fclose(output);

  if((output=fopen("list_hitpattern_tsup0.spn","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(histogram_tsup0,sizeof(histogram_tsup0),1,output);
  fclose(output);
 

    fclose(inp);
}
