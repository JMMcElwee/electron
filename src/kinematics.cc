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




// === KINEMATIC CALCULATIONS =================================

#include <math.h>
double q2weight(float Enu_true, float Elep, float angle){
  float dElep, q2;
  dElep = Enu_true - Elep;
  
  q2 = 4*Enu_true*(Enu_true - dElep)*pow(cos(angle/2),2);
  
  return 1/pow(q2,2);
}

double q2test(float Enu_true, float Elep, float angle){
  float dElep, q2;
  dElep = Enu_true - Elep;
  
  q2 = 4*Enu_true*(Enu_true - dElep)*pow(cos(angle/2),2);
  
  return q2;
}

float q3Calc(float energy, float q0, float angle){
  float q2 = 2 * energy * (energy-q0) * (1 - cos(angle*M_PI/180));
  float q3 = sqrt(q2 + pow(q0,2));
  return q3;
}

// ============================================================
