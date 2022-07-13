#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,prev;
  int  gate;
  static gmap map;
  long long dt;
  
  son=sizeof(node);
  memset(&prev,0,son);
  prev.csi_trig=-1;
  
  if(argc!=4)
    {
      printf("list_TIP_trigger fragment_list map gate_in_ns\n");
      exit(-1);
    }
  
 
  printf("Program assigns trigger number to TIP events on a list of fragments created from GRIF3/GRIF4 midas file.\n");


  read_map(argv[2],&map);

 
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
    gate=atoi(argv[3]);

  
    
     while(1)
       {
	 if(fread(&curr,son,1,fl)!=1) break;//stop on incorrect reading
	 if((curr.ch.timestamp|curr.ch.timestamp_up)!=0)//ignore bad events at the start
	   if(curr.chan>=map.csiarray_min)//check the range for TIP channels
	     if(curr.chan<=map.csiarray_max)//check the range for TIP channels
	       //if(map.hpge_lt[curr.chan-map.tig_min].seg==0)//channel present on the CC list
	       //if(map.hpge_lt[curr.chan-map.tig_min].pos>0)//channel present on the CC list
	       //if(map.hpge_lt[curr.chan-map.tig_min].pos<NPOSTIGR)//channel present on the CC list	       
		     {
		       if(prev.tsns==0)//the first channel since previous not stored
			 {
			   trigger=1;
			   curr.csi_trig=trigger;
			   fseek(fl,-son,SEEK_CUR);
			   fwrite(&curr,son,1,fl);
			   memcpy(&prev,&curr,son);//store to the previous
			 }
		       dt=curr.tsns-prev.tsns;
		       
		       if((int)dt<=gate)//coincidence with the event stored in previous
			 {
			   curr.csi_trig=trigger;
			   fseek(fl,-son,SEEK_CUR);
			   fwrite(&curr,son,1,fl);
			   /* memcpy(&prev,&curr,son);//store to the previous      // Commented so does not reset gate if finds new gamma within	    */
			 }
		       else//new event
			 {
			   trigger++;
			   curr.csi_trig=trigger;
			   fseek(fl,-son,SEEK_CUR);
			   fwrite(&curr,son,1,fl);
			   memcpy(&prev,&curr,son);//store to the previous	   
			 }
		       
		     }
	 
       }

 
    fclose(fl);
  

    
}
