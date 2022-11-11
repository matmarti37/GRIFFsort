#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DIM  32768 //S32K for mca, S4K for spn

double quad(double aa, double bb, double cc, double yy)
{
  double x_pos;//, x_neg;

  x_pos = ((-bb + sqrt(bb*bb + 4*aa*(yy-cc))) / (2*aa));
  //x_neg = ((-bb - sqrt(bb*bb + 4*aa*(yy-cc))) / (2*aa));

  //printf("For y = %f: x_pos = %f and x_neg = %f\n", yy, x_pos, x_neg);
  //printf("Returning x_pos.\n");

  if(x_pos < DIM)  
    return x_pos;
  else
    return (DIM-1);
}

int rebin(double aa, double bb, double cc, double* hist_quad, int* hist_input, int* hist_output, int verbose)
{
  int i,j;
  double overflow, floor_val, ceil_val;
  overflow = 0.0;
  
  for(i=0; i<DIM; i++)
    {
      if(i==DIM)
	verbose = 1;
      
      if(verbose == 1)
	printf("///////////////////////////////////////////////////////////// i=%d:\n", i);
      
      if(hist_quad[i] <= 0)
	{
	  hist_output[i] = 0;
	}
      else
	{
	  if(i>0)
	    {
	      if((floor(hist_quad[i]) - floor(hist_quad[i-1])) == 0)
		{
		  //Find the amount of counts corresponding to the head and tail of the output bin in terms of the input bins
		  floor_val = ((hist_quad[i] - hist_quad[i-1]) * (hist_input[i]));

		  //Combine these values, round them, add to the current bin
		  hist_output[i] += round(floor_val);

		  //Track the lost decimal as this progresses
		  overflow += (floor_val) - round(floor_val);

		  if(verbose == 1)
		    printf("Between output+=%f\n", ((hist_quad[i] - hist_quad[i-1]) * (hist_input[i])));

		  if(verbose == 1)
		    printf("Overflow value=%f\n", overflow);

		  //Implement the overflow when it corresponds to a full count.
		  if(abs(overflow) >= 1)
		    {
		      if(overflow < 0)
			{
			  overflow += 1;
			  hist_output[i] -= 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", -1);
			}
		      else
			{
			  overflow -= 1;
			  hist_output[i] += 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", 1);
			}

		    }
		}
	      else if((floor(hist_quad[i]) - floor(hist_quad[i-1])) >= 1)
		{
		  for(j=1; j<(floor(hist_quad[i]) - floor(hist_quad[i-1])); j++)
		    {
		      if(i+j < DIM)
			{
			  hist_output[i] += hist_input[i+j];
			  if(verbose == 1)
			    printf("For output+=%d\n", hist_input[i+j]);
			}
		      else
			{
			  printf("i +j > DIM!\n");
			  exit(1);
			}
		    }		  

		  //Find the amount of counts corresponding to the head and tail of the output bin in terms of the input bins
		  floor_val = ((hist_quad[i] - floor(hist_quad[i])) * (hist_input[(int)floor(hist_quad[i])]));
		  ceil_val = ((ceil(hist_quad[i-1]) - hist_quad[i-1]) * (hist_input[(int)floor(hist_quad[i-1])]));

		  //Combine these values, round them, add to the current bin
		  hist_output[i] += round(floor_val + ceil_val);

		  //Track the lost decimal as this progresses
		  overflow += (floor_val + ceil_val) - round(floor_val + ceil_val);
		  
		  if(verbose == 1)
		    printf("Floor and Ceil output+=%f\n", (((hist_quad[i] - floor(hist_quad[i])) * (hist_input[(int)floor(hist_quad[i])]))+((ceil(hist_quad[i-1]) - hist_quad[i-1]) * (hist_input[(int)floor(hist_quad[i-1])]))));

		  if(verbose == 1)
		    printf("Overflow value=%f\n", overflow);

		  //Implement the overflow when it corresponds to a full count.
		  if(abs(overflow) >= 1)
		    {
		      if(overflow < 0)
			{
			  overflow += 1;
			  hist_output[i] -= 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", -1);
			}
		      else
			{
			  overflow -= 1;
			  hist_output[i] += 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", 1);
			}

		    }
		}
	      else
		{
		  printf("Impossible step size!\n");
		  printf("First: %f and second: %f\n", hist_quad[i], hist_quad[i-1]);
		  exit(1);
		}      
	     
	    }
	  else
	    {
	      if(floor(hist_quad[i]) == 0)
		{
		  //Find the amount of counts corresponding to the head of the output bin in terms of the input bins
		  floor_val = ((hist_quad[i]) * (hist_input[(int)floor(hist_quad[i])]));

		  //Combine this value, round them, add to the current bin
		  hist_output[i] += round(floor_val);

		  //Track the lost decimal as this progresses
		  overflow += (floor_val) - round(floor_val);
		  
		  if(verbose == 1)
		    printf("Edge output+=%f\n", (hist_quad[i]) * (hist_input[(int)floor(hist_quad[i])]));

		  if(verbose == 1)
		    printf("Overflow value=%f\n", overflow);

		  //Implement the overflow when it corresponds to a full count.
		  if(abs(overflow) >= 1)
		    {
		      if(overflow < 0)
			{
			  overflow += 1;
			  hist_output[i] -= 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", -1);
			}
		      else
			{
			  overflow -= 1;
			  hist_output[i] += 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", 1);
			}

		    }
		}
	      else if(floor(hist_quad[i]) >= 1)
		{
		  for(j=0; j<(floor(hist_quad[i])); j++)
		    {
		      if(i+j < DIM)
			{
			  hist_output[i] += hist_input[i+j];
			  if(verbose == 1)
			    printf("For output+=%d\n", hist_input[i+j]);
			}
		      else
			{
			  printf("i +j > DIM!\n");
			  exit(1);
			}
		    }

		  //Find the amount of counts corresponding to the head of the output bin in terms of the input bins
		  floor_val = ((hist_quad[i] - floor(hist_quad[i])) * (hist_input[(int)floor(hist_quad[i])]));

		  //Combine this value, round them, add to the current bin
		  hist_output[i] += round(floor_val);

		  //Track the lost decimal as this progresses
		  overflow += (floor_val) - round(floor_val);
		  
		  if(verbose == 1)
		    printf("Floor output+=%f\n", ((hist_quad[i] - floor(hist_quad[i])) * (hist_input[(int)floor(hist_quad[i])])));

		  if(verbose == 1)
		    printf("Overflow value=%f\n", overflow);

		  //Implement the overflow when it corresponds to a full count.
		  if(abs(overflow) >= 1)
		    {
		      if(overflow < 0)
			{
			  overflow += 1;
			  hist_output[i] -= 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", -1);
			}
		      else
			{
			  overflow -= 1;
			  hist_output[i] += 1;
			  if(verbose == 1)
			    printf("Overflow output+=%d\n", 1);
			}

		    }
		}
	      else
		{
		  printf("Impossible step size!\n");
		  printf("First: %f and second: %f\n",hist_quad[i],hist_quad[i-1]);
		  exit(1);
		}  
	    }
	}

      if(verbose == 1)
	{
	  printf("Final output=%d\n", hist_output[i]);
	  printf("input=%d and quad=%f\n", hist_input[i], hist_quad[i]);
	  getc(stdin);
	}
      
    }

  return 0;
}

