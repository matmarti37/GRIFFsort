#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,prev;
  
  son=sizeof(node);
  memset(&prev,0,son);
  
  if(argc!=2)
    {
      printf("list_HPGe_Trigger_tsns fragment_list\n");
      exit(-1);
    }
  

  printf("Program assigns global trigger as TIG trigger.\n");


  if((fl=fopen(argv[1],"r+"))==NULL)
    {
      printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
      exit(-2);
    }

  while(1)
    {
      if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
      if(curr.tig_trig>0) //look for tigress events with triggers
	{
	  curr.trig=curr.tig_trig;
	  fseek(fl,-son,SEEK_CUR);
	  fwrite(&curr,son,1,fl);
	}
    }

  fclose(fl);
  

    
}
