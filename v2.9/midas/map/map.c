#include "map.h"
/*======================================================================*/
void print_map(gmap* map)
{
  printf("================    ==========================================\n");
  printf("GRIFDAQMAP          %s\n",map->title);
  printf("================    ==========================================\n");
  printf("TIGRESS             PARAMETER\n");
  printf("TIG_MIN             %4d\n",map->tig_min);
  printf("TIG_MAX             %4d\n",map->tig_max);
  printf("CC_MAP              %s\n",map->tccmap);
  printf("SEG_MAP             %s\n",map->tsegmap);
  printf("SUP_MAP             %s\n",map->tsupmap); 
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

  print_tccmap(map);
  print_tsegmap(map);
  print_tsupmap(map);
  print_csimap(map);
}
/*======================================================================*/
void print_csimap(gmap* map)
{
  int i;

  printf("CSIARRAY            PARAMETER\n");
  printf("CHANNEL             POSITION\n");
  for(i=0;i<CSIPOSLT;i++)
    if(map->csi_lt[i]>0)
      if(map->csi_lt[i]<NCSI)
	printf("%5d             %5d\n",i+map->csiarray_min,map->csi_lt[i]);
  printf("================    ==========================================\n");
}
/*======================================================================*/
void print_tccmap(gmap* map)
{
  int i;
  const char *col[]={"B","G","R","W"};
  
 
  printf("TIGRESS_CC          PARAMETER\n");
  printf("CHANNEL             POSITION_COLOR\n");
  for(i=0;i<TIGPOSLT;i++)
    if(map->hpge_lt[i].pos>0)
      if(map->hpge_lt[i].pos<NPOSTIGR)
	if(map->hpge_lt[i].seg==0)
	printf("%5d             %5d %8s\n",i+map->tig_min,map->hpge_lt[i].pos,col[map->hpge_lt[i].col]);
   printf("================    ==========================================\n");
}
/*======================================================================*/
void print_tsegmap(gmap* map)
{
  int i;
  const char *col[]={"B","G","R","W"};
  
 
  printf("TIGRESS_SEG         PARAMETER\n");
  printf("CHANNEL             POSITION_COLOR_SEGMENT\n");
  for(i=0;i<TIGPOSLT;i++)
    if(map->hpge_lt[i].pos>0)
      if(map->hpge_lt[i].pos<NPOSTIGR)
	if(map->hpge_lt[i].seg>0)
	  if(map->hpge_lt[i].seg<NSEGTIGR)	  
	    printf("%5d             %5d %8s %8d\n",i+map->tig_min,map->hpge_lt[i].pos,col[map->hpge_lt[i].col],map->hpge_lt[i].seg);
   printf("================    ==========================================\n");
}
/*======================================================================*/
void print_tsupmap(gmap* map)
{
  int i;
  const char *col[]={"B","G","R","W"};
  
 
  printf("TIGRESS_SUP         PARAMETER\n");
  printf("CHANNEL             POSITION_COLOR_SEGMENT\n");
  for(i=0;i<TIGPOSLT;i++)
    if(map->supp_lt[i].pos>0)
      if(map->supp_lt[i].pos<NPOSTIGR)
	if(map->supp_lt[i].seg>0)
	  if(map->supp_lt[i].seg<NSUP)	  
	    printf("%5d             %5d %8s %8d\n",i+map->tig_min,map->supp_lt[i].pos,col[map->supp_lt[i].col],map->supp_lt[i].seg);
   printf("================    ==========================================\n");
}
/*======================================================================*/
void read_map(char* name,gmap* map)
{
  FILE *inp;
  FILE *csi_inp;
  FILE *tcc_inp;
  FILE *tseg_inp;
  FILE *tsup_inp;
  int ch,pos,seg;
  char str1[132],str2[132],col[8];
  
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

	      if(strcmp(str1,"TIG_MIN")==0)
		  map->tig_min=atoi(str2);
	      
		if(strcmp(str1,"TIG_MAX")==0)
		  map->tig_max=atof(str2);

		if((map->tig_max-map->tig_min)>TIGPOSLT)
		  {
		    printf("TIGRESS position lookup table not long enough.\n");
		    printf("Recompile the map with larger TIGPOSLT parameter.\n");
		    printf("Terminating.\n");
		    exit(EXIT_FAILURE);
		  }

		if(strcmp(str1,"CC_MAP")==0)
		  {		 
		    strcpy(map->tccmap,str2);

		    if((tcc_inp=fopen(map->tccmap,"r"))==NULL)
		      {
			printf("\nFile %s can not be opened\n",map->tccmap);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("TIGRESS channel to CC position map read from file %s\n",map->tccmap);

		    while(fscanf(tcc_inp,"%d %d %s",&ch,&pos,col)!=EOF)
		      {
			ch-=map->tig_min;
			if(ch>=0)
			  if(ch<TIGPOSLT)
			    if(pos>0)
			      if(pos<NPOSTIGR)
				{
				  map->hpge_lt[ch].pos=pos;
				  map->hpge_lt[ch].seg=0;
				  if(strcmp(col,"B")==0) map->hpge_lt[ch].col=0;
				  if(strcmp(col,"G")==0) map->hpge_lt[ch].col=1;
				  if(strcmp(col,"R")==0) map->hpge_lt[ch].col=2;
				  if(strcmp(col,"W")==0) map->hpge_lt[ch].col=3;		  
				}
		      }
		    fclose(tcc_inp);		    
		  }

		if(strcmp(str1,"SEG_MAP")==0)
		  {
		    strcpy(map->tsegmap,str2);

		    if((tseg_inp=fopen(map->tsegmap,"r"))==NULL)
		      {
			printf("\nFile %s can not be opened\n",map->tsegmap);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("TIGRESS channel to SEG position map read from file %s\n",map->tsegmap);

		    while(fscanf(tseg_inp,"%d %d %s %d",&ch,&pos,col,&seg)!=EOF)
		      {
			ch-=map->tig_min;
			if(ch>=0)
			  if(ch<TIGPOSLT)
			    if(pos>0)
			      if(pos<NPOSTIGR)
				if(seg>0)
				  if(seg<NSEGTIGR)				
				    {
				      map->hpge_lt[ch].pos=pos;
				      map->hpge_lt[ch].seg=seg;
				      if(strcmp(col,"B")==0) map->hpge_lt[ch].col=0;
				      if(strcmp(col,"G")==0) map->hpge_lt[ch].col=1;
				      if(strcmp(col,"R")==0) map->hpge_lt[ch].col=2;
				      if(strcmp(col,"W")==0) map->hpge_lt[ch].col=3;		  
				    }
		      }
		    fclose(tseg_inp);		    
		  }

		if(strcmp(str1,"SUP_MAP")==0)
		  {
		    strcpy(map->tsupmap,str2);

		    if((tsup_inp=fopen(map->tsupmap,"r"))==NULL)
		      {
			printf("\nFile %s can not be opened\n",map->tsupmap);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("TIGRESS channel to SUP position map read from file %s\n",map->tsupmap);

		    while(fscanf(tsup_inp,"%d %d %s %d",&ch,&pos,col,&seg)!=EOF)
		      {
			ch-=map->tig_min;
			if(ch>=0)
			  if(ch<TIGPOSLT)
			    if(pos>0)
			      if(pos<NPOSTIGR)
				if(seg>0)
				  if(seg<NSUP)				
				    {
				      map->supp_lt[ch].pos=pos;
				      map->supp_lt[ch].seg=seg;
				      if(strcmp(col,"B")==0) map->supp_lt[ch].col=0;
				      if(strcmp(col,"G")==0) map->supp_lt[ch].col=1;
				      if(strcmp(col,"R")==0) map->supp_lt[ch].col=2;
				      if(strcmp(col,"W")==0) map->supp_lt[ch].col=3;		  
				    }
		      }
		    fclose(tsup_inp);		    
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
			printf("\nFile %s can not be opened\n",map->csimap);
			exit(EXIT_FAILURE);
		      }
		    else
		      printf("CsI channel to position map read from file %s\n",map->csimap);

		    while(fscanf(csi_inp,"%d %d",&ch,&pos)!=EOF)
		      {
			ch-=map->csiarray_min;
			if(ch>=0)
			  if(ch<CSIPOSLT)
			    if(pos>0)
			      if(pos<NCSI)
				map->csi_lt[ch]=pos;
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