int main(int argc, char **argv) {

  FILE *fp;
  char *inp_name;
  int i,verbose;
  double a,b,c;
  int hist_input[DIM], hist_output[DIM];
  double hist_quad[DIM];  
 
  if (argc !=6) {
    printf("calibrationAttempt mca_to_shift a b c verbose\n");
    printf("Attempts to rebin based on fit parameters a, b and c.\n");
    printf("Where y = ax^2 + bx + c\n");
    printf("Assumptions: |a| = ~10^-6, b = ~2, |c| < 1.\n");
    printf("Set verbose to 1 for debugging\n");
    exit(1);
  }
  
  inp_name = argv[1];
  a = atof(argv[2]);
  b = atof(argv[3]);
  c = atof(argv[4]);
  verbose = atoi(argv[5]);

  printf("a = %f b = %f and c = %f\n", a, b, c);
  
  /* fp = fopen(inp_name, "r"); */
  /* if (fp == NULL) { */
  /*   printf("\n*** Could not open .mca file for reading\n"); */
  /*   exit(1); */
  /* }  */

  /* fread(hist_input, sizeof(hist_input), 1, fp); */
  memset(hist_input, 0, sizeof(hist_input));
  memset(hist_output, 0, sizeof(hist_output));
  memset(hist_quad, 0, sizeof(hist_quad));
  //fclose(fp);

  for(i=0; i<DIM-5; i++)
    {
      hist_quad[i] = quad(a, b, c, i);

      if(i >= 5)
	hist_input[i] = 5;
    }
  
  rebin(a, b, c, hist_quad, hist_input, hist_output, verbose); 

  fp = fopen("calAttempt.mca", "w");
  if (fp == NULL) {
    printf("\n*** Could not open output file for writing\n");
    exit(1);
  }
  fwrite(hist_output, sizeof(hist_output), 1, fp);
  fclose(fp);
  
  fp = fopen("quadAttempt.mca", "w");
  if (fp == NULL) {
    printf("\n*** Could not open output file for writing\n");
    exit(1);
  }
  fwrite(hist_quad, sizeof(hist_quad), 1, fp);  
  fclose(fp);

  fp = fopen("inputAttempt.mca", "w");
  if (fp == NULL) {
    printf("\n*** Could not open output file for writing\n");
    exit(1);
  }
  fwrite(hist_input, sizeof(hist_input), 1, fp);  
  fclose(fp);
  return 0;
}





