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



  // === MAIN EVENT LOOP =================================================

  double eangle, scale;

  for (Long64_t evnt = 0; evnt < neutTree->GetEntries(); ++evnt){

    // --- Command Line Output -----
    neutTree->GetEntry(evnt);
    
    if (verbose){
      if (evnt % (neutTree->GetEntries()/100) == 0){
	std::cout << "\033[1;34m[INFO]\033[0m Event number: " << evnt << std::endl;
      }
    }
    else if (evnt % (neutTree->GetEntries()/10) == 0){
      std::cout << "\033[1;34m[INFO]\033[0m Event number: " << evnt << std::endl;
    }
    

    int pStack = 12;
    if (isCCQE) pStack = 11;
    // --- Check the stack for correct particle numbering
    if (neutpdg_vert[0] != 12 || neutpdg_vert[2] != pStack){
      std::cout << "\033[31;1m[ERROR]\033[0m Lepton particle stack is incorrect. Exiting." << std::endl;
      std::cout << neutpdg_vert[0] << " " << neutpdg_vert[2] << std::endl;
      if (neutELep != neutE_vert[2] && neutEnu_true != neutE_vert[0]){
	std::cout << "\033[31;1m[ERROR].\033[0m Lepton energy is incorrect. Exiting." << std::endl;
        neutSim.setTruth(false);
      }
      neutSim.setTruth(false);
    }
    
    if (((neutpdg_vert[1] != 2112) && (neutpdg_vert[1] != 2212)) ||
	(neutpdg_vert[3] != 2112) && (neutpdg_vert[3] != 2212)){
      std::cout << "\033[31;1m[ERROR]\033[0m Nucleon particle stack is incorrect. Exiting." << std::endl;
      std::cout << neutpdg_vert[1] << " " << neutpdg_vert[3] << std::endl;
      neutSim.setTruth(false);
    }



    // --- Angle calculation ------ 
    
    // [1] is the nucleon in the initial vectors 
    // ORIGINAL METHOD 
    eangle = acos(neutCosLep) * (180/M_PI);
    /*    TLorentzVector nuc4Vec(neutpx_vert[1], neutpy_vert[1], neutpz_vert[1], neutE_vert[1]);
    TVector3 nucVecBoost = nuc4Vec.BoostVector(); // 3-Vec of \beta
    TLorentzVector zAxis(0,0,0.6231,0.6231);
    Double_t origAngD;
    
    
    // UPDATED
    TLorentzVector lep4VecPre(neutpx_vert[0], neutpy_vert[0], neutpz_vert[0], neutEnu_true);
    TLorentzVector lep4VecPost(neutpx_vert[2], neutpy_vert[2], neutpz_vert[2], neutELep);
    TLorentzVector fMomTrans = lep4VecPost - lep4VecPre;
    double fMomQ2 = fMomTrans.Mag2();
    double lepAngle = lep4VecPre.Vect().Angle(lep4VecPost.Vect());
    
    
    TLorentzVector lep4Vec(neutpx_vert[2], neutpy_vert[2], neutpz_vert[2], neutELep);
    lep4Vec.Boost(-nucVecBoost);
    zAxis.Boost(-nucVecBoost);
    TLorentzVector newTest = lep4Vec - zAxis;
    origAngD = lep4Vec.Vect().Angle(zAxis.Vect());
    
    lepAngle = lepAngle * (180/M_PI);*/
    
    scale = neutfScaleFactor;

    if ( angSel-1 < eangle && eangle < angSel+1){
      Float_t dELep = neutEnu_true - neutELep;
      //      neutSim.GetQ0()->Fill(dELep, scale);
      //      neutSim.GetQE()->Fill(dELep, scale);
      neutSim.GetQ0()->Fill(dELep, scale/pow(neutQ2,2));
      neutSim.GetQE()->Fill(dELep, scale/pow(neutQ2,2));
    }    




  }





  return neutSim;

}
