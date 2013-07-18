/*
 * scrm is an implementation of the Sequential-Coalescent-with-Recombination Model.
 * 
 * Copyright (C) 2013 Paul R. Staab, Sha (Joe) Zhu and Gerton Lunter
 * 
 * This file is part of scrm.
 * 
 * scrm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "fastfunc.h"
#include "mersenne_twister.h"


double speedtest(int oper, double rate, double growth, double limit) {

  int i;
  double x = 1.0;
  float xf = 1.0;
  double y = 0.999;
  float yf = 0.0;
  double z = 0.0;
  float zf = 0.0;

  class MersenneTwister rg;
  class FastFunc ff;

  for (i=0; i<100000000; i++) {
    x += 1e-8;
    xf = float(x);
    y = x;
    switch(oper) {
    case 0: break;
    case 1: y = x+y; break;
    case 2: y = x/x; break;
    case 3: y = x*x; break;
    case 4: y = log(x); break;
    case 5: yf = logf(xf); break;
    case 6: y = ff.fastlog(x); break;
    case 7: y = exp(x); break;
    case 8: y = ff.fastexp_lo(x); break;
    case 9: y = rg.sample(); break;
    case 10: y = rg.sampleExpo( 1.0 ); break;
    case 11: y = rg.sampleExpoLimit( 1.0, 0.1 ); break;
    default: y = rg.sampleExpoExpoLimit( rate, growth, limit ); break;
    }
    z += y;
    zf += yf;
  }
  return z + zf;  // to avoid optimizing everything away
}


void testlog() {

  const int CASES=4;
  const double epsilon=1e-7;
  const double x[CASES] = {0.0, 1.0, 2.0, 3.0};
  class FastFunc ff;
  int i;
  printf("x\t\tlog\t\tfastlog\n");
  for (i=0; i<CASES; i++) {
    printf("%1.9f\t%1.9f\t%1.9f\n", x[i], log(x[i]), ff.fastlog(x[i]));
  }
  double maxdiff = 0.0;
  for (i=0; i<(int)(2+1.0/epsilon); i++) {
    double y = 0.5 + epsilon*i;
    double z1 = log(y);
    double z2 = ff.fastlog(y);
    double diff = fabs(z1-z2);
    if (diff > maxdiff) {
      maxdiff = diff;
    }
  }
  std::cout << "max absolute difference across [0.5-1.5] = " << maxdiff << std::endl;
}


int main(int argc, char** argv) {
  
  const int CASES=10;
  const int LLTEST=12;
  const char* testnames[LLTEST+1] = {"nop\t","+\t","/\t","*\t","log()\t","logf()\t","fastlog()","exp()\t","fastexp()","raw sample","sample(1.0)","sample(1.0,0.1)","sample\t"};
  const double rate[CASES] =   {1.0,      1.0, 1.0, 1.0,      1.0, 1.0, 10.0, 1.0,      1.0,  1.0};
  const double growth[CASES] = {0.0,      0.0, 0.0, 1.0,      1.0, 1.0, 10.0, -1.0,     -1.0, -1.0};
  const double limit[CASES] =  {INFINITY, 1.0, 0.1, INFINITY, 1.0, 0.1, 0.1,  INFINITY, 1.0,  0.1};

  class MersenneTwister rg;

  testlog();

  printf("Test\t\tRate\tGrowth\tLimit\tTime\n");
  for (int i=0; i<LLTEST + CASES; i++) {
    clock_t start = clock(), diff;
    double r = i>=LLTEST ? rate[i-LLTEST] : 0, g = i>=LLTEST ? growth[i-LLTEST] : 0, l = i>=LLTEST ? limit[i-LLTEST] : 0;
    speedtest(i, r, g, l);
    diff = clock() - start;
    printf("%s\t%1.4f\t%1.4f\t%1.4f\t%ld\n",testnames[i>=LLTEST ? LLTEST : i],r,g,l,diff * 1000 / CLOCKS_PER_SEC);
  }
  return 0;
}

