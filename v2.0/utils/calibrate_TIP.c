#include "calibrate_TIP.h"

int TIP_cal_initialize()
{
 int i;
 for(i=0;i<128;i++)
 {
  TIP_cal_params[i][0]=0.;
  TIP_cal_params[i][1]=1.;
 }
 printf("Initialized TIP calibration to\n");
 printf("   Energy = Channel\n");
 printf("Reading calibration file now\n");
 return 0;
}

int TIP_calibration(char *cal_filename)
{
 // Initializes array for calibration
 TIP_cal_initialize();
 
 // Opens calibration file and exits if fails
 FILE *cal_file=open(cal_filename,"r");
 if(cal_file==NULL)
  {
   printf("\nError in opening TIP calibration file\n");
   exit(-1);
  }
 
 // Reads calibration parameters from file
 char * line=NULL;
 size_t len=0;
 ssize_t read;
 int num_items=0;
 int buffer=0, buffer2=0;
 while((read=getline(&line,&len,cal_file))!=-1)
  {
   num_items=sscanf(line,"%d\t%LF\t%LF",&i,&buffer);
   num_items=sscanf(line,"%d\t%LF\t%LF",&buffer2,&TIP_cal_params[i][0],&TIP_cal_params[i]);
   if(num_items!=3)
    {
     printf("Fix calibration file\n");
     exit(-1);
    }
  }
 printf("Read TIP Calibration file\n");
 return 0;
}
