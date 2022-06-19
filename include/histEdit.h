#ifndef XSEC_H
#define XSEC_H

#include "TH1F.h"

void xsecScale(TH1F *hist, float angSel, bool isNEUT);
void hist_format(TH1F *hist, float, float);

#endif
