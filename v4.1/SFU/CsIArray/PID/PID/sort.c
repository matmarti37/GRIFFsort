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
	      h[0]->Fill(e,r);
	      h[pos]->Fill(e,r);
	      h_ring[cev->csiarray.ring[pos]]->Fill(e,r);
	    }
	}
  free(cev);
  return SEPARATOR_DISCARD;
}
/*====================================================================================*/
int main(int argc, char *argv[])
{
  //FILE * output;
  input_names_type* name;
  TCanvas *canvas;
  TApplication *theApp;
  char histname[32];
  //TFile* g;

  if(argc!=2)
    {
      printf("sfu_CsIArray_PID master_file_name\n");
      exit(-1);
    }

  for(int i=0;i<NCSI;i++)
    {
      sprintf(histname,"PID_%3d",i);
      h[i] = new TH2D(histname,histname,S32K,0,S32K-1,150,100,249);
      h[i]->Reset();
    }
  for(int i=0;i<10;i++)
    {
      sprintf(histname,"PID_R%1d",i);
      h_ring[i] = new TH2D(histname,histname,S32K,0,S32K-1,150,100,249);
      h_ring[i]->Reset();
    }

  printf("Program sorts PID plot for the CsIArray. 0 is sum, i is det number\n");
  name=(input_names_type*)malloc(sizeof(input_names_type));
  memset(name,0,sizeof(input_names_type));
  cal_par=(calibration_parameters*)malloc(sizeof(calibration_parameters));
  memset(cal_par,0,sizeof(calibration_parameters));
  
  read_master(argv[1],name);

  if(name->flag.inp_data!=1)
    {
      printf("ERROR!!! Input data file not defined!\n");
      exit(EXIT_FAILURE);
    }

  if(name->flag.root_output_file!=1)
    {
      printf("ERROR!!! Output data file not defined!\n");
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
  
  /* if(name->flag.root_gate_file==1) */
  /*   { */
  /*     g=new TFile(name->fname.root_gate_file,"READ"); */
  /*     pGate=(TCutG *) gROOT->FindObject("cut_0"); */
  /*   } */
  
  sort(name);
  
  theApp=new TApplication("App", &argc, argv);
  canvas = new TCanvas("PID","PID",10,10, 500, 300);
  gPad->SetLogz(1);
  gStyle->SetPalette(1);
  h[0]->Draw("COLZ");

  char *output_filename=name->fname.root_output_file;
  printf("%s\n",output_filename);
  TFile f(output_filename,"recreate");

  for(int i=0;i<NCSI;i++)
    {
      h[i]->GetXaxis()->SetTitle("Energy [keV]");
      h[i]->GetXaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitle("A_{S}/A_{F} \\times 100 + 100");
      h[i]->GetYaxis()->CenterTitle(true);
      h[i]->GetYaxis()->SetTitleOffset(0);
      h[i]->SetOption("COLZ");
      //h[i]->SetStats(0);
      h[i]->Write();
    }
  for(int i=0;i<10;i++)
    {
      h_ring[i]->GetXaxis()->SetTitle("Energy [keV]");
      h_ring[i]->GetXaxis()->CenterTitle(true);
      h_ring[i]->GetYaxis()->SetTitle("A_{S}/A_{F} \\times 100 + 100");
      h_ring[i]->GetYaxis()->CenterTitle(true);
      h_ring[i]->GetYaxis()->SetTitleOffset(0);
      h_ring[i]->SetOption("COLZ");
      //h_ring[i]->SetStats(0);
      h_ring[i]->Write();
    }
  
  
  theApp->Run(kTRUE);
}
