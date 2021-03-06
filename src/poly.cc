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
#include "limits.h"
#include "classes.h"
#include "sims.h"
#include "histEdit.h"
#include "kinematics.h"



int main(int argc, char *argv[]){


  // === COMMAND LINE FLAGS ===================================

  // --- Default Files -----
  std::string eDataName = "./data/12C.root";

  std::string eNEUT = "";
  bool isNEUT = false;


  // --- Default values -----
  float enSel = 0.620;
  float angSel = 36;

  bool verbose = false;  


  // --- Fit Defaults -----
  std::string polFitHist = "5";
  std::string polFitData = "5";

  bool plotFits = false;


  // --- Read command line -----
  int argCount = 0;
  int opt;
  while ((opt = getopt(argc, argv, ":hvfE:a:d:p:P:n:")) != -1){
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
      case 'f':
	plotFits = true;
	break;
      case 'P':
	polFitHist = optarg;
	break;
      case 'p':
	polFitData = optarg;
	break;
      case 'n':
	isNEUT = true;
	eNEUT = optarg;
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

  if(isNEUT && !exist(eNEUT)){
    std::cout << "\033[31;1m[ERROR]\033[0m No input NEUT QE data; please supply NEUT electron file." << std::endl;
    return 0;
  }

  // ==========================================================




  // === SAVE INFORMATION =====================================

  std::cout << "\033[1;34m[INFO]\033[0m Electron data selected with theta: " << angSel
	    << " and energy: " << enSel << "." << std::endl;
  std::string _directory = "./plots/";
  std::string _saving = _directory + "e_"
    + std::to_string(static_cast<int>(enSel*1000)) + "_"
    + std::to_string(static_cast<int>(angSel));

  if (isNEUT) _saving = _saving + "_NEUT";

  if (plotFits) _saving += "_fits";

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


  // --- Select fitting region manually -----
  int binRange[2] = {0,0};
  if (plotFits) dataLims(enSel, angSel, binRange);

  if (verbose && plotFits){
    std::cout << "\033[1;34m[INFO]\033[0m The fitting parameters selected are:" << std::endl;
    std::cout << "DATA ->" << "\t \033[1m" << binRange[0] << " " << binRange[1]
	      << "\033[0m" << std::endl;
  }

  
  // --- Fitting data -----
  std::vector<float>fitVectorX, fitVectorY;
  for (int evnt = 0; evnt < eDq0.size(); ++evnt){
    if (evnt >= binRange[0] && evnt <= binRange[1]){
      fitVectorX.push_back(eDq0.at(evnt));
      fitVectorY.push_back(eDxsec.at(evnt));
    }
  }
  std::string someFitHist = "pol" + polFitHist;
  std::string someFitData = "pol" + polFitData; 
  

  // --- QE Data Graph ------
  TGraphErrors *eScatDat = new TGraphErrors(eDq0.size(), &eDq0[0], &eDxsec[0], 0, &eDerr[0]);
  TGraph *fitGraph = new TGraph(fitVectorX.size(), &fitVectorX[0], &fitVectorY[0]);
  eScatDat->SetMarkerStyle(2);
  eScatDat->SetMarkerSize(1);


  // --- Find maxima ------
  double *yvalues = eScatDat->GetY();
  double *xvalues = eScatDat->GetX();
  int max_location = TMath::LocMax(eScatDat->GetN(), yvalues);
  double eData_max = yvalues[max_location];
  float eData_maxX = xvalues[max_location];


  // --- Set Monte Carlo limits -----
  float enRange[2] = {0,0};
  if (isNEUT) MClims(enSel, angSel, enRange);



  // ==========================================================



  // === PROCESS DATA =========================================

  float hist_lims[2] = {0,0.5};
  //  if (eDq0.back() > 0.5) hist_lims[1] = eDq0.back() + 0.05;
  hist_lims[1] = eDq0.back() + 0.05;

  Simulation neutSim;
  if (isNEUT) neutSim = neut(eNEUT, angSel, hist_lims, enRange, false, verbose);

  // ==========================================================



  // === HISTOGRAM PREP =======================================

  // --- NEUT ----
  if (isNEUT){
    xsecScale(neutSim.GetQ0(), angSel, isNEUT, eData_max);
    hist_format(neutSim.GetQ0(), 1, 4);

    xsecScale(neutSim.GetQE(), angSel, isNEUT, eData_max);
    hist_format(neutSim.GetQE(), 1, 2);
  }


  // ==========================================================





  // === FITTING ==============================================

  if (plotFits){

    // --- Fit electron data -----
    std::cout << "\033[1m=== Data Fit ===========================\033[0m"
	      << std::endl;
    fitGraph->Fit(someFitData.c_str(),"FM","");
    fitGraph->GetFunction(someFitData.c_str())->SetLineColor(kBlack);
    std::cout << "\033[1m========================================\033[0m" 
	      << std::endl;


    // --- Fit NEUT -----
    if (isNEUT){
      std::cout << "==============================================\n\033[1mHist Fit NEUT\033[0m"
		<< std::endl;
      neutSim.GetQ0()->Fit(someFitHist.c_str(),"FM","",enRange[0],enRange[1]);
      neutSim.GetQ0()->GetFunction(someFitHist.c_str())->SetLineColor(kBlue);  
      std::cout << "==============================================" << std::endl;
    }
  
  }


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
  if (plotFits) fitGraph->Draw("psame");


  // --- Plot MC (if available) -----
  if (isNEUT){ 
    //   neutSim.GetQE()->Draw("histSAME");
    neutSim.GetQ0()->Draw("histSAME");
    if (plotFits) neutSim.GetQ0()->GetFunction(someFitHist.c_str())->Draw("same");
  } 


  // ==========================================================




  // === CALCULATE EB SHIFT ===================================

  float maxData,maxNEUT,
    shiftNEUT,
    q3;

  char printMaxNEUT[40],
    printQ3[40];

  // --- Get Maxima ----- 
  if (plotFits) {
    maxData = fitGraph->GetFunction(someFitData.c_str())->GetMaximumX();
    q3 = q3Calc(enSel,maxData,angSel);
    sprintf(printQ3, "q3 = %0.4f", q3);

    if (isNEUT) {
      maxNEUT = neutSim.GetQ0()->GetFunction(someFitHist.c_str())->GetMaximumX();
      shiftNEUT = maxData - maxNEUT;
      sprintf(printMaxNEUT, "NEUT = %0.4f", shiftNEUT);
    }

  }

  // ==========================================================



  // === GRAPH FORMATTING =====================================

  float position = 0.8;

  // --- Set graph printing -----
  if (plotFits){    
    TText *q3Text = new TText(0.5,position,printQ3);
    q3Text->SetNDC();
    q3Text->SetTextSize(20);
    q3Text->SetTextFont(43);
    q3Text->Draw();

    if (isNEUT){
      position -= 0.05;
      TText *neutText = new TText(0.5,position,printMaxNEUT);
      neutText->SetNDC();
      neutText->SetTextSize(20);
      neutText->SetTextFont(43);
      neutText->Draw();
    }

  }


  // ==========================================================




  // === FIT PARAMETERS =======================================

  if (plotFits){
    std::ofstream outputq3;
    outputq3.open(_saveq3.c_str());
    outputq3 << std::setprecision(4) <<  enSel << "\t" << angSel << "\t"
	     << q3 << "\t"; 
    
    if (isNEUT) {
      outputq3 << std::setprecision(4) << "\t" << shiftNEUT;
    }

    outputq3 << "\n";

    outputq3.close();  
  }

  // ==========================================================



  // === LEGEND FORMAT ========================================

  TLegend *plotLeg = new TLegend(0.795,0.78,0.945,0.93);
  plotLeg->AddEntry(eScatDat, "(e,e') Data", "p");

  if (isNEUT) plotLeg->AddEntry(neutSim.GetQ0(), "NEUT", "l");

  plotLeg->Draw();

  // ==========================================================


  c1.Print(_saving.c_str());

  return 0;
}
