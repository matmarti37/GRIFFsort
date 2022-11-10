#include "sort.h"

int analyze_data(raw_event *data)
{
  cal_event* cev;
  uint64_t one=1;
  int pos;
  double e,r;

  if((data->h.setupHP&CsIArray_BIT)==0)
    return SEPARATOR_DISCARD;

  cev=(cal_event*)malloc(sizeof(cal_event));
  memset(cev,0,sizeof(cal_event));
  calibrate_CSIARRAY(data,&cal_par->csiarray,&cev->csiarray);

  if(cev->csiarray.h.FE>0)
    for(pos=1;pos<NCSI;pos++)
      if((cev->csiarray.h.EHP[pos/64]&(one<<pos%64))!=0)
	{
	  if(data->csiarray.wfit[pos].type!=1)
	    continue;
	  e=cev->csiarray.csi[pos].E/cal_par->csiarray.contr_e;
	  r=100*(data->csiarray.wfit[pos].am[3]/data->csiarray.wfit[pos].am[2])+100;
	  if(e>=0 && e<S32K)
	    {
	      if(pGate->IsInside(e,r))
		h->Fill(e,r);
	    }
	}
  free(cev);
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  FILE * output;
  input_names_type* name;
  TCanvas *canvas;
  TApplication *theApp;

  if(argc!=2)
    {
      printf("sfu_CsIArray_Gated_PID master_file_name\n");
      exit(-1);
    }
  
  h = new TH2D("PID","PID",S32K,0,S32K-1,150,100,249);
  h->Reset();

  printf("Program sorts PID plot for the CsIArray.\n");
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  read_master(argv[1],name);

  TFile* g;
  if(name->flag.root_gate_file==1)
    {
      g=new TFile(name->fname.root_gate_file,"READ");
      pGate=(TCutG *) gROOT->FindObject("cut_0");
    }

  if(name->flag.inp_data!=1)
    {
      printf("ERROR!!! Input data file not defined!\n");
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
  
  sort(name);

  /*
  if((output=fopen("CsIArray_ECal.mca","w"))==NULL)
    {
      printf("ERROR!!! I cannot open the mca file!");
      exit(EXIT_FAILURE);
    }
  for(int pos=0;pos<NCSI;pos++)
    fwrite(hist[pos],S32K*sizeof(int),1,output);
  
  fclose(output);
  */
  
  theApp=new TApplication("App", &argc, argv);
  canvas = new TCanvas("PID","PID",10,10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  h->Draw("COLZ");

  char *output_filename="testing.root";
  TFile f(output_filename,"recreate");
 
 if(h->GetEntries())
 {
  h->GetXaxis()->SetTitle("Energy [keV]");
  h->GetXaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitle("A_{S}/A_{F} \\times 100 + 100");
  h->GetYaxis()->CenterTitle(true);
  h->GetYaxis()->SetTitleOffset(0);
  h->SetOption("COLZ");
  h->SetStats(0);
  h->Write();
 }
  
  
  theApp->Run(kTRUE);
}
