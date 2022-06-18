#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TText.h"
#include "TLorentzVector.h"

#include "fileSys.h"



int main(int argc, char *argv[]){


  // === COMMAND LINE FLAGS ===================================

  // --- Default Files -----
  std::string eDataName = "./data/12C.root";

  // --- Default values -----
  float enSel = 0.620;
  float angSel = 36;

  bool verbose = false;  


  // --- Read command line -----
  int argCount = 0;
  int opt;
  while ((opt = getopt(argc, argv, ":hvE:a:d:")) != -1){
    switch (opt)
      {
      case 'h':
	help();
	return 0;
      case 'v':
	verbose = true;
	break;
      case 'E':
	enSel = std::stof(optarg);
	break;
      case 'a':
	angSel = std::stof(optarg);
	break;
      case 'd':
	eDataName = optarg;
	break;
      case ':':
	printf("\033[1;31m[ERROR]\033[0m -%c requires an argument.\n",optopt);
	return 0;
      case '?':
	printf("\033[1;33m[ERROR]\033[0m -%c is an unknown argument... just ignoring it.\n",optopt);
	break;
      }   
  }


  // --- Set Graph Style -----
  gStyle->SetOptStat(0);

  // ==========================================================




  // === SANITY CHECKS ========================================

  // --- Check files have been loaded -----
  if(!exist(eDataName)){
    std::cout << "\033[31;1m[ERROR]\033[0m No input quasi-elastic archive data; please supply data file." << std::endl;
    return 0;
  }

  // ==========================================================




  // === SAVE INFORMATION =====================================

  std::cout << "\033[1;34m[INFO]\033[0m Electron data selected with theta: " << angSel
	    << " and energy: " << enSel << "." << std::endl;
  std::string _directory = "/home/jmcelwee/T2K/eb_work/poly/plots/";
  std::string _saving = _directory + "e_"
    + std::to_string(static_cast<int>(enSel*1000)) + "_"
    + std::to_string(static_cast<int>(angSel));

  std::string _saveq3 = _saving + ".txt";
  _saving = _saving + ".pdf";

  // ==========================================================




  // === ELECTRON DATA ========================================

  std::cout << "\033[34;1m[INFO]\033[0m Reading in electron data." << std::endl;
  std::cout << "\t \033[1m" << eDataName << "\033[0m" << std::endl;
  TFile eData(eDataName.c_str(),"READ");
  TTree *eDTree = 0;
  eData.GetObject("electronScatter", eDTree);
  
  if (verbose){
    std::cout << "\033[34;1m[INFO]\033[0m Example output from the electron data:" << std::endl;
    eData.ls();
    eDTree->Show(0);
  }

  // --- Quasi elastic archive data ------      
  Float_t Elep, q0, theta, xsec,xsecErr;
  eDTree->SetBranchAddress("E", &Elep);
  eDTree->SetBranchAddress("q0",&q0);
  eDTree->SetBranchAddress("theta", &theta);
  eDTree->SetBranchAddress("xsec", &xsec);
  eDTree->SetBranchAddress("error", &xsecErr);


  std::vector<float> eDq0, eDxsec, eDerr;
  for (int evnt= 0; evnt < eDTree->GetEntries(); ++evnt){
    eDTree->GetEntry(evnt);
    if (Elep < enSel+0.01 && Elep > enSel-0.01
	&& theta > angSel-1 && theta < angSel+1){
      eDq0.push_back(q0);
      eDxsec.push_back(xsec);
      eDerr.push_back(xsecErr);
    }
  }
  

  float binning[eDq0.size()+1];
  binning[0] = 0;
  double bin;
  int maxpos = 0;
  

  for (int evnt = 0; evnt < eDq0.size(); ++evnt){
    
    // --- Binning     
    if (evnt == eDq0.size() - 1){
      bin = (eDq0.at(evnt) - binning[evnt]) + eDq0.at(evnt);
      binning[evnt+1] = bin;
    }
    else {
      bin = (eDq0.at(evnt) + eDq0.at(evnt+1))/2;
      binning[evnt+1] = bin;
    }
    
    // --- Find maximum   
    if (evnt < eDxsec.size()-3){
      if (evnt > 3 && eDxsec.at(evnt+2) < eDxsec.at(evnt) 
	           && eDxsec.at(evnt) > eDxsec.at(evnt-2)){
        if (maxpos == 0) maxpos = evnt;
      }
    }
  }


  // ==========================================================




  // === FITTING PARAMETERS ===================================

  // --- QE Data Graph ------
  TGraphErrors *eScatDat = new TGraphErrors(eDq0.size(), &eDq0[0], &eDxsec[0], 0, &eDerr[0]);
  //  TGraph *fitGraph = new TGraph(fitVectorX.size(), &fitVectorX[0], &fitVectorY[0]);
  eScatDat->SetMarkerStyle(2);
  eScatDat->SetMarkerSize(1);


  // --- Find maxima ------
  double *yvalues = eScatDat->GetY();
  double *xvalues = eScatDat->GetX();
  int max_location = TMath::LocMax(eScatDat->GetN(), yvalues);
  double eData_max = yvalues[max_location];
  float eData_maxX = xvalues[max_location];


  // ==========================================================



  // === PROCESS DATA =========================================

  float hist_lims[2] = {0,0.5};
  if (eDq0.back() > 0.5) hist_lims[1] = eDq0.back() + 0.05;

  // ==========================================================





  // === PLOTTING =============================================

  // --- Setup canvas -----
  TCanvas c1("c1","");
  c1.cd();
  gPad->SetLeftMargin(0.12);
  gPad->SetRightMargin(0.04);
  gPad->SetTopMargin(0.05);

  TH1F *blankHist = new TH1F("", ";#nu [GeV];#frac{d^{2}#sigma}{dEd#Omega} [nb/sr/GeV]", 100, hist_lims[0], hist_lims[1]);
  blankHist->GetYaxis()->SetRangeUser(0,eData_max*1.1);
  blankHist->SetStats(0);
  blankHist->Draw();
  
  
  // --- Plot data -----
  eScatDat->Draw("psame");
  //  if (plotFits) fitGraph->Draw("psame");


  // ==========================================================




  // === PLOTTING =============================================

  // ==========================================================



  // === LEGEND FORMAT ========================================

  TLegend *plotLeg = new TLegend(0.75,0.75,0.9,0.9);
  plotLeg->AddEntry(eScatDat, "(e,e') Data", "p");

  plotLeg->Draw();

  // ==========================================================

  c1.Print(_saving.c_str());

  return 0;
}