#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  int suppFlag=0;
  int take=0;
  int i=0;
  int j=0;

  double* energy;
  int* ring;
  int* position;


  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  
  calibrate_TIGRESS(data,&cal_par->tg,&cev->tg);
  
  energy=(double*)calloc(cev->tg.h.FA,sizeof(double));
  ring=(int*)calloc(cev->tg.h.FA,sizeof(int));
  position=(int*)calloc(cev->tg.h.FA,sizeof(int));

  if(cev->tg.h.FA<2)
    {
      free(cev);
      free(energy);
      free(ring);
      free(position);
      return SEPARATOR_DISCARD;
    }
  
  if(cev->tg.h.FA>0)
    for(pos=1;pos<NPOSTIGR;pos++)
      {
      	suppFlag=0;
      	if((cev->tg.h.HHP&(1<<(pos-1)))!=0)
	  if(cev->tg.det[pos].hge.FH>0)
	    if((cev->tg.h.AHP&(1<<(pos-1)))!=0)
	      {
		take=0;
		for(col=0;col<NCOL;col++)
		  {
		    if((cev->tg.det[pos].hge.HHP&(1<<col))!=0)
		      if(cev->tg.det[pos].ge[col].h.FH>0)
			{
			  if(cev->tg.det[pos].ge[col].suppress>=supLow && cev->tg.det[pos].ge[col].suppress<=supHigh && take==0)
			    {
			      suppFlag=1;
			      take=1;
			    }
			}
		  }

		energy[i]=cev->tg.det[pos].addback.E/cal_par->tg.contr_e;
		colAddBack=cev->tg.det[pos].addbackC;
		ring[i]=cev->tg.det[pos].ge[colAddBack].ring+NRING*suppFlag;
		position[i]=4*(pos-1)+colAddBack + 64*suppFlag;
		/* printf("%d\n",position[i]); */

		if(energy[i]>=0 && energy[i]<S32K)
		  /* if(position[i]!=20) */
		    projhist[position[i]][(int)(energy[i])]++;
		  //projhist[ring[i]][(int)(energy[i])]++;

		i++;//increment event counter

	      }
      }
  
  if(i!=cev->tg.h.FA)
    printf("WARNING: Addback fold not equal to the number of events seen!\n");
  
  for(i=0;i<cev->tg.h.FA;i++)
    {
      //look for a gamma that falls into the gate
      if(energy[i]>=0)
	if(energy[i]<S32K)
	  if(energy[i]>=gateELow/cal_par->tg.contr_e)
	    if(energy[i]<=gateEHigh/cal_par->tg.contr_e)
	      //if(ring[i]>0)
	      if(position[i]>=0)
		//if(ring[i]<NRING)
		if(position[i]<64)
		  /* if(position[i]!=20) */
		  {
		    //add all gammas in the event that aren't the gamma that fell into the gate
		    for(j=0;j<cev->tg.h.FA;j++)
		      {
			if(j!=i)
			  if(energy[j]>=0)
			    if(energy[j]<S32K)
			      //if(ring[j]>0)
			      if(position[j]>=0)
				//if(ring[j]<NRING)
				if(position[j]<64)
				  /* if(position[j]!=20) */
				    //hist[ring[j]][(int)(energy[j])]++;
				    hist[position[j]][(int)(energy[j])]++;
		      }
		    //gatehist[ring[i]][(int)(energy[i])]++;
		    gatehist[position[i]][(int)(energy[i])]++;
		    break;//don't double count
		  }
    }
  
  //printf("***** END OF EVENT *****\n");
  //getc(stdin);
  
  free(cev);
  free(energy);  
  free(ring);
  free(position);
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  FILE * output;
  input_names_type* name;
  FILE *cluster;
  char n[132],FileName[132];
  double avgGateE;
  double gateWidth;

  if(argc!=6)
    {
      printf("TIGRESS_ECalABSuppSumEGated master_file_name supLow supHigh gateELow gateEHigh\n");
      printf("Program attempts to generate energy gated gamma ray spectra (not background subtracted).  Energy gate values (gateEHigh, gateELow) should be specified in keV.\n");
      exit(-1);
    }
  
  printf("Program attempts to generate energy gated gamma ray spectra.\n");
  
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  memset(hist,0,sizeof(hist));
  memset(gatehist,0,sizeof(gatehist));
  memset(projhist,0,sizeof(projhist));
  read_master(argv[1],name);
  
  supLow=atof(argv[2]);
  supHigh=atof(argv[3]);
  gateELow = atof(argv[4]);
  gateEHigh = atof(argv[5]);

  if(gateELow>gateEHigh)
  	{
  		printf("ERROR: cannot have lower gate bound larger than upper gate bound.\n");
  		exit(-1);
  	}
  	
  avgGateE=(gateELow+gateEHigh)/2.;
  gateWidth=gateEHigh-gateELow;

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
  
  printf("\n");
  printf("  Using gamma energy gate between %f and %f keV.\n",gateELow,gateEHigh);
  printf("\n");
  
  name->flag.inp_data=1; 
  while(fscanf(cluster,"%s",n)!=EOF)
    {
      strcpy(name->fname.inp_data,n);
      printf("Sorting data from file %s\n", name->fname.inp_data);
      sort(name);
    }

  fclose(cluster);
  
  printf("\n");

  sprintf(FileName,"ECalABSuppSum_c%.0f_w%.0fgated.mca",avgGateE,gateWidth);
  if((output=fopen(FileName,"w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!\n");
      exit(EXIT_FAILURE);
    }
  /* fwrite(hist,2*NRING*S32K*sizeof(int),1,output); */
  fwrite(hist,2*65*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Gated spectrum saved to file: %s\n",FileName);
  
  sprintf(FileName,"ECalABSuppSum_c%.0f_w%.0fgate.mca",avgGateE,gateWidth);
  if((output=fopen(FileName,"w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!\n");
      exit(EXIT_FAILURE);
    }
  /* fwrite(gatehist,2*NRING*S32K*sizeof(int),1,output); */
  fwrite(gatehist,2*65*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Gate spectrum saved to file: %s\n",FileName);
  
  sprintf(FileName,"ECalABSuppSum_c%.0f_w%.0fproj.mca",avgGateE,gateWidth);
  if((output=fopen(FileName,"w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!\n");
      exit(EXIT_FAILURE);
    }
  /* fwrite(projhist,2*NRING*S32K*sizeof(int),1,output); */
  fwrite(projhist,2*65*S32K*sizeof(int),1,output);
  fclose(output);
  printf("Projection spectrum saved to file: %s\n",FileName);

}

  

