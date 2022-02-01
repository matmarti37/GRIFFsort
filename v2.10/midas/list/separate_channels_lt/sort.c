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
  FILE* map;
  size_t son;
  node nd;
  char line[256],str[32];
  
  son=sizeof(node);

  memset(&lt,0,sizeof(lt));
  
  if(argc!=4)
    {
      printf("list_separate_channels_lt input_list output_list lookup_table\n");
      exit(-1);
    }
  
 
  printf("Program separates a list of HPGe channels from the list of fragments created from GRIF3/GRIF4 midas file.\n");

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
   
    if((map=fopen(argv[3],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[3]);
      exit(-2);
    }

    while(fgets(line, sizeof(line), map))
      {
	sscanf(line,"%s",str);
	lt[atoi(str)]=1;
      }
    fclose(map);
    
    while(fread(&nd,son,1,inp)==1)
      if(lt[nd.chan]==1)
	fwrite(&nd,son,1,out);
  
 
  fclose(inp);
  fclose(out);

    
}
