/* ---------------- basic.cc ---------------- *
 * This contains all of the code for the neut *
 * analysis of the EB work.                   *
 *                                            *
 * SOFTWARE REQUIRED:                         *
 * ---> ROOT                                  *
 * ---> standard C++ libraries                *
 * ---> classes.h                             *
 *                                            *
 *                 jmmcelwee1@sheffield.ac.uk *
 * -------------------------- J. McElwee ---- */


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

#include "classes.h"

Simulation neut(std::string eNEUT, float angSel, float hist_lims[2], float enRange[2], bool isCCQE, bool verbose){


  // === SETUP CLASS =====================================================
 
  Simulation neutSim;

  // --- Histogram sets ----- 
  TH1F *neutq0 = new TH1F("", ";#nu [GeV];#frac{d^{2}#sigma}{dEd#Omega} [nb/sr/GeV]",80,hist_lims[0],hist_lims[1]);
  TH1F *eNEUTQE = new TH1F("", ";#nu [GeV];#frac{d^{2}#sigma}{dEd#Omega} [nb/sr/GeV]",80,hist_lims[0],hist_lims[1]);
  TH1F *eMissNEUT = new TH1F("", ";E_{miss} [GeV]", 100,-0.02,0.1);

  neutSim.setQ0(neutq0);
  neutSim.setQE(eNEUTQE);

  // --- Sim check -----
  neutSim.setTruth(true);

  // =====================================================================  



  // === FILE READ =======================================================

  // --- Load files -----
  std::cout << "\033[34;1m[INFO]\033[0m Reading in NEUT QE Mode flattree:" << std::endl;
  std::cout << "\t \033[1m" << eNEUT << "\033[0m" << std::endl;
  TFile neutFile(eNEUT.c_str(),"READ");
  TTree *neutTree = 0;
  neutFile.GetObject("FlatTree_VARS", neutTree);
  if (verbose){
    neutFile.ls();
    std::cout << "\033[34;1m[INFO]\033[0m Example event:" << std::endl;
    neutTree->Show(0);
  }


  // --- NEUT Branch Addresses -----
  Int_t neutMode;
  Int_t neutnfsp = 100;
  double neutfScaleFactor;
  Float_t neutELep, neutEnu_true, neutCosLep, neutQ2;

  neutTree->SetBranchAddress("Mode", &neutMode);
  neutTree->SetBranchAddress("nfsp", &neutnfsp);
  neutTree->SetBranchAddress("ELep", &neutELep);
  neutTree->SetBranchAddress("Enu_true", &neutEnu_true);
  neutTree->SetBranchAddress("CosLep", &neutCosLep);
  neutTree->SetBranchAddress("Q2", &neutQ2);
  neutTree->SetBranchAddress("fScaleFactor", &neutfScaleFactor);
  

  Int_t neutninitp = 100;
  Int_t neutnvertp = 100;
  Int_t neutpdg_fs[neutnfsp];
  Int_t neutpdg_vert[neutnvertp];
  Float_t neutpx_fs[neutnfsp], neutpy_fs[neutnfsp], neutpz_fs[neutnfsp], neutE_fs[neutnfsp],
    neutpx_init[neutninitp], neutpy_init[neutninitp], neutpz_init[neutninitp], neutE_init[neutninitp],
    neutpx_vert[neutnvertp], neutpy_vert[neutnvertp], neutpz_vert[neutnvertp], neutE_vert[neutnvertp];

  neutTree->SetBranchAddress("ninitp", &neutninitp);
  neutTree->SetBranchAddress("nvertp", &neutnvertp);
  neutTree->SetBranchAddress("pdg", neutpdg_fs);
  neutTree->SetBranchAddress("pdg_vert", neutpdg_vert);
  neutTree->SetBranchAddress("px_init", neutpx_init);
  neutTree->SetBranchAddress("py_init", neutpy_init);
  neutTree->SetBranchAddress("pz_init", neutpz_init);
  neutTree->SetBranchAddress("E_init", neutE_init);
  neutTree->SetBranchAddress("px_vert", neutpx_vert);
  neutTree->SetBranchAddress("py_vert", neutpy_vert);
  neutTree->SetBranchAddress("pz_vert", neutpz_vert);
  neutTree->SetBranchAddress("E_vert", neutE_vert);
  neutTree->SetBranchAddress("px", neutpx_fs);
  neutTree->SetBranchAddress("py", neutpy_fs);
  neutTree->SetBranchAddress("pz", neutpz_fs);    
  neutTree->SetBranchAddress("E", neutE_fs);
  
  // ====================================================================




  return neutSim;

}
