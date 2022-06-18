/* ---------------- boringStuff.cc ---------------- *
 * File system checks, along with help function.    *
 * Default script for anything generic... i.e. the  *
 * stuff not to break.                              *
 *                                                  *
 * SOFTWARE REQUIRED:                               *
 * ---> standard C++ libraries                      *
 *                                                  *
 *                       jmmcelwee1@sheffield.ac.uk *
 * -------------------------------- J. McElwee ---- */



// === FILE SYSTEM STUFF =====================================

#include <sys/stat.h>
#include <string>
#include <cmath>

int exist(const std::string &name){
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


double my_round(double x, int precision_digits){
  double power_of_10 = std::pow(10,precision_digits);
  return std::round(x * power_of_10) / power_of_10;
}

// ============================================================



// === COMMAND LINE ===========================================

#include <iostream>
#include "TFile.h"
#include "TTree.h"

void help(){

  std::cout << "\033[1;32m[HELP]\033[37m ===== EB Validations =====" << std::endl;
  std::cout << "\033[1;32m[HELP]\033[0m Syntax: ./basic " << std::endl;
  std::cout << "\033[1;32m[HELP]\033[0m Args: " << std::endl;
  std::cout << "\033[1;32m[HELP]\033[0m" << std::endl;

}

// ============================================================
