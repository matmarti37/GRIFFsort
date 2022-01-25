#include "map.h"
/*======================================================================*/
void print_map(gmap* map)
{
  printf("================    ==========================================\n");
  printf("GRIFDAQMAP          %s\n",map->title);
  printf("================    ==========================================\n");
  printf("CORSE_TIME_GATE     %d\n",map->div);
  printf("================    ==========================================\n");
}
/*======================================================================*/
void read_map(char* name,gmap* map)
{
  FILE *inp;
  char str1[132],str2[132];
  float div;
  
  if((inp=fopen(name,"r"))==NULL)
      {
         printf("\nFile %s can not be opened\n",name);
         exit(EXIT_FAILURE);
      }
  else
    printf("GDAQ map read from file %s\n",name);

  //initialize map to -1 to avoid mis-labeling channels
  memset(map,-1,sizeof(gmap));

  while(fscanf(inp,"%s %s",str1,str2)!=EOF)
    {
      if(strcmp(str1,"GRIFDAQMAP")==0)
	strncpy(map->title,str2,256);

      if(strcmp(str1,"CORSE_TIME_GATE")==0)
	{
	  div=atof(str2);
	  if(ceil(log2(div)) != floor(log2(div)))
	    {
	      printf("Corse time gate is not a power of 2\n");
	      printf("Corse timing is not done on a bit-shifted time stamp\n");
	    }
	   
	  map->div=atoi(str2);
	}
      
    }
  fclose(inp);
  print_map(map);
}
