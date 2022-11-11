#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DIM  32768 //Equivalent to S4K, used for spn, mca useds S32K=32768

int main(int argc, char **argv) {

  FILE *fp1,*fp2;
  char *inp_name1,*inp_name2;
  int i,j,N;
  int low,high,LENGTH;
  double alphaN[DIM];
  double beta,hist1SUM,hist2SUM,chisq,STEP;
  int hist1[DIM],hist2[DIM];
  
 
  if (argc !=7) {
    printf("chisqspn inp_name1 inp_name2 start_bin end_bin step_size steps\n");
    printf("Attempts to calculate the scaling factor relating both spns.");
    printf("This does not account for background.");      
    exit(1);
  }
  
  inp_name1 = argv[1];
  inp_name2 = argv[2];
  low = atoi(argv[3]);
  high = atoi(argv[4]);
  STEP = atof(argv[5]);
  LENGTH = atoi(argv[6]);
  N = 0;
  beta = 0;
  hist1SUM = 0;
  hist2SUM = 0;
  chisq = 0;
  memset(alphaN,0,2*LENGTH);

 

  fp1 = fopen(inp_name1, "r");
  if (fp1 == NULL) {
    printf("\n*** Could not open matrix file 1 for reading\n");
    exit(1);
  } 

  fp2 = fopen(inp_name2, "r");
  if (fp2 == NULL) {
    printf("\n*** Could not open matrix file 2 for reading\n");
    exit(1);
  }

  fread(hist1, sizeof(hist1), 1, fp1);
  fread(hist2, sizeof(hist2), 1, fp2);

    
  for(i=low; i<high; i++)
    {
      hist1SUM += hist1[i];
      hist2SUM += hist2[i];
    }

  alphaN[0] = hist1SUM / hist2SUM;

  printf("High-low is: %d\n",high-low);

  printf("Step size is: %f\n",STEP);
  
  //printf("Alpha0 was found to be: %f\n",alphaN[0]);

  for(i=low; i<high; i++)
    {
      chisq += (pow((hist1[i]-(alphaN[0]*hist2[i])),2))/(hist1[i]+(pow(alphaN[0],2)*hist2[i]));
    }

  //printf("Chisq for Alpha0 was found to be: %f\n",chisq);


  for(j=1; j<(2*LENGTH); j++)
    {
      alphaN[j] = alphaN[0] + (STEP*alphaN[0]*(j-LENGTH));
      //      printf("Alpha%d was found to be: %f\n",j-LENGTH,alphaN[j]);

      chisq=0;
      for(i=low; i<high; i++)
	{
	  chisq += (pow((hist1[i]-(alphaN[j]*hist2[i])),2))/(hist1[i]+(pow(alphaN[j],2)*hist2[i]));
	}

      //      printf("Chisq for Alpha%d was found to be: %f\n",j-LENGTH,chisq);
      printf("%f      %f\n",alphaN[j],chisq);
    }
    
  /* for (i = 0; i < DIM; i++) */
  /*   { */
  /*     printf("Adding row %d\n",i); */
  /*     if(fread(hist1, sizeof(hist1), 1, fp1)>0) */
  /* 	if(fread(hist2, sizeof(hist2), 1, fp2)>0) */
  /* 	  for (j = 0; j < DIM; j++) */
  /* 	    { */
  /* 	      hist1[j]+=hist2[j]; */
  /* 	      fwrite(hist1, sizeof(hist1), 1, fp3); */
  /* 	    } */
  /*   } */

  fclose(fp1); 
  fclose(fp2); 

  return 0;
}





