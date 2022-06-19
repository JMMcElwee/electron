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



// === LIMITS FOR POlY FIT ====================================

void MClims(float enSel, float angSel, float *ERange){
  
  if (enSel < 0.321 && enSel > 0.319 && angSel < 40){
    ERange[0] = 0.044;
    ERange[1] = 0.089;
  }
  else if (enSel < 0.321 && enSel > 0.319 && angSel > 40){
    ERange[0] = 0.0415;
    ERange[1] = 0.130;
  }
  else if (enSel > 0.360 && enSel < 0.362 && angSel > 40){
    ERange[0] = 0.050;
    ERange[1] = 0.132;
  }
  else if (enSel > 0.399 && enSel < 0.4001 && angSel < 40){
    ERange[0] = 0.042;
    ERange[1] = 0.103;
  }
  else if (enSel > 0.400 && enSel < 0.402 && angSel > 40){
    ERange[0] = 0.058;
    ERange[1] = 0.150;
  }
  else if (enSel > 0.439 && enSel < 0.441 && angSel > 40){
    ERange[0] = 0.062;
    ERange[1] = 0.173;
  }
  else if (enSel > 0.479 && enSel < 0.481 && angSel < 40){
    ERange[0] = 0.046;
    ERange[1] = 0.122;
  }
  else if (enSel > 0.479 && enSel < 0.481 && angSel > 40){
    ERange[0] = 0.085;
    ERange[1] = 0.180;
  }
  else if (enSel > 0.499 && enSel < 0.501 && angSel > 40){
    ERange[0] = 0.083;
    ERange[1] = 0.200;
  }
  else if (enSel > 0.518 && enSel < 0.520 && angSel > 40){
    ERange[0] = 0.091;
    ERange[1] = 0.191;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel < 40){
    ERange[0] = 0.048;
    ERange[1] = 0.140;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel > 40 && angSel < 130){
    ERange[0] = 0.115;
    ERange[1] = 0.218;
  }
  else if (enSel > 0.559 && enSel < 0.561 && angSel > 130){
    ERange[0] = 0.273;
    ERange[1] = 0.365;
  }
  else if (enSel > 0.619 && enSel < 0.621 && angSel < 40){
    ERange[0] = 0.073;
    ERange[1] = 0.150;
  }
  else if (enSel > 0.619 && enSel < 0.621 && angSel > 40){
    ERange[0] = 0.134;
    ERange[1] = 0.236;
  }
  else if (enSel > 0.679 && enSel < 0.681 && angSel < 40){
    ERange[0] = 0.065;
    ERange[1] = 0.160;
  }
  else if (enSel > 0.679 && enSel < 0.681 && angSel > 40){
    ERange[0] = 0.150;
    ERange[1] = 0.278;
  }
  else if (enSel > 0.699 && enSel < 0.701 && angSel < 40){
    ERange[0] = 0.048;
    ERange[1] = 0.145;
  }
  else if (enSel > 0.729 && enSel < 0.731 && angSel < 40){
    ERange[0] = 0.079;
    ERange[1] = 0.185;
  }
  else if (enSel > 0.736 && enSel < 0.738 && angSel < 40){
    ERange[0] = 0.075;
    ERange[1] = 0.187;
  }
  else if (enSel > 0.879 && enSel < 0.881 && angSel < 40){
    ERange[0] = 0.100;
    ERange[1] = 0.212;
  }
  else if (enSel > 0.960 && enSel < 0.962 && angSel < 40){
    ERange[0] = 0.142;
    ERange[1] = 0.250;
  }
  else if (enSel > 1.079 && enSel < 1.081 && angSel < 40){
    ERange[0] = 0.120;
    ERange[1] = 0.260;
  }
  else if (enSel > 1.107 && enSel < 1.109 && angSel < 40){
    ERange[0] = 0.180;
    ERange[1] = 0.305;
  }
  else if (enSel > 1.199 && enSel < 1.201 && angSel < 40){
    ERange[0] = 0.157;
    ERange[1] = 0.310;
  }
  else if (enSel > 1.299 && enSel < 1.301 && angSel < 12.5){
    ERange[0] = 0.047;
    ERange[1] = 0.115;
  }
  else if (enSel > 1.299 && enSel < 1.301 && angSel > 12.5){
    ERange[0] = 0.052;
    ERange[1] = 0.122;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel < 12.5){
    ERange[0] = 0.055;
    ERange[1] = 0.131;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel > 30){
    ERange[0] = 0.250;
    ERange[1] = 0.435;
  }
  else if (enSel > 1.499 && enSel < 1.501 && angSel > 12.5){
    ERange[0] = 0.065;
    ERange[1] = 0.145;
  }
  else if (enSel > 1.500 && enSel < 1.502 && angSel > 36){
    ERange[0] = 0.345;
    ERange[1] = 0.492;
  }
  else if (enSel > 1.649 && enSel < 1.651 && angSel < 12){
    ERange[0] = 0.045;
    ERange[1] = 0.140;
  }
  else if (enSel > 1.649 && enSel < 1.651 && angSel > 12){
    ERange[0] = 0.060;
    ERange[1] = 0.150;
  }
  else if (enSel > 1.929 && enSel < 1.931 && angSel < 17){
    ERange[0] = 0.110;
    ERange[1] = 0.240;
  }
  else if (enSel > 1.929 && enSel < 1.931 && angSel > 17){
    ERange[0] = 0.130;
    ERange[1] = 0.280;
  }
  else if (enSel > 1.999 && enSel < 2.001 && angSel < 17){
    ERange[0] = 0.100;
    ERange[1] = 0.225;
  }
  else if (enSel > 2.014 && enSel < 2.016 && angSel > 17){
    ERange[0] = 0.500;
    ERange[1] = 0.710;
  }
  else if (enSel > 2.019 && enSel < 2.021 && angSel < 17){
    ERange[0] = 0.110;
    ERange[1] = 0.235;
  }
  else if (enSel > 2.019 && enSel < 2.021 && angSel > 17){
    ERange[0] = 0.190;
    ERange[1] = 0.340;
  }
  else if (enSel > 2.129 && enSel < 2.131 && angSel < 17){
    ERange[0] = 0.125;
    ERange[1] = 0.270;
  }
  else if (enSel > 2.129 && enSel < 2.131 && angSel > 17){
    ERange[0] = 0.175;
    ERange[1] = 0.325;
  }
  else if (enSel > 2.499 && enSel < 2.501 && angSel < 17){
    ERange[0] = 0.150;
    ERange[1] = 0.310;
  }
  else if (enSel > 2.699 && enSel < 2.701 && angSel < 17){
    ERange[0] = 0.220;
    ERange[1] = 0.350;
  }
  else if (enSel > 3.187 && enSel < 3.189 && angSel > 17){
    ERange[0] = 0.345;
    ERange[1] = 0.492;
  }
  else if (enSel > 3.594 && enSel < 3.596 && angSel < 17){
    ERange[0] = 0.350;
    ERange[1] = 0.500;
  }
  else if (enSel > 3.594 && enSel < 3.596 && angSel > 17){
    ERange[0] = 0.560;
    ERange[1] = 0.860;
  }

}
