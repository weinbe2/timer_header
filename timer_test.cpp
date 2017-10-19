//////////////////////////////////////
// A test demo for timing routines. //
// ESW 2017-10-12                   /////////
// This test code is maintained at         //
// https://github.com/weinbe2/timer_header //
/////////////////////////////////////////////

#include <iostream>
#include <complex>

using namespace std;

#include "timer.h"


int main(int argc, char** argv)
{
  // Iterators.
  int i, j;

  // Timing.
  time_sec_t timer;

  // Length of array.
  const int length = 10000000;

  // Some arrays.
  double* x = new double[length];
  double* y = new double[length];
  double a = 10.0;

  // Time in seconds.
  timer = begin_timing();
  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < length; j++)
    {
      y[j] = y[j] + a*x[j];
    }
  }
  std::cout << "[TIME]: axpy took " << end_timing(&timer) << " seconds.\n";

  delete[] x;
  delete[] y;

  return 0;

}
