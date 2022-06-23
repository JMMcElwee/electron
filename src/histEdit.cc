/* ---------------- functions.cc ---------------- *
 * The functions for the basic fitting script.    *
 * This includes the calculations for q3 and the  *
 * Q2 reweight, along with the data and MC        *
 * fitting limits.                                *
 *                                                *
 * SOFTWARE REQUIRED:                             *
 * ---> standard C++ libraries                    *
 *                                                *
 *                     jmmcelwee1@sheffield.ac.uk *
 * ------------------------------ J. McElwee ---- */


#include "TH1F.h"

void xsecScale(TH1F *hist, float angSel, bool isNEUT, double data_max){

  // --- Normal Scaling -----
  float cosBinWidth = sin(angSel*M_PI/180) * 2*M_PI/180 * 2*M_PI;
  hist->Scale(1E38*1E-5); // nb 
  hist->Scale(1/cosBinWidth,"width"); // nb/sr/GeV
  hist->Scale(12); // per nucleon

  hist->Scale(data_max/hist->GetMaximum());
  
  /*  // --- Change NEUT ----- 
  if (isNEUT) {
    hist->Scale(2*(1/pow(137,2))*(1/pow(1.1664E-5,2))*4*M_PI*M_PI); // weak->EM
    hist->Scale(0.5); // CC->NC
  }*/

}


void hist_format(TH1F *hist, float lWid, float lCol){

  hist->SetLineWidth(lWid);
  hist->SetLineColor(lCol);
  hist->Smooth();

}
