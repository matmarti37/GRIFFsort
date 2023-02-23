#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  uint64_t one=1;
  int pos,csi,csi2;
  double etig,ecsi,ecsi2;
  
  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);

  if((data->h.setupHP&TIGRESS_BIT)==0)
    {
      free(cev);
      return SEPARATOR_DISCARD;
    }
  if((data->h.setupHP&CsIArray_BIT)==0)
    {
      free(cev);
      return SEPARATOR_DISCARD;
    }

  /* printf("Number of Tig hits and energy %d %d\n",cev->tg.h.FH,cev->tg.h.FE); */
  if(cev->tg.h.FH>0)
    if(cev->csiarray.h.FE>0)
      for(pos=1;pos<NPOSTIGR;pos++)
	if((cev->tg.h.HHP&(1<<(pos-1)))!=0)
	  if(cev->tg.det[pos].hge.FE>0)
	    if((cev->tg.h.AHP&(1<<(pos-1)))!=0)
	      {
		etig = cev->tg.det[pos].addback.E; /* TIGRESS energy in keV */
		/* printf("Number of CsI Fragments: %d\n",cev->csiarray.h.FE); */
		/* printf("CsI Hit Patten %12.12lld\n",cev->csiarray.h.EHP); */
		if(etig>=eLow && etig<=eHigh)
		//if(cev->csiarray.h.FE>1)
		for(csi=1;csi<NCSI;csi++)
		  //if(cev->csiarray.csi[csi].E>0)
		  if((cev->csiarray.h.EHP[csi/64]&(one<<csi%64))!=0)
		    {
		      num1++;
		      ecsi=cev->csiarray.csi[csi].E; /* CsI energy in keV */
		      for(csi2=csi+1;csi2<NCSI;csi2++)
			//if(cev->csiarray.csi[csi2].E>0)
			if((cev->csiarray.h.EHP[csi2/64]&(one<<csi2%64))!=0)
			  {
			    num2++;
			    ecsi2=cev->csiarray.csi[csi2].E;
			    h->Fill(ecsi,ecsi2);
			    h->Fill(ecsi2,ecsi);
			  }
		    }
	      }
  
  free(cev);
  return SEPARATOR_DISCARD;
}
/*=============================================================================*/
int main(int argc, char *argv[])
{
  FILE *cluster,*output;
  input_names_type* name;
  char DataFile[132];
  char rootFile[132];
  num1=0,num2=0;
 
  if(argc!=4)
    {
      printf("TigressCsIArray_CsIECalSum_TigEGate master_file_name Elow [keV] Ehigh [keV] \n");
      exit(-1);
    }

  h = new TH2D("TIG-Gated_CsI-CsI_EE","TIG-Gated_CsI-CsI_EE",S2K,0,S32K,S2K,0,S32K);
  h->Reset();

  //CsI energies for gating
  eLow=atoi(argv[2]);
  eHigh=atoi(argv[3]);
  
  printf("Program sorts CsI energy histograms for events with TIGRESS hits in the specified energy range.\n");
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  /* memset(hist,0,sizeof(hist)); */

  read_master(argv[1],name);
  
  if(name->flag.cluster_file==1)
    {
      printf("Sorting based upon the cluster file: %s\n",name->fname.cluster_file);
      if((cluster=fopen(name->fname.cluster_file,"r"))==NULL)
	{
	  printf("ERROR! I can't open input file %s\n",name->fname.cluster_file);
	  exit(-2);
	}
    }
  else
    {
      printf("ERROR! Cluster file not defined\n");
      exit(-1);
    }
  
  if(name->flag.TIGRESS_cal_par==1)
    {
      printf("TIGRESS calibration read from %s.\n",name->fname.TIGRESS_cal_par);
      initialize_TIGRESS_calibration(&cal_par->tg,name->fname.TIGRESS_cal_par);
    }
  if(name->flag.CSIARRAY_cal_par==1)
    {
      printf("CsIArray calpar read from: %s\n",name->fname.CSIARRAY_cal_par);
      initialize_CSIARRAY_calibration(&cal_par->csiarray,name->fname.CSIARRAY_cal_par);
    }
  else
    {
      printf("ERROR!!! TIGRESS calibration parameters not defined!\n");
      exit(EXIT_FAILURE);
    }
  
  while(fscanf(cluster,"%s",DataFile) != EOF)
    {
      memset(name,0,sizeof(input_names_type));
      strcpy(name->fname.inp_data,DataFile);
      
      printf("Sorting data from %s\n", name->fname.inp_data);
      sort(name); 
    }

  strcpy(rootFile,"TIG-Gated_CsI-CsI_EE.root");
  TFile f(rootFile,"recreate");
  h->GetXaxis()->SetTitle("CsI Energy 1 [keV]");
  h->GetYaxis()->SetTitle("CsI Energy 2 [keV]");
  h->SetOption("COLZ");
  h->Write();
  f.Close();

  /* if((output=fopen("CsIECalSum_TigEGate.mca","w"))==NULL) */
  /*   { */
  /*     printf("ERROR!!! I cannot open the mca file!\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
  
  /* fwrite(hist,NCSI*S32K*sizeof(int),1,output); */

  /* fclose(output); */

  printf("num1: %d\n",num1);
  printf("num2: %d\n",num2);
  return 0;
}
