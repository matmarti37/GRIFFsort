#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  uint64_t one=1;
  int pos;
  double e;
  if((data->h.setupHP&CsIArray_BIT)==0)
    return SEPARATOR_DISCARD;

  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  e=0;
  if(cev->csiarray.h.FE>0)
    for(pos=1;pos<NCSI;pos++)
      if((cev->csiarray.h.EHP[pos/64]&(one<<pos%64))!=0)
        e+=cev->csiarray.csi[pos].E/cal_par->csiarray.contr_e;
  if(e>=0)
    if(e<=S32K)
      hist[(int)e]++;
  free(cev);
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  FILE *output, *cluster;
  char DataFile[132];
  input_names_type* name;

  if(argc!=2)
    {
      printf("sfu_CsIArray_ECalSum master_file_name\n");
      exit(-1);
    }

  printf("Program sorts ECal histograms for the CsIArray.\n");
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  memset(hist,0,sizeof(hist));
  read_master(argv[1],name);  

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
      printf("Sorting calibrated energy histograms for TIGRESS clovers and cores based upon the cluster file: %s\n",name->fname.cluster_file);
      if((cluster=fopen(name->fname.cluster_file,"r"))==NULL)
	{
	  printf("ERROR! I can't open input file %s\n",name->fname.cluster_file);
	  exit(-2);
	}
    }
  while(fscanf(cluster,"%s",DataFile) != EOF)
    {
      memset(name,0,sizeof(input_names_type));
      strcpy(name->fname.inp_data,DataFile);
      
      printf("Sorting gamma-ray energy data from file %s\n", name);
      sort(name);
    }

  
  if((output=fopen("CsIArray_TotECal.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!");
      exit(EXIT_FAILURE);
    }
  fwrite(hist,S32K*sizeof(int),1,output);
  fclose(output);
}
