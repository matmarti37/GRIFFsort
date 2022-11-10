#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  int csi,ind,i;
  uint64_t one=1;
  double epart,ppart;

  int pos,col;
  int suppFlag=0,take=0;
  double eAddBack;
  int cAddBack;
  int ring,dsgroup=0;

  double DOTPRODUCT,ds=0;

  double borders[NRING];
  borders[0]=0.000;
  borders[1]=0.971;
  //borders[1]=0.980; //Checking something
  borders[2]=0.984;
  borders[3]=1.000;
  borders[4]=1.014;
  borders[5]=1.029;
  borders[6]=S2K;

  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  // Initialize vectors to 0
  memset(p_beam,0,sizeof(p_beam));
  memset(d_part,0,sizeof(d_part));
  memset(np_part,0,sizeof(np_part));
  memset(p_part,0,sizeof(p_part));
  memset(p_res,0,sizeof(p_res));
  memset(np_res,0,sizeof(np_res));
  memset(d_gamma,0,sizeof(d_gamma));
  memset(np_gamma,0,sizeof(np_gamma));
  
  p_beam[3]=sqrt((cal_par->csiarray.Ebeam*cal_par->csiarray.Ebeam) + (2*cal_par->csiarray.Ebeam*cal_par->csiarray.mproj));
  p_res[3]=p_beam[3];

  /////////
  // Calculates residual nucleus' momentum
  /////////
  if(cev->csiarray.h.FH>0)
    for(csi=0;csi<NCSI;csi++)
      if((cev->csiarray.h.HHP[csi/64]&(one<<csi%64))!=0)
	{
	  epart=cev->csiarray.csi[csi].E/1000.;
	  ppart=sqrt( (epart*epart) + (2*epart*cal_par->csiarray.mp));
	  for(ind=0;ind<3;ind++)
	    d_part[csi][ind+1]=cal_par->csiarray.cpos_xyz[csi][ind];
	  d_part[csi][0]=sqrt(d_part[csi][1]*d_part[csi][1]+d_part[csi][2]*d_part[csi][2]+d_part[csi][3]*d_part[csi][3]);
	  for(ind=1;ind<4;ind++)
	    {
	      np_part[csi][ind]=d_part[csi][ind]/d_part[csi][0];
	      p_part[csi][ind]=np_part[csi][ind]*ppart;
	      p_res[ind]-=p_part[csi][ind];
	    }
	}
  p_res[0]=sqrt(p_res[1]*p_res[1]+p_res[2]*p_res[2]+p_res[3]*p_res[3]);
  for(ind=1;ind<4;ind++)
    np_res[ind]=p_res[ind]/p_res[0];
  /* printf("Residual momentum: x:%.4f y:%.4f z:%.4f z\n",p_res[1],p_res[2],p_res[3]); */
  /* printf("Residual direction: x:%.4f y:%.4f z:%.4f z\n",np_res[1],np_res[2],np_res[3]); */

  beta=sqrt( 1 - (cal_par->csiarray.mr*cal_par->csiarray.mr)/(p_res[0]*p_res[0]+cal_par->csiarray.mr*cal_par->csiarray.mr) );
  /* printf("Residual beta is: %.4f\n",beta); */
  /////////
  /////////

  

  /////////
  // Gets direction of most energetic gamma ray
  /////////
  if(cev->tg.h.FA>0)
    for(pos=1;pos<NPOSTIGR;pos++)
      {
	suppFlag=0;
	if((cev->tg.h.HHP&(one<<(pos-1)))!=0)
	  if(cev->tg.det[pos].hge.FH>0)
	    if((cev->tg.h.AHP&(one<<(pos-1)))!=0)
	      {
		take=0;
		for(col=0;col<NCOL;col++)
		  if((cev->tg.det[pos].hge.HHP&(one<<col))!=0)
		    if(cev->tg.det[pos].ge[col].h.FH>0)
		      if((cev->tg.det[pos].ge[col].h.HHP&one)!=0)
			if(cev->tg.det[pos].ge[col].suppress>=supLow)
			  if(cev->tg.det[pos].ge[col].suppress<=supHigh)
			    if(take==0)
			      {
				suppFlag=1;
				take=1;
			      }
		eAddBack=0;
		if(suppFlag==0)
		  eAddBack=cev->tg.det[pos].addback.E/cal_par->tg.contr_e;
		/* eAddBack=cev->tg.det[pos].addback.E/cal_par->tg.contr_e; */ //Uncomment to include all energies, even those suppressed
		cAddBack=cev->tg.det[pos].addbackC;
		ring=cev->tg.det[pos].ge[cAddBack].ring;
		/* printf("Ring is %d\n",ring); */
		/* printf("Gamma energy is %.1f\n",eAddBack); */
		/* printf("Gamma position: pos: %d col: %d\n",pos,cAddBack); */

		for(ind=0;ind<4;ind++)
		  d_gamma[ind]=0;

		if(eAddBack>0)
		  if(eAddBack<S32K)
		    {
		      for(ind=1;ind<4;ind++)
			d_gamma[ind]=cal_par->tg.tpos_xyz[pos][cAddBack][ind-1];
		      d_gamma[0]=sqrt(d_gamma[1]*d_gamma[1]+d_gamma[2]*d_gamma[2]+d_gamma[3]*d_gamma[3]);
		      for(ind=0;ind<4;ind++)
			np_gamma[ind]=d_gamma[ind]/d_gamma[0];
		      /* printf("Tigress position x: %.4f y: %.4f z: %.4f\n",d_gamma[1],d_gamma[2],d_gamma[3]); */
		      /* printf("Tigress direction (mag: %.14f) x: %.4f y: %.4f z: %.4f\n",np_gamma[0],np_gamma[1],np_gamma[2],np_gamma[3]); */

		      DOTPRODUCT=0.;
		      for(ind=1;ind<4;ind++)
			DOTPRODUCT+=np_gamma[ind]*np_res[ind];
		      ds=sqrt(1-beta*beta)/(1-beta*(DOTPRODUCT));
		      /* ds2hist=(int)(1000*ds); */
		      if(ds>=0)
			if(ds<=2)
			  {
			    dshist[(int)(1000*ds)]++;
			    dsring->Fill(1000*ds,ring);
			    for(i=0;i<NRING;i++)
			      if(ds>borders[i])
				if(ds<=borders[i+1])
				  dsgroup=i+1;
			    /* printf("dsgroup is: %d\n",dsgroup); */
			    dsdsgroup->Fill(1000*ds,dsgroup);
			    dsgroupring->Fill(ring,dsgroup);
			    edsgroup[0][(int)(1000*ds+(dsgroup-1)*1000)]++;
			    edsgroup[dsgroup][(int)eAddBack]++;
			    ering[0][(int)(1000*ds+(ring-1)*1000)]++;
			    ering[ring][(int)eAddBack]++;
			  }
		    }
	      }
      }
  /////////
  /////////

  

  /* getc(stdin); */
  free(cev);
  return SEPARATOR_DISCARD;
}
/*=========================================================================*/
int main(int argc, char *argv[])
{
  FILE * output;
  FILE *cluster;
  input_names_type* name;
  char mcaFile[132];
  char rootFile[132];
  char DataFile[132];
 
  
  if(argc!=2 && argc!=4)
    {
      printf("sfu_DSGroups_HitPattern parameter_file [supLow] [supHigh]\n");
      exit(-1);
    }
  if(argc==2)
    {
      supLow=1;
      supHigh=32000;
    }
  if(argc==4)
    {
      supLow=atoi(argv[2]);
      supHigh=atoi(argv[3]);
    }
  
  printf("Program sorts TIGRESS ABSupp hits by Doppler Shift group\n");
  
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  memset(dshist,0,sizeof(dshist));
  dsring = new TH2D("DopplerShiftbyRing","DopplerShiftbyRing",100,950,1050,6,1,7);
  dsring->Reset();
  dsdsgroup = new TH2D("DopplerShiftbyGroup","DopplerShiftbyGroup",100,950,1050,6,1,7);
  dsdsgroup->Reset();
  dsgroupring = new TH2D("DopplerShiftGroupbyRing","DopplerShiftGroupbyRing",6,1,7,6,1,7);
  dsgroupring->Reset();
  memset(ering,0,sizeof(ering));
  memset(edsgroup,0,sizeof(edsgroup));
  
  read_master(argv[1],name);

  /* if(name->flag.inp_data!=1) */
  /*   { */
  /*     printf("ERROR!!! Input data file not defined.\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
  
  if(name->flag.TIGRESS_cal_par==1)
    {
      printf("TIGRESS calpar read from: %s\n",name->fname.TIGRESS_cal_par);
      initialize_TIGRESS_calibration(&cal_par->tg,name->fname.TIGRESS_cal_par);
    }
  else
    {
      printf("ERROR!!! TIGRESS calibration parameters not defined\n");
      exit(EXIT_FAILURE);
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

  // Print information
  printf("\n\nStarting Info\n================\n");
  printf("  Beam energy: %f MeV/c^2\n",cal_par->csiarray.Ebeam);
  printf("  Projectile mass: %f MeV/c^2\n",cal_par->csiarray.mproj);
  printf("  Particle mass: %f MeV/c^2\n",cal_par->csiarray.mp);
  printf("  Residual mass: %f MeV/c^2\n",cal_par->csiarray.mr);
  printf("================\n");

  if(name->flag.cluster_file==1)
    {
      //printf("Sorting ECalABSuppRingSum histograms for TIGRESS clovers and cores based upon the cluster file: %s\n",name->fname.cluster_file);
      if((cluster=fopen(name->fname.cluster_file,"r"))==NULL)
	{
	  printf("ERROR!!! I can't open input file %s\n",name->fname.cluster_file);
	  exit(-2);
	}
    }
  else
    {
      printf("ERROR!!! Cluster file not defined\n");
      exit(-1);
    }

  while(fscanf(cluster,"%s",DataFile) != EOF)
    {
      memset(name,0,sizeof(input_names_type));
      strcpy(name->fname.inp_data,DataFile);
      
      printf("Sorting data from file %s\n", name->fname.inp_data);
      sort(name);
    }
  
  
  /* sort(name); */

  strcpy(mcaFile,"dsHP.spn");
  if((output=fopen(mcaFile,"w"))==NULL)
    {
      printf("ERROR! Cannot open spn file\n");
      exit(EXIT_FAILURE);
    }
  fwrite(dshist,sizeof(dshist),1,output);
  fclose(output);
  printf("Spectrum saved to %s with multiplicative factor 1000\n",mcaFile);
  printf("Spectrum 0 contains all data\n");

  strcpy(mcaFile,"dsgroupE.mca");
  if((output=fopen(mcaFile,"w"))==NULL)
    {
      printf("ERROR! Cannot open mca file\n");
      exit(EXIT_FAILURE);
    }
  fwrite(edsgroup,NRING*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Spectrum saved to %s with multiplicative factor 1000\n",mcaFile);
  printf("Spectrum 0 has ds*dsgroup*1000, spectra 1-6 have energy for dsgroup\n");

  strcpy(mcaFile,"ringE.mca");
  if((output=fopen(mcaFile,"w"))==NULL)
    {
      printf("ERROR! Cannot open mca file\n");
      exit(EXIT_FAILURE);
    }
  fwrite(ering,NRING*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Spectrum saved to %s with multiplicative factor 1000\n",mcaFile);
  printf("Spectrum 0 has ds*ring*1000, spectra 1-6 have energy for ring\n");

  
  strcpy(rootFile,"ring_dsHP.root");
  TFile f(rootFile,"recreate");
  dsring->GetXaxis()->SetTitle("Doppler Shift Factor");
  dsring->GetYaxis()->SetTitle("Ring");
  dsring->SetOption("COLZ");
  dsring->Write();

  dsdsgroup->GetXaxis()->SetTitle("Doppler Shift Factor");
  dsdsgroup->GetYaxis()->SetTitle("Doppler Shift Group");
  dsdsgroup->SetOption("COLZ");
  dsdsgroup->Write();

  dsgroupring->GetXaxis()->SetTitle("Ring");
  dsgroupring->GetYaxis()->SetTitle("Doppler Shift Group");
  dsgroupring->SetOption("COLZ");
  dsgroupring->Write();
  f.Close();
}
