#include "sort.h"
#include <stdio.h>
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
      printf("list_read list_input_data [number]\n");
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
  while(fread(&nd,son,1,inp)==1)
    {
      if(i<94858)
	{
	  i++;
	  continue;
	}
      analyze_list(1,i,&nd);
      if(i==94867)
	exit(-1);
      if(nd.chan>1000 && nd.trig>0) tip_count++;
      i++;
      /* if(i==58600) */
      /* 	{ */
      /* 	  fclose(inp); */
      /* 	  exit(-1); */
      /* 	} */
    };
  printf("Number of TIP channels with TRIGGER:  %d\n",tip_count);
  
 

    fclose(inp);
}
