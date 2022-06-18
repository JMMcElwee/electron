#ifndef BORINGSTUFF_H
#define BORINGSTUFF_H



// === FILE SYSTEM STUFF =====================================

#include <sys/stat.h>
#include <string>
#include <cmath>

int exist(const std::string &name);
double my_round(double x, int precision_digits);

// ============================================================


// === COMMAND LINE ===========================================

#include "TTree.h"

void help();
void fileRead(std::string infile, std::string type, TTree *tree, bool verbose);
void readData(std::string infile, TTree *tree, bool verbose);

// ============================================================


#endif
