#include "sort.h"

/*================================================================*/
int analyze_fragment(Grif_event* ptr, short* waveform)
{
  /* long ts; */
  int tsup;
  /* ts=(ptr->timestamp&0xfffffffffffc0000)<<4; */
  /* ts+=ptr->cfd; */
  /* ts*=10; */
  /* ts/=16; */
  tsup=(int)((ptr->timestamp>>32)&0xffff);

  h[tsup]++;
  
  
  /* printf("=========================================================\n"); */
  /* printf(" Data Time Stamp [samples]:   %16ld 0x%16.16lx\n",ptr->timestamp,ptr->timestamp); */
  /* printf(" Time Stamp U18B [samples]:   %16d 0x%16.16x\n",tsup,tsup); */
  /* printf(" Time Stamp L18B [samples]:   %16ld 0x%16.16lx\n",(ptr->timestamp&0x3ffff),(ptr->timestamp&0x3ffff)); */
  /* printf("        CFD T18B [samples]:   %16ld 0x%16.16lx\n",(long)(ptr->cfd>>4),(long)(ptr->cfd>>4)); */
  /* printf("          CFD/16 [samples]:   %16ld 0x%16.16lx\n",(long)(ptr->cfd/16),(long)(ptr->cfd/16)); */
  /* printf("             CFD [ns]     :   %16ld 0x%16.16lx\n",(long)(ptr->cfd/1.6),(long)(ptr->cfd/1.6)); */
  /* printf("      Time Stamp [ns]     :   %16ld 0x%16.16lx\n",ts,ts); */
  /* printf("      Time Stamp [samples]:   %16ld 0x%16.16lx\n",ts/10,ts/10); */
 
 
  //getc(stdin);
  return 0;
}
/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* output;

  if(argc!=2)
    {
      printf("view_timing midas_input_data\n");
      exit(-1);
    }

  memset(&h,0,sizeof(h));
 
  /* do sorting */
  sort_but_not_assemble(argv[1]);
  printf("Program provides information on consecutive fragments.\n");

  if((output=fopen("TSUP_HIST.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file.\n");
      exit(EXIT_FAILURE);
    }
  fwrite(h,sizeof(h),1,output);
  fclose(output);
}
