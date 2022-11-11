#include "sort.h"
int analyze_list(int limit,int offset,node* nd, gmap* map)
{

  int chan;
  
  if(nd->wfit.type>0)
    if((chan=map->csi_lt[nd->chan-map->csiarray_min])>0)
      if(chan<NCSI)
	hist[chan][(int)nd->wfit.t[0]]++;
	
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* inp;
  FILE* out;
  int i;
  static gmap map;
  size_t son;
  node nd;
  
  son=sizeof(node);
  memset(&hist,0,sizeof(hist));
  if(argc!=3)
    {
      printf("list_TIP_t0 list_input_data map\n");
      exit(-1);
    }
  
 
  printf("Program sorts time difference histogram between consecutive fragments on the list\n");

  if((inp=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open %s for reading!\n",argv[1]);
      exit(-2);
    }

  /* get the map */
  read_map(argv[2],&map);


  i=0;
  while(fread(&nd,son,1,inp)==1)
    {     
      analyze_list(1,i,&nd,&map);
      i++;
    };

  fclose(inp);
  
 if((out=fopen("list_TIP_t0.spn","w"))==NULL)
   {
    printf("ERROR\n");
    exit(EXIT_FAILURE);
   }
  fwrite(hist,sizeof(hist),1,out);
  fclose(out);
  
}
