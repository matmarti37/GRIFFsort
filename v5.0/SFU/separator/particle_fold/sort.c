#include "sort.h"

int analyze_data(raw_event *data)
{
  if(data->csiarray.h.TSfold==fold)
    return SEPARATOR_KEEP;
  
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/

int main(int argc, char *argv[])
{
  input_names_type* name;
  
  if(argc!=4)
    {
      printf("sfu_separate_particle_fold SFU_input_data SFU_output_data N_Particles\n\n");
      printf("Program separates according to the given particle fold\n");
      exit(-1);
    }
   
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  strcpy(name->fname.inp_data,argv[1]);
  strcpy(name->fname.out_data,argv[2]);
  name->flag.separate=1;

  fold=atoi(argv[3]);
  sort(name); 
}
