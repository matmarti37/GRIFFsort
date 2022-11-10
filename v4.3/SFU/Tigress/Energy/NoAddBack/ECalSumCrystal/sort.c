#include "sort.h"

int analyze_data(raw_event *data)
{
  int pos,col;
  double e;
  
  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);
  
  if(cev->tg.h.FE>0)
    for(pos=1;pos<NPOSTIGR;pos++)
      if((cev->tg.h.EHP&(1<<(pos-1)))!=0)
  	if(cev->tg.det[pos].hge.FE>0)
  	  for(col=0;col<NCOL;col++)
  	    if((cev->tg.det[pos].hge.EHP&(1<<col))!=0)
  	      if(cev->tg.det[pos].ge[col].h.FE>0)
  		if((cev->tg.det[pos].ge[col].h.EHP&1)!=0)
  		  {
  		    e=cev->tg.det[pos].ge[col].seg[0].E/cal_par->tg.contr_e;
		    if(e>=0 && e<S32K)
		      h->Fill(e,4*(pos-1)+col);
		  }
  free(cev);
  return SEPARATOR_DISCARD;
}
/*=========================================================================*/
int main(int argc, char *argv[])
{
  FILE *output, *cluster;
  input_names_type* name;
  int stop,pos,col;
  char DataFile[132];
  
  if(argc!=2)
    {
      printf("TIGRESS_ECalSum master_file_name\n");
      exit(-1);
    }
  
  printf("Program sorts summed ECal histograms for TIGRESS crystal cores from a cluster file\n");

  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  /* memset(hist,0,sizeof(hist)); */
  read_master(argv[1],name);

  h = new TH2D("ECalnoABSupp_by_Crystal","ECalnoABSupp_by_Crystal",S32K,0,S32K,64,0,64);
  h->Reset();
  
  if(name->flag.cluster_file==1)
    {
      printf("Sorting calibrated energy histograms for TIGRESS clovers and cores based upon the cluster file: %s\n",name->fname.cluster_file);
      if((cluster=fopen(name->fname.cluster_file,"r"))==NULL)
	{
	  printf("ERROR! I can't open input file %s\n",name->fname.cluster_file);
	  exit(-2);
	}}
  else
    {
      printf("ERROR! Cluster file not defined\n");
      exit(-1);
    }
  
  if(name->flag.TIGRESS_cal_par==1)
    {
      printf("TIGRESS calpar read from: %s\n",name->fname.TIGRESS_cal_par);
      initialize_TIGRESS_calibration(&cal_par->tg,name->fname.TIGRESS_cal_par);	      }
  else
    {
      printf("ERROR! TIGRESS calibration parameters not defined\n");
      exit(EXIT_FAILURE);
    }
  
  while(fscanf(cluster,"%s",DataFile) != EOF)
    {
      memset(name,0,sizeof(input_names_type));
      strcpy(name->fname.inp_data,DataFile);
      
      printf("Sorting gamma-ray energy data from file %s\n", name);
      sort(name);
    }

  TFile f("ch_v_det.root","recreate");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Detector");
  h->SetOption("COLZ");
  h->Write();
  f.Close();
}
