#ifndef SIMS_H
#define SIMS_H


// === COMMAND LINE ===========================================

#include <string>
#include <vector>
#include "TH1F.h"
#include "classes.h"


Simulation neut(std::string eNEUT, float angSel, float hist_lims[2], float enRange[2], bool isCCQE, bool verbose);
//Simulation genie(std::string eGENIE, float angSel, float hist_lims[2], bool verbose);
//Simulation nuwro(std::string eNUWRO, float angSel, float hist_lims[2], bool verbose);


// ============================================================


#endif
