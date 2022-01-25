#include "map.h"
/*======================================================================*/
void print_map(gmap* map)
{
  printf("================    ==========================================\n");
  printf("GRIFDAQMAP          %s\n",map->title);
  printf("================    ==========================================\n");
  printf("TIGRESS             PARAMETER\n");
  printf("CC_MIN              %4d\n",map->tcc_min);
  printf("CC_MAX              %4d\n",map->tcc_max);
  printf("CC_MAP              %s\n",map->tccmap);
  printf("================    ==========================================\n");
  printf("CSIARRAY            PARAMETER\n");
  printf("MIN                 %4d\n",map->csiarray_min);
  printf("MAX                 %4d\n",map->csiarray_max);
  printf("MAP                 %4s\n",map->csimap);
  if(map->csiarray_fit==1)
    printf("FIT                 YES\n");
  else
    printf("FIT                 NO\n");
  printf("TRC                 %8.3f\n",map->csiarray_trc);
  printf("TF                  %8.3f\n",map->csiarray_tf);
  printf("TS                  %8.3f\n",map->csiarray_ts);
  printf("TR                  %8.3f\n",map->csiarray_tr);
  printf("================    ==========================================\n");

  print_tccpos(map);
  print_csipos(map);
}
/*======================================================================*/
void print_csipos(gmap* map)
{
  int i;

  printf("CSIARRAY            PARAMETER\n");
  printf("CHANNEL             POSITION\n");
  for(i=0;i<CSIPOSLT;i++)
    if(map->csipos[i]>0)
      if(map->csipos[i]<NCSI)
	printf("%5d             %5d\n",i+map->csiarray_min,map->csipos[i]);
  printf("================    ==========================================\n");
}
/*======================================================================*/
void print_tccpos(gmap* map)
{
  int i;
  const char *col[]={"B","G","R","W"};
  
 
  printf("TIGRESS_CC          PARAMETER\n");
  printf("CHANNEL             POSITION_COLOR\n");
  for(i=0;i<TCCPOSLT;i++)
    if(map->tccpos[i]>0)
      if(map->tccpos[i]<NPOSTIGR)
	printf("%5d             %5d %8s\n",i+map->tcc_min,map->tccpos[i],col[map->tcccol[i]]);
   printf("================    ==========================================\n");
}
/*======================================================================*/
void read_map(char* name,gmap* map)
{
  FILE *inp;
  FILE *csi_inp;
  FILE *tcc_inp;
  int ch,pos;
  char str1[132],str2[132],seg[8];
  
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

      if(strcmp(str1,"TIGRESS")==0)
	if(strcmp(str2,"PARAMETER")==0)
	  while(1)
	    {	      
	      if(fscanf(inp,"%s %s",str1,str2)==EOF) break;
	      if(strstr(str1,"=")!=NULL) break;

	      if(strcmp(str1,"CC_MIN")==0)
		  map->tcc_min=atoi(str2);
	      
		if(strcmp(str1,"CC_MAX")==0)
		  map->tcc_max=atof(str2);

		if(strcmp(str1,"CC_MAP")==0)
		  {
		    if((map->tcc_max-map->tcc_min)>TCCPOSLT)
		      {
			printf("TIGRESS core position lookup table not long enough.\n");
			printf("Recompile the map with larger TCCPOSLT parameter.\n");
			printf("Terminating.\n");
			exit(EXIT_FAILURE);
		      }
		    strcpy(map->tccmap,str2);

		    if((tcc_inp=fopen(map->tccmap,"r"))==NULL)
		      {
			printf("\nFile %s can not be opened\n",name);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("TIGRESS channel to position map read from file %s\n",name);

		    while(fscanf(tcc_inp,"%d %d %s",&ch,&pos,seg)!=EOF)
		      {
			ch-=map->tcc_min;
			if(ch>=0)
			  if(ch<TCCPOSLT)
			    if(pos>0)
			      if(pos<NPOSTIGR)
				{
				  map->tccpos[ch]=pos;
				  if(strcmp(seg,"B")==0) map->tcccol[ch]=0;
				  if(strcmp(seg,"G")==0) map->tcccol[ch]=1;
				  if(strcmp(seg,"R")==0) map->tcccol[ch]=2;
				  if(strcmp(seg,"W")==0) map->tcccol[ch]=3;		  
				}
		      }
		    fclose(tcc_inp);		    
		  }
	      
	    }
	      
      if(strcmp(str1,"CSIARRAY")==0)
	if(strcmp(str2,"PARAMETER")==0)
	  while(1)
	    {
	      if(fscanf(inp,"%s %s",str1,str2)==EOF) break;
	      if(strstr(str1,"=")!=NULL) break;
	      
	      if(strcmp(str1,"MIN")==0)
		  map->csiarray_min=atoi(str2);
	      
		if(strcmp(str1,"MAX")==0)
		  map->csiarray_max=atof(str2);

		if(strcmp(str1,"MAP")==0)
		  {
		    if((map->csiarray_max-map->csiarray_min)>CSIPOSLT)
		      {
			printf("CsI position lookup table not long enough.\n");
			printf("Recompile the map with larger CSIPOSLT parameter.\n");
			printf("Terminating.\n");
			exit(EXIT_FAILURE);
		      }
		    strcpy(map->csimap,str2);

		    if((csi_inp=fopen(map->csimap,"r"))==NULL)
		      {
			printf("\nFile %s can not be opened\n",name);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("CsI channel to position map read from file %s\n",name);

		    while(fscanf(csi_inp,"%d %d",&ch,&pos)!=EOF)
		      {
			ch-=map->csiarray_min;
			if(ch>=0)
			  if(ch<CSIPOSLT)
			    if(pos>0)
			      if(pos<NCSI)
				map->csipos[ch]=pos;
		      }
		    fclose(csi_inp);
		  }

		if(strcmp(str1,"FIT")==0)
		  if(strcmp(str2,"YES")==0)
		    map->csiarray_fit=1;

		if(strcmp(str1,"TRC")==0)
		  map->csiarray_trc=atof(str2);

		if(strcmp(str1,"TF")==0)
		  map->csiarray_tf=atof(str2);

		if(strcmp(str1,"TS")==0)
		  map->csiarray_ts=atof(str2);

		if(strcmp(str1,"TR")==0)
		  map->csiarray_tr=atof(str2);

		if(strcmp(str1,"PRETRIG")==0)
		  map->csiarray_pretrig=atof(str2);
	    }
      
    }
  fclose(inp);
  print_map(map);
}
