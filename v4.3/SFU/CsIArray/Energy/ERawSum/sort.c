#include "sort.h"

int analyze_data(raw_event *data)
{
  /* cal_event* cev; */
  uint64_t one=1;
  int pos;
  double e;
  
 if((data->h.setupHP&CsIArray_BIT)==0)
    return SEPARATOR_DISCARD;

  if(data->csiarray.h.Efold>0)
    for(pos=1;pos<NCSI;pos++)
      if((data->csiarray.h.EHP[pos/64]&(one<<pos%64))!=0)
	if(data->csiarray.wfit[pos].type==1)
	{
	  e=data->csiarray.wfit[pos].am[3]+data->csiarray.wfit[pos].am[2];
	  hist[pos][(int)(e)]++;
	  h->Fill(e,pos);
	}
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  FILE *output, *cluster;
  char DataFile[132];
  input_names_type* name;
  /* TCanvas *canvas; */
  /* TApplication *theApp; */

  if(argc!=2)
    {
      printf("sfu_CsIArray_ERawSum master_file_name\n");
      exit(-1);
    }
  
  h = new TH2D("ERaw","ERaw",S32K,0,S32K-1,NCSI,0,NCSI);
  h->Reset();

  printf("Program sorts ERaw histograms for the CsIArray.\n");
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  read_master(argv[1],name);

  /* if(name->flag.inp_data!=1) */
  /*   { */
  /*     printf("ERROR!!! Input data file not defined!\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
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
  
  if((output=fopen("CsIArray_ERaw.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!");
      exit(EXIT_FAILURE);
    }
  for(int pos=0;pos<NCSI;pos++)
    fwrite(hist[pos],S32K*sizeof(int),1,output);
  
  fclose(output);

  TFile f("CsI_ERaw.root","recreate");
  h->GetXaxis()->SetTitle("Charge [arb.]");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("Position");
  h->GetYaxis()->CenterTitle(true);
  h->SetOption("COLZ");
  h->Write();
  f.Close();
}
