#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE** subrun;
  int    n;
  FILE* subrun_list;
  char name[132];
  FILE* input;
  int i,k;
  unsigned long long tsns;
  node* nodes;
  size_t son;
  node  store;
  
  if(argc!=3)
    {
      printf("list_combine list_of_subrun_lists output_list_name\n");
      exit(-1);
    }

  printf("Program combines a list of fragments from lists sorted from GRIF3/GRIF4 midas files.\n");
  
  /* open the list of subrun midas files */
  if((subrun_list=fopen(argv[1],"r"))==NULL)
    {
      printf("ERROR!!! I can't open the subrun midas file list %s\n",argv[1]);
      exit(-2);
    }
  son=sizeof(node);
  n=0;
  subrun=NULL;
  /* process input file list*/
  while(fscanf(subrun_list,"%s",name)!=EOF)
    if(( input=fopen(name,"r"))==NULL)
      {
	printf("\nI can't open input file %s\n",name);
	exit(-2);	  
      }
    else
      {
	
	if(n==0)
	  subrun=(FILE**)malloc(sizeof(FILE*));
	else	  
	  subrun=(FILE**)realloc((FILE**)subrun,(n+1)*sizeof(FILE*));
	
	subrun[n]=input;
	n++;
	printf("File %3d named %s opened for processing\n",n,name);	  

	
      }
  
  fclose(subrun_list);
  
    if((out=fopen(argv[2],"w"))==NULL)
    {
      printf("ERROR!!! I can't open %s for writing!\n",argv[2]);
      exit(-2);
    }

    nodes=(node*)malloc(n*son);

    //read the first event from each subrun file
    for(i=0;i<n;i++)
      if(feof(subrun[i])==0)
	{
	  if(fread(&store,son,1,subrun[i])==1)
	      memcpy(&nodes[i],&store,son);
	  else
	    nodes[i].tsns=-1;
	}

 
    while(1)
      {
	tsns=LLONG_MAX;//set to the number beyond the clock range
	k=-1;
	//find the file with the minimum tsns

	for(i=0;i<n;i++)
	  if(nodes[i].tsns>=0)
	    if(nodes[i].tsns<tsns)
	      {
		tsns=nodes[i].tsns;
		k=i;
	      }
	if(k==-1) break;

	if(fwrite(&nodes[k],son,1,out)!=1)
	  {
	    printf("Error in writing to the output file, exiting\n");
	    fclose(out);
	    exit(0);
	  }

	nodes[k].tsns=-1;
	if(!feof(subrun[k]))
	  if(fread(&store,son,1,subrun[k])==1)
	    memcpy(&nodes[k],&store,son);
      }
    
    for(i=0;i<n;i++)
      fclose(subrun[i]);
      
    fclose(out);
   

}
