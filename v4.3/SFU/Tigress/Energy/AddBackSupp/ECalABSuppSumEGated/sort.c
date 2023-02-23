#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;

  int pos1,suppFlag1,col1=0,ring1,take1;
  double eAddBack1;
  int pos2,suppFlag2,col2=0,ring2,take2;
  double eAddBack2;
  

  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);

  if(cev->tg.h.FA>1)
    for(pos1=1;pos1<NPOSTIGR;pos1++)
      {
	suppFlag1=0;
	if((cev->tg.h.HHP&(1<<(pos1-1)))!=0)
	  if(cev->tg.det[pos1].hge.FH>0)
	    if((cev->tg.h.AHP&(1<<(pos1-1)))!=0)
	      {
		take1=0;
		for(col1=0;col1<NCOL;col1++)
		  {
		    if((cev->tg.det[pos1].hge.HHP&(1<<col1))!=0)
		      if(cev->tg.det[pos1].ge[col1].h.FH>0)
			if(cev->tg.det[pos1].ge[col1].suppress>=supLow && cev->tg.det[pos1].ge[col1].suppress<=supHigh && take1==0)
			  {
			    suppFlag1=1;
			    take1=1;
			  }
		  }
		eAddBack1 = cev->tg.det[pos1].addback.E/cal_par->tg.contr_e;
		col1 = cev->tg.det[pos1].addbackC;
		ring1 = cev->tg.det[pos1].ge[col1].ring;
		
		if(eAddBack1 >= gateELow[ring1] && eAddBack1 <= gateEHigh[ring1] && suppFlag1==0)
		  {
		    gatehist[ring1][(int)eAddBack1]++;
		    for(pos2=1;pos2<NPOSTIGR;pos2++)
		      {
			suppFlag2=0;
			if((cev->tg.h.HHP&(1<<(pos2-1)))!=0)
			  if(cev->tg.det[pos2].hge.FH>0)
			    if((cev->tg.h.AHP&(1<<(pos2-1)))!=0)
			      {
				take2=0;
				for(col2=0;col2<NCOL;col2++)
				  {
				    if((cev->tg.det[pos2].hge.HHP&(1<<col2))!=0)
				      if(cev->tg.det[pos2].ge[col2].h.FH>0)
					if(cev->tg.det[pos2].ge[col2].suppress>=supLow && cev->tg.det[pos2].ge[col2].suppress<=supHigh && take2==0)
					  {
					    suppFlag2=1;
					    take2=1;
					  }
				  }
				eAddBack2 = cev->tg.det[pos2].addback.E/cal_par->tg.contr_e;
				col2 = cev->tg.det[pos2].addbackC;
				ring2 = cev->tg.det[pos2].ge[col2].ring;
				if(pos1 != pos2 || col1 != col2)
				  if(eAddBack2 >= 0 && eAddBack2 < S32K && suppFlag2==0)
				    {
				      hist[ring2][(int)eAddBack2]++;
				    }
			      }
		      }
		  }
	      }
      }
  free(cev);
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  FILE * output;
  input_names_type* name;
  FILE *cluster;
  char n[132], gateFilename[132];
  FILE *gateFile;
  char FileName[132];
  char num[32],low[32],high[32];
  int ring;

  if(argc!=5)
    {
      printf("sfu_Tigress_ECalABSuppSumEGate master_file_name supLow supHigh gateRing_file\n");
      exit(-1);
    }

  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  //memset(hist,0,sizeof(hist));
  memset(gatehist,0,sizeof(gatehist));
  memset(hist,0,sizeof(hist));
  read_master(argv[1],name);
  
  supLow=atof(argv[2]);
  supHigh=atof(argv[3]);
  strcpy(gateFilename,argv[4]);

  
  if((gateFile=fopen(gateFilename,"r"))==NULL)
    {
      printf("\nCannot open gate file\n");
      exit(-2);
    }

  printf("\n");
  while(fscanf(gateFile,"%s %s %s\n",num,low,high)!=EOF)
    {
      ring=atoi(num);
      gateELow[ring]=atoi(low);
      gateEHigh[ring]=atoi(high);
      printf("Gate for ring %d: %d to %d\n",ring,gateELow[ring],gateEHigh[ring]);
    }

  if(name->flag.cluster_file==1)
    {
      printf("\nSorting data from cluster file:\n %s\n",name->fname.cluster_file);
      if((cluster=fopen(name->fname.cluster_file,"r"))==NULL)
	{
	  printf("\nI can't open input file %s\n",name->fname.cluster_file);
	  exit(-2);
	}
    }
  else
    {
      printf("\nCluster file not defined\n");
      exit(-1);
    }

  if(name->flag.TIGRESS_cal_par==1)
    {
      printf("\nTIGRESS calibration read from the file:\n %s\n",name->fname.TIGRESS_cal_par);
      initialize_TIGRESS_calibration(&cal_par->tg,name->fname.TIGRESS_cal_par);
    }
  else
    {
      printf("\nTIGRESS calibration parameters not defined\n");
      exit(EXIT_FAILURE);
    }
  
  name->flag.inp_data=1; 
  while(fscanf(cluster,"%s",n)!=EOF)
    {
      strcpy(name->fname.inp_data,n);
      printf("Sorting data from file %s\n", name->fname.inp_data);
      sort(name);
    }

  fclose(cluster);
  
  printf("\n");

  sprintf(FileName,"ECalABSuppSum_Gate.mca");
  if((output=fopen(FileName,"w"))==NULL)
    {
      printf("CANNOT OPEN %s\n",FileName);
      exit(-1);
    }
  fwrite(gatehist,7*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Gate spectrum saved to file %s\n",FileName);

  sprintf(FileName,"ECalABSuppSum_Gated.mca");
  if((output=fopen(FileName,"w"))==NULL)
    {
      printf("CANNOT OPEN %s\n",FileName);
      exit(-1);
    }
  fwrite(hist,7*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Gated spectrum saved to file %s\n",FileName);
}

  

