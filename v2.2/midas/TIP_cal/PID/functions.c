/*-------------------------------------------------*/
//      READ PARAMETER FILE
/*-------------------------------------------------*/
void read_parameter_file(char *param_filename)
{
 FILE *param_file=fopen(param_filename,"r");
 if(param_file==NULL) {printf("\nError in opening parameter file\n"); exit(-1);}
 
 printf("Successfully opened parameter file\nReading parameter file\n\n");
 char * param_line=NULL;
 size_t len=0; ssize_t read;
 int num_items=0;
 char buf[128],buf2[128];
 while((read=getline(&param_line,&len,param_file))!=-1)
 {
  num_items=sscanf(param_line,"%s %s\n",buf,buf2);
  if(num_items!=2) {printf("Fix parameter file\n"); exit(-1);}
  
  if(strcmp(buf,"DATA_LIST")==0) {strcpy(data_filename,buf2);}
  else if(strcmp(buf,"OUTPUT_FILE")==0) {strcpy(output_filename,buf2);}
  else if(strcmp(buf,"DETECTOR_MAP")==0) {strcpy(map_filename,buf2);}
  else if(strcmp(buf,"CALIBRATION_FILE")==0) {strcpy(cal_filename,buf2);}
  else if(strcmp(buf,"RING_FILE")==0) {strcpy(ring_filename,buf2);}
  else if(strcmp(buf,"CHI_SQ_CUTOFF")==0) {chisq_cutoff=atoi(buf2);}
  else if(strcmp(buf,"T_RC")==0) {par->t[1]=atof(buf2);}
  else if(strcmp(buf,"T_F")==0) {par->t[2]=atof(buf2);}
  else if(strcmp(buf,"T_S")==0) {par->t[3]=atof(buf2);}
  else if(strcmp(buf,"T_G")==0) {par->t[4]=atof(buf2);}
  else if(strcmp(buf,"RING_LOW")==0) {ring_low=atoi(buf2);}
  else if(strcmp(buf,"RING_HIGH")==0) {ring_high=atoi(buf2);}
  else if(strcmp(buf,"PLOT_UNCALIBRATED")==0 && (strcmp(buf2,"YES")==0 || strcmp(buf2,"yes") || strcmp(buf2,"y") || strcmp(buf2,"Y"))) {ampl_flag=1;}
  else {printf("Unknown parameter: %s\nIgnoring line and continuing\n",buf);}
 }
 printf("\nParameter file read\n");
 printf("\n");
 printf("Data file:              %s\n",data_filename);
 printf("Outpute file:           %s\n",output_filename);
 printf("Map file:               %s\n",map_filename);
 printf("Calibration file:       %s\n",cal_filename);
 printf("Ring file:              %s\n",ring_filename);
 printf("Chi sq cutoff:          %d\n",chisq_cutoff);
 printf("tRC:                    %Lf\n",par->t[1]);
 printf("tF:                     %Lf\n",par->t[2]);
 printf("tS:                     %Lf\n",par->t[3]);
 printf("tG:                     %Lf\n",par->t[4]);
 printf("Ring low:               %d\n",ring_low);
 printf("Ring high:              %d\n",ring_high);
 return;
}

/*-------------------------------------------------*/
//      READ MAP FILE
/*-------------------------------------------------*/
void read_map_file(char *filename)
{
 FILE *map_file=fopen(filename,"r");
 if(map_file==NULL) {printf("\nError in opening map file\n"); exit(-1);}
 
 int i;
 
 printf("Successfully opened map file\nReading map file\n");
 for(i=0;i<S2K;i++) {det_map[i]=-1;} // Initializes the detector map
 
 char * line=NULL;
 size_t len=0; ssize_t read;
 int num_items=0,j;
 int buf=0, buf2=0;
 while((read=getline(&line,&len,map_file))!=-1)
 {
  num_items=sscanf(line,"%d\t%d",&j,&buf);
  num_items=sscanf(line,"%d\t%d",&buf2,&det_map[j]);
  if(num_items!=2) {printf("Fix map file\n"); exit(-1);}
 }
 printf("Successfully read map file\n\n");
 return;
}

/*-------------------------------------------------*/
//      CALIBRATE TIP
/*-------------------------------------------------*/
void TIP_calibration(char *filename)
{
 int i;
 for(i=0;i<256;i++) {TIP_cal_params[i][0]=0.; TIP_cal_params[i][1]=1.;}
 printf("Initialized TIP calibration to\n");
 printf("    Energy = Channel\n");
 printf("Reading calibration file now\n");
 
 FILE *cal_file=fopen(filename,"r");
 if(cal_file==NULL) {printf("\nError in opening calibration file\n"); exit(-1);}
 printf("Successfully opened calibration file\n\n");
 
 char * line=NULL;
 size_t len=0; ssize_t read;
 int num_items=0,j;
 long double buf=0; int buf2=0;
 while((read=getline(&line,&len,cal_file))!=-1)
 {
  num_items=sscanf(line,"%d\t%Le\t%Le",&j,&buf,&buf);
  num_items=sscanf(line,"%d\t%Le\t%Le",&buf2,&TIP_cal_params[j][0],&TIP_cal_params[j][1]);
  if(num_items!=3) {printf("Fix calibration file\n"); exit(-1);}
 }
 
 printf("Successfully read TIP calibration file\n\n");
 //for(i=1;i<129;i++) {printf("Detector: %d  a0: %1.3Le  a1: %1.3Le\n",i,TIP_cal_params[i][0],TIP_cal_params[i][1]);}
 return;
}

