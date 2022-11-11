#include "sort.h"
NOT READY
int analyze_data(raw_event *data)
{
  // TIGRESS
  uint64_t one=1;
  int csi_pos;
  double p,r;

  // CsI ARRAY
  cal_event* cev;
  double e;
  int content=0, ring;

  
  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  /* if(cev->csiarray.h.FE==fold) */
    for(csi_pos=1;csi_pos<NCSI;csi_pos++)
      if((cev->csiarray.h.EHP[csi_pos/64]&(one<<csi_pos%64))!=0)
	{
	  if(data->csiarray.wfit[csi_pos].type!=1)
	    continue;
	  p=cev->csiarray.csi[csi_pos].E/cal_par->csiarray.contr_e;
	  r=100*(data->csiarray.wfit[csi_pos].am[3]/data->csiarray.wfit[csi_pos].am[2])+100;
	  ring=cev->csiarray.ring[pos];
	  if(e>=0 && e<S32K)
	    {
	      if(pGate->IsInside(p,r))
	        content++;
	      if(aGate->IsInside(p,r))
		content+=10;
	    }
	}
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
			if(content<10)
			  h_p[content][pos][(int)rint(e)]++;
			if(content==10)
			  h_a[1][pos][(int)rint(e)]++;
			if(content==20)
			  h_a[2][pos][(int)rint(e)]++;
			if(content==30)
			  h_a[3][pos][(int)rint(e)]++;
		      }
		  }
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
  float eff,bkg,efb;

  if(argc!=4)
    {
      printf("sfu_CsIArray_ContentMatrices master_file_name efficiency background\n");
      printf("efficiency: efficiency of detection\n");
      printf("background: prob. of additional detection\n");
      exit(-1);
    }
  
  printf("Program sorts calibrated energy histogram for TIGRESS cores \n");

  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  memset(h_p,0,sizeof(h_p));
  memset(h_a,0,sizeof(h_a));
  memset(h_p_chan,0,sizeof(h_p_chan));
  memset(h_a_chan,0,sizeof(h_a_chan));
  read_master(argv[1],name);
  eff=atof(argv[2]);
  bkg=atof(argv[3]);
  efb=(1.0-eff-bkg);

  // Filling matrix
  m[0][0]=eff*eff*eff + 3*eff*eff*efb*bkg + 3*eff*efb*efb*bkg*bkg + ebf*ebf*ebf*bkg*bkg*bkg;
  m[0][1]=eff*eff*bkg + 2*eff*efb*bkg*bkg + efb*efb*bkg*bkg*bkg;
  m[0][2]=eff*bkg*bkg + efb*bkg*bkg*bkg;

  m[1][0]=3*eff*eff*efb + 3*eff*efb*efb*bkg + efb*efb*efb*bkg*bkg;
  m[1][1]=eff*eff + 2*eff*efb*bkg + efb*efb*bkg*bkg;
  m[1][2]=eff*bkg * efb*bkg*bkg;

  m[2][0]=3*eff*efb*efb + efb*efb*efb*bkg;
  m[2][1]=2*eff*efb + efb*efb*bkg;
  m[2][2]=eff + efb*bkg;
  //

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
      aGate=(TCutG *) gROOT->FindObject("cut_1");
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

  for(int i=0;i<4;i++)
    {
      sprintf(n,"proton_%d.mca",i);
      if((output=fopen(n,"w"))==NULL)
	{
	  printf("ERROR! Cannot open mca file\n");
	  exit(EXIT_FAILURE);
	}
      for(int j=0;j<NPOSTIGR;j++)
	fwrite(h_p[i][j],S32K*sizeof(int),1,output);
      fclose(output);
    }
  for(int i=0;i<4;i++)
    {
      sprintf(n,"alpha_%d.mca",i);
      if((output=fopen(n,"w"))==NULL)
	{
	  printf("ERROR! Cannot open mca file\n");
	  exit(EXIT_FAILURE);
	}
      for(int j=0;j<NPOSTIGR;j++)
	fwrite(h_a[i][j],S32K*sizeof(int),1,output);
      fclose(output);
    }

  printf("Efficiency is: %.2f\n",epsilon);
  for(int j=0;j<NPOSTIGR;j++)
    for(int i=0;i<S32K;i++)
    {
      h_p_chan[0][j][i]=0;
      h_p_chan[1][j][i]=(int)(3*(1-epsilon)*(1-epsilon)*h_p[3][j][i]/(epsilon*epsilon*epsilon) - 2*(1-epsilon)*h_p[2][j][i]/(epsilon*epsilon) + h_p[1][j][i]/epsilon);
      h_p_chan[2][j][i]=(int)(h_p[2][j][i]/(epsilon*epsilon) - 3*(1-epsilon)*h_p[3][j][i]/(epsilon*epsilon*epsilon));
      h_p_chan[3][j][i]=(int)(h_p[3][j][i]/(epsilon*epsilon));

      h_a_chan[0][j][i]=0;
      h_a_chan[1][j][i]=(int)(3*(1-epsilon)*(1-epsilon)*h_a[3][j][i]/(epsilon*epsilon*epsilon) - 2*(1-epsilon)*h_a[2][j][i]/(epsilon*epsilon) + h_a[1][j][i]/epsilon);
      h_a_chan[2][j][i]=(int)(h_a[2][j][i]/(epsilon*epsilon) - 3*(1-epsilon)*h_a[3][j][i]/(epsilon*epsilon*epsilon));
      h_a_chan[3][j][i]=(int)(h_a[3][j][i]/(epsilon*epsilon));
    }

  for(int i=0;i<4;i++)
    {
      sprintf(n,"c_proton_%d.mca",i);
      if((output=fopen(n,"w"))==NULL)
	{
	  printf("ERROR! Cannot open mca file\n");
	  exit(EXIT_FAILURE);
	}
      for(int j=0;j<NPOSTIGR;j++)
	fwrite(h_p_chan[i][j],S32K*sizeof(int),1,output);
      fclose(output);
    }

  for(int i=0;i<4;i++)
    {
      sprintf(n,"c_alpha_%d.mca",i);
      if((output=fopen(n,"w"))==NULL)
	{
	  printf("ERROR! Cannot open mca file\n");
	  exit(EXIT_FAILURE);
	}
      for(int j=0;j<NPOSTIGR;j++)
	fwrite(h_a_chan[i][j],S32K*sizeof(int),1,output);
      fclose(output);
    }

  
  /* for(pos=1;pos<NPOSTIGR;pos++) */
  /*   { */
  /*     stop=0; */
  /*     for(col=0;col<NCOL;col++) */
  /* 	stop+=cal_par->tg.ceflag[pos][col]; */
  /*     if(stop>0) */
  /* 	{ */
  /* 	  sprintf(n,"pos%1d%1d_ECal.mca",pos/10,pos-(pos/10)*10); */
  /* 	  if((output=fopen(n,"w"))==NULL) */
  /* 	    { */
  /* 	      printf("ERROR! I cannot open the mca file!\n"); */
  /* 	      exit(EXIT_FAILURE); */
  /* 	    } */
	  
  /* 	  for(col=0;col<NCOL;col++) */
  /* 	    fwrite(hist[pos][col],S32K*sizeof(int),1,output); */
	  
  /* 	  fclose(output); */
  /* 	}} */
}

