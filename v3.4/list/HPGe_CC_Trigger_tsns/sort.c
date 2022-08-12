#include "sort.h"

/*================================================================*/
int main(int argc, char *argv[])
{
  FILE* fl;
  size_t son;
  node curr,prev;
  
  son=sizeof(node);
  memset(&prev,0,son);
  
  if(argc!=2)
    {
      printf("list_HPGe_Trigger_tsns fragment_list\n");
      exit(-1);
    }
  

  printf("Program assigns time stamp in ns from first fragment in trigger to all fragments in trigger for CC events.\n");
  //printf("Program assigns trigger number to HPGe central contact events on a list of fragments created from GRIF3/GRIF4 midas file.\n");


  //read_map(argv[2],&map);

 
    
    if((fl=fopen(argv[1],"r+"))==NULL)
      {
	printf("ERROR!!! I can't open %s for read/write access!\n",argv[1]);
	exit(-2);
      }
  
    //gate=atoi(argv[3]);

    prev.tsns=-1;
    prev.tig_trig=-1;

    while(1)
      {
	if(fread(&curr,son,1,fl)!=1) break; //stop on incorrect reading
	if(curr.tig_trig>0) //look for tigress events with triggers
	  {
	    if(curr.tig_trig==prev.tig_trig) //if in coincidence
	      {
		curr.trig_tsns=prev.tsns;
		fseek(fl,-son,SEEK_CUR);
		fwrite(&curr,son,1,fl);
	      }
	    else
	      {
		curr.trig_tsns=curr.tsns;
		fseek(fl,-son,SEEK_CUR);
		fwrite(&curr,son,1,fl);
		memcpy(&prev,&curr,son);//store to previous
	      }
	  }
      }

  
    
     /* while(1) */
     /*   { */
     /* 	 if(fread(&curr,son,1,fl)!=1) break;//stop on incorrect reading */
     /* 	 if((curr.ch.timestamp|curr.ch.timestamp_up)!=0)//ignore bad events at the start */
     /* 	   if(curr.chan>=map.tig_min)//check the range for TIGRESS channels */
     /* 	     if(curr.chan<=map.tig_max)//check the range for TIGRESS channels */
     /* 	       if(map.hpge_lt[curr.chan-map.tig_min].seg==0)//channel present on the CC list */
     /* 		 if(map.hpge_lt[curr.chan-map.tig_min].pos>0)//channel present on the CC list */
     /* 		   if(map.hpge_lt[curr.chan-map.tig_min].pos<NPOSTIGR)//channel present on the CC list	        */
     /* 		     { */
     /* 		       if(prev.tsns==0)//the first channel since previous not stored */
     /* 			 { */
     /* 			   trigger=1; */
     /* 			   curr.tig_trig=trigger; */
     /* 			   fseek(fl,-son,SEEK_CUR); */
     /* 			   fwrite(&curr,son,1,fl); */
     /* 			   memcpy(&prev,&curr,son);//store to the previous */
     /* 			 } */
     /* 		       dt=curr.tsns-prev.tsns; */
		       
     /* 		       if((int)dt<=gate)//coincidence with the event stored in previous */
     /* 			 { */
     /* 			   curr.tig_trig=trigger; */
     /* 			   fseek(fl,-son,SEEK_CUR); */
     /* 			   fwrite(&curr,son,1,fl); */
     /* 			   /\* memcpy(&prev,&curr,son);//store to the previous      // Commented so does not reset gate if finds new gamma within	    *\/ */
     /* 			 } */
     /* 		       else//new event */
     /* 			 { */
     /* 			   trigger++; */
     /* 			   curr.tig_trig=trigger; */
     /* 			   fseek(fl,-son,SEEK_CUR); */
     /* 			   fwrite(&curr,son,1,fl); */
     /* 			   memcpy(&prev,&curr,son);//store to the previous	    */
     /* 			 } */
		       
     /* 		     } */
	 
     /*   } */

 
    fclose(fl);
  

    
}