/*-------------------------------------------------*/
//      READ RING MAP
/*-------------------------------------------------*/
void read_ring_map(char *filename)
{
 FILE *ring_file=fopen(filename,"r");
 if(ring_file==NULL) {printf("\nError in opening ring map file\n"); exit(-1);}
 
 int i;
 for(i=0;i<10;i++) {ring_dets[i][0]=0; ring_dets[i][1]=0;}
 
 char * line=NULL;
 size_t len; ssize_t read;
 int num_items=0,j,k;
 int buf=0, buf2=0;
 while((read=getline(&line,&len,ring_file))!=-1)
 {
  num_items=sscanf(line,"%d\t%d\t%d",&j,&buf,&buf);
  num_items=sscanf(line,"%d\t%d\t%d",&buf2,&ring_dets[j][0],&ring_dets[j][1]);
  if(num_items!=3) {printf("Fix ring map file\n"); exit(-1);}
  
  for(k=1;k<129;k++) {if(k>=ring_dets[j][0]&&k<=ring_dets[j][1]) {dets_ring[k]=j;}}
 }
 
 det_low=ring_dets[ring_low][0];
 det_high=ring_dets[ring_high][1];
 printf("Converted from ring to detector\n");
 printf("Detector low:            %d\n",det_low);
 printf("Detector high:           %d\n\n",det_high);
 return;
}

/*-------------------------------------------------*/
//      CREATES HISTOGRAMS
/*-------------------------------------------------*/
void create_histograms()
{
 char histname[128];
 
 sprintf(histname,"Calibrated Particle ID");
 cal_PID=new TH2D(histname,histname,S8K,0,32,150,100,250); cal_PID->Reset();
 
 sprintf(histname,"PID_Uncalibrated");
 uncal_PID=new TH2D(histname,histname,S1K,0,S4K,150,100,250); uncal_PID->Reset();
 
 int i;
 for(i=0;i<10;i++)
 {
  sprintf(histname,"Ring%2d_PID_Calibrated",i);
  ring_cal_PID[i]=new TH2D(histname,histname,S8K,0,32,150,100,250); ring_cal_PID[i]->Reset();
  
  sprintf(histname,"Ring%2d_PID_Uncalibrated",i);
  ring_uncal_PID[i]=new TH2D(histname,histname,S1K,0,S4K,150,100,250); ring_uncal_PID[i]->Reset();
 }
 
 printf("Histograms initialized\n\n");
 return;
}

/*-------------------------------------------------*/
//      LOOP THROUGH FILES AND DO SORT
/*-------------------------------------------------*/
void sort_data(char *filename)
{
 FILE *inputfile=fopen(filename,"r");
 if(inputfile==NULL) {printf("\nError in opening data file\n"); exit(-1);}
 
 char * line=NULL;
 size_t len; ssize_t read;
 int num_items=0;
 char current_file[256];
 while((read=getline(&line,&len,inputfile))!=-1)
 {
  num_items=sscanf(line,"%s",current_file);
  if(num_items!=1) {printf("Fix data file\n"); exit(-1);}
  printf("Sorting data for: %s\n\n",current_file);
  sort_but_not_assemble(current_file);
 }
 fclose(inputfile);
 return;
}

/*-------------------------------------------------*/
//      CREATE AND FORMAT ROOT FILES
/*-------------------------------------------------*/
void create_root_files(char *output_filename)
{
 TFile f(output_filename,"recreate");
 
 if(cal_PID->GetEntries())
 {
  cal_PID->GetXaxis()->SetTitle("Energy [MeV]");
  cal_PID->GetXaxis()->CenterTitle(true);
  cal_PID->GetYaxis()->SetTitle("A_{S}/A_{F} \\times 100 + 100");
  cal_PID->GetYaxis()->CenterTitle(true);
  cal_PID->GetYaxis()->SetTitleOffset(0);
  cal_PID->SetOption("COLZ");
  cal_PID->SetStats(0);
  cal_PID->Write();
 }
 if(uncal_PID->GetEntries())
 {
  uncal_PID->GetXaxis()->SetTitle("Amplitude [arb.]");
  uncal_PID->GetXaxis()->CenterTitle(true);
  uncal_PID->GetYaxis()->SetTitle("$A_S/A_F \\times 100 + 100$");
  uncal_PID->GetYaxis()->CenterTitle(true);
  uncal_PID->GetYaxis()->SetTitleOffset(0);
  uncal_PID->SetOption("COLZ");
  uncal_PID->Write();
 }
 
 int i;
 for(i=0;i<10;i++)
 {
  if(ring_cal_PID[i]->GetEntries())
  {
   ring_cal_PID[i]->GetXaxis()->SetTitle("Energy [MeV]");
   ring_cal_PID[i]->GetXaxis()->CenterTitle(true);
   ring_cal_PID[i]->GetYaxis()->SetTitle("$A_S/A_F \\times 100 + 100$");
   ring_cal_PID[i]->GetYaxis()->CenterTitle(true);
   ring_cal_PID[i]->GetYaxis()->SetTitleOffset(0);
   ring_cal_PID[i]->SetOption("COLZ");
   ring_cal_PID[i]->Write();
  }
  if(ring_uncal_PID[i]->GetEntries())
  {
   ring_uncal_PID[i]->GetXaxis()->SetTitle("Amplitude [arb.]");
   ring_uncal_PID[i]->GetXaxis()->CenterTitle(true);
   ring_uncal_PID[i]->GetYaxis()->SetTitle("$A_S/A_F \\times 100 + 100$");
   ring_uncal_PID[i]->GetYaxis()->CenterTitle(true);
   ring_uncal_PID[i]->GetYaxis()->SetTitleOffset(0);
   ring_uncal_PID[i]->SetOption("COLZ");
   ring_uncal_PID[i]->Write();
  }
 }
 return;
}





































