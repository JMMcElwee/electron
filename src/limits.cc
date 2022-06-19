/* ----------------- limits.cc ------------------ *
 * Limits for all of the polynomial fits. This    *
 * includes all data and Monte Carlo sims.        *
 *                                                *
 * SOFTWARE REQUIRED:                             *
 * ---> standard C++ libraries                    *
 *                                                *
 *                     jmmcelwee1@sheffield.ac.uk *
 * ------------------------------ J. McElwee ---- */


#include <iostream>

// === LIMITS FOR DATA FIT ====================================

void dataLims(float enSel, float angSel, int *binRange){
  
  if (enSel < 0.321 && enSel > 0.319 && angSel < 40){
    binRange[0] = 1;
    binRange[1] = 9;
  }
  else if (enSel < 0.321 && enSel > 0.319 && angSel > 40){
    binRange[0] = 6;
    binRange[1] = 23;
  }
  else if (enSel > 0.360 && enSel < 0.362 && angSel > 40){
    binRange[0] = 7;
    binRange[1] = 21;
  }
  else if (enSel > 0.399 && enSel < 0.4001 && angSel < 40){
    binRange[0] = 2;
    binRange[1] = 15;
  }
  else if (enSel > 0.400 && enSel < 0.402 && angSel > 40){
    binRange[0] = 10;
    binRange[1] = 24;
  }
  else if (enSel > 0.439 && enSel < 0.441 && angSel > 40){
    binRange[0] = 10;
    binRange[1] = 30;
  }
  else if (enSel > 0.479 && enSel < 0.481 && angSel < 40){
    binRange[0] = 5;
    binRange[1] = 15;
  }
  else if (enSel > 0.479 && enSel < 0.481 && angSel > 40){
    binRange[0] = 13;
    binRange[1] = 31;
  }
  else if (enSel > 0.499 && enSel < 0.501 && angSel > 40){
    binRange[0] = 10;
    binRange[1] = 23;
  }
  else if (enSel > 0.518 && enSel < 0.520 && angSel > 40){
    binRange[0] = 8;
    binRange[1] = 19;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel < 40){
    binRange[0] = 2;
    binRange[1] = 11;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel > 40 && angSel < 130){
    binRange[0] = 8;
    binRange[1] = 20;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel > 130){
    binRange[0] = 11;
    binRange[1] = 17;
  }
  else if (enSel > 0.619 && enSel < 0.621 && angSel < 40){
    binRange[0] = 3;
    binRange[1] = 13;
  }
  else if (enSel > 0.619 && enSel < 0.621 && angSel > 40){
    binRange[0] = 9;
    binRange[1] = 21;
  }
  else if (enSel > 0.679 && enSel < 0.681 && angSel < 40){
    binRange[0] = 4;
    binRange[1] = 15;
  }
  else if (enSel > 0.679 && enSel < 0.681 && angSel > 40){
    binRange[0] = 10;
    binRange[1] = 22;
  }
  else if (enSel > 0.699 && enSel < 0.701 && angSel < 40){
    binRange[0] = 0;
    binRange[1] = 4;
  }
  else if (enSel > 0.729 && enSel < 0.731 && angSel < 40){
    binRange[0] = 4;
    binRange[1] = 15;
  }
  else if (enSel > 0.736 && enSel < 0.738 && angSel < 40){
    binRange[0] = 4;
    binRange[1] = 15;
  }
  else if (enSel > 0.879 && enSel < 0.881 && angSel < 40){
    binRange[0] = 1;
    binRange[1] = 4;
  }
  else if (enSel > 0.960 && enSel < 0.962 && angSel < 40){
    binRange[0] = 6;
    binRange[1] = 20;
  }
  else if (enSel > 1.079 && enSel < 1.081 && angSel < 40){
    binRange[0] = 0;
    binRange[1] = 5;
  }
  else if (enSel > 1.107 && enSel < 1.109 && angSel < 40){
    binRange[0] = 5;
    binRange[1] = 21;
  }
  else if (enSel > 1.199 && enSel < 1.201 && angSel < 40){
    binRange[0] = 2;
    binRange[1] = 4;
  }
  else if (enSel > 1.299 && enSel < 1.301 && angSel < 12.5){
    binRange[0] = 0;
    binRange[1] = 5;
  }
  else if (enSel > 1.299 && enSel < 1.301 && angSel > 12.5){
    binRange[0] = 1;
    binRange[1] = 8;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel < 12.5){
    binRange[0] = 0;
    binRange[1] = 6;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel > 30){
    binRange[0] = 1;
    binRange[1] = 6;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel > 12.5){
    binRange[0] = 0;
    binRange[1] = 9;
  }
  else if (enSel > 1.500 && enSel < 1.502 && angSel > 36){
    binRange[0] = 10;
    binRange[1] = 25;
  }
  else if (enSel > 1.649 && enSel < 1.651 && angSel < 12){
    binRange[0] = 0;
    binRange[1] = 9;
  }
  else if (enSel > 1.649 && enSel < 1.651 && angSel > 12){
    binRange[0] = 1;
    binRange[1] = 10;
  }
  else if (enSel > 1.929 && enSel < 1.931 && angSel < 17){
    binRange[0] = 5;
    binRange[1] = 13;
  }
  else if (enSel > 1.929 && enSel < 1.931 && angSel > 17){
    binRange[0] = 7;
    binRange[1] = 16;
  }
  else if (enSel > 1.999 && enSel < 2.001 && angSel < 17){
    binRange[0] = 7;
    binRange[1] = 20;
  }
  else if (enSel > 2.014 && enSel < 2.016 && angSel > 17){
    binRange[0] = 1;
    binRange[1] = 8;
  }
  else if (enSel > 2.019 && enSel < 2.021 && angSel < 17){
    binRange[0] = 1;
    binRange[1] = 11;
  }
  else if (enSel > 2.019 && enSel < 2.021 && angSel > 17){
    binRange[0] = 9;
    binRange[1] = 19;
  }
  else if (enSel > 2.129 && enSel < 2.131 && angSel < 17){
    binRange[0] = 5;
    binRange[1] = 15;
  }
  else if (enSel > 2.129 && enSel < 2.131 && angSel > 17){
    binRange[0] = 7;
    binRange[1] = 16;
  }
  else if (enSel > 2.499 && enSel < 2.501 && angSel < 17){
    binRange[0] = 13;
    binRange[1] = 28;
  }
  else if (enSel > 2.699 && enSel < 2.701 && angSel < 17){
    binRange[0] = 17;
    binRange[1] = 33;
  }
  else if (enSel > 3.187 && enSel < 3.189 && angSel > 17){
    binRange[0] = 0.345;
    binRange[1] = 0.492;
  }
  else if (enSel > 3.594 && enSel < 3.596 && angSel < 17){
    binRange[0] = 20;
    binRange[1] = 25;
  }
  else if (enSel > 3.594 && enSel < 3.596 && angSel > 17){
    binRange[0] = 20;
    binRange[1] = 25;
  }

}

// ============================================================
