//////////////////////////////////////
// A test demo for timing routines. //
// ESW 2017-10-12                   //
//////////////////////////////////////

#include "stdio.h"
#include "stdlib.h"

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
  double* x = (double*)malloc(sizeof(double)*length);
  double* y = (double*)malloc(sizeof(double)*length);
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
  printf("[TIME]: axpy took %f seconds.\n", end_timing(&timer));

  free(x);
  free(y);

  return 0;

}
