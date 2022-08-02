#include "sort.h"

int analyze_data(raw_event *data)
{
  // TIGRESS
  uint64_t one=1;
  int csi_pos;
  double p,r;

  // CsI ARRAY
  cal_event* cev;
  double e;
  int p_count=0;

  
  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  if(cev->csiarray.h.FE==2)
    for(csi_pos=1;csi_pos<NCSI;csi_pos++)
      if((cev->csiarray.h.EHP[csi_pos/64]&(one<<csi_pos%64))!=0)
	{
	  if(data->csiarray.wfit[csi_pos].type!=1)
	    continue;
	  p=cev->csiarray.csi[csi_pos].E/cal_par->csiarray.contr_e;
	  r=100*(data->csiarray.wfit[csi_pos].am[3]/data->csiarray.wfit[csi_pos].am[2])+100;
	  if(e>=0 && e<S32K)
	    {
	      if(pGate->IsInside(p,r))
	        p_count++;
	    }
	}
  if(p_count==2)
    {
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
		      {
			//printf("made it %d\n",count);
			hist[pos][col][(int)rint(e)]++;
			//count++;
		      }
		    else hist[pos][col][S32K-10]++;
		  }}
  free(cev);
  return SEPARATOR_DISCARD;
}
/*=========================================================================*/
int main(int argc, char *argv[])
{
  FILE * output;
  input_names_type* name;
  int stop,pos,col;
  char n[132];

  if(argc!=2)
    {
      printf("CsIArray_Gated_Energy master_file_name\n");
      exit(-1);
    }
  
  printf("Program sorts calibrated energy histogram for TIGRESS cores \n");

  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  memset(hist,0,sizeof(hist));
  read_master(argv[1],name);

  if(name->flag.inp_data!=1)
    {
      printf("ERROR! Input data file not defined.\n");
      exit(EXIT_FAILURE);
    }
  
  if(name->flag.TIGRESS_cal_par==1)
    {
      printf("TIGRESS calpar read from: %s\n",name->fname.TIGRESS_cal_par);
      initialize_TIGRESS_calibration(&cal_par->tg,name->fname.TIGRESS_cal_par);
    }
  else
    {
      printf("ERROR! TIGRESS calibration parameters not defined\n");
      exit(EXIT_FAILURE);
    }


  // CSI STUFF //
  TFile* g;
  if(name->flag.root_gate_file==1)
    {
      g=new TFile(name->fname.root_gate_file,"READ");
      pGate=(TCutG *) gROOT->FindObject("cut_0");
    }
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
  // //


  
  
  sort(name);

  for(pos=1;pos<NPOSTIGR;pos++)
    {
      stop=0;
      for(col=0;col<NCOL;col++)
	stop+=cal_par->tg.ceflag[pos][col];
      if(stop>0)
	{
	  sprintf(n,"pos%1d%1d_ECal.mca",pos/10,pos-(pos/10)*10);
	  if((output=fopen(n,"w"))==NULL)
	    {
	      printf("ERROR! I cannot open the mca file!\n");
	      exit(EXIT_FAILURE);
	    }
	  
	  for(col=0;col<NCOL;col++)
	    fwrite(hist[pos][col],S32K*sizeof(int),1,output);
	  
	  fclose(output);
	}}}

