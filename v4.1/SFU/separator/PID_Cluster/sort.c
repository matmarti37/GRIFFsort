#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  uint64_t one=1;
  int pos;
  double e,r;
  int content=0;
  //int ring;

  if((data->h.setupHP&CsIArray_BIT)==0)
    return SEPARATOR_DISCARD;

  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  if(cev->csiarray.h.FE>0)
    for(pos=1;pos<NCSI;pos++)
      if((cev->csiarray.h.EHP[pos/64]&(one<<pos%64))!=0)
	{
	  if(data->csiarray.wfit[pos].type!=1)
	    continue;
	  e=cev->csiarray.csi[pos].E/cal_par->csiarray.contr_e;
	  r=100*(data->csiarray.wfit[pos].am[3]/data->csiarray.wfit[pos].am[2])+100;
	  //ring=cev->csiarray.ring[pos];
	  if(e>=0 && e<S32K)
	    {
	      if(pGate->IsInside(e,r))
	        content++;
	      if(aGate->IsInside(e,r))
		content+=10;
	    }
	}
  free(cev);

  if(content==keep)
    return SEPARATOR_KEEP;
  
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/

int main(int argc, char *argv[])
{
  input_names_type* name;
  int n_a,n_p;
  FILE *cluster;
  char n[132];
  
  if(argc!=4)
    {
      printf("sfu_separate_PID master_file N_Alphas N_Protons\n\n");
      printf("Program separates according to the given particle fold\n");
      exit(-1);
    }
   
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  read_master(argv[1],name);
  
  name->flag.separate=1;

  TFile* g;
  if(name->flag.root_gate_file==1)
    {
      g=new TFile(name->fname.root_gate_file,"READ");
      pGate=(TCutG *) gROOT->FindObject("cut_0");
      aGate=(TCutG *) gROOT->FindObject("cut_1");
    }

  /* if(name->flag.inp_data!=1) */
  /*   { */
  /*     printf("ERROR!!! Input data file not defined!\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */

  if(name->flag.CSIARRAY_cal_par==1)
    {
      printf("CsIArray calpar read from: %s\n",name->fname.CSIARRAY_cal_par);
      initialize_CSIARRAY_calibration(&cal_par->csiarray,name->fname.CSIARRAY_cal_par);
    }
  else
    {
      printf("ERROR! CsIArray calibration parameters not defined!\n");
      exit(EXIT_FAILURE);
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

  n_a=atoi(argv[2]);
  n_p=atoi(argv[3]);
  keep=10*n_a+n_p;
  int i=0;
  /* name->flag.inp_data=1; */
  while(fscanf(cluster,"%s",n)!=EOF)
    {
      strcpy(name->fname.inp_data,n);
      sprintf(name->fname.out_data,"/home/matmarti/S2043/RDM/05.433/Data/2PFiles/testing_%i.sfu",i);
      sort(name);
      i++;
    }

  fclose(cluster);
  /* sort(name);  */
}
