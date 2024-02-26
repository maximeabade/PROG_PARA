#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  float N;
  float pi, deltaX;
  double start_time, run_time;
  N = 100.0;
  n = 100;
  deltaX = 1 / N ;
  pi = 0.0;

  omp_set_num_threads(4);

  // Start measuring the execution time here
  start_time = omp_get_wtime();

  #pragma omp parallel
  {
    float local_pi = 0.0;

    #pragma omp for
    for (int i = 0; i < n; i++) {
      double x = (i + 0.5) * deltaX;
      double term = 4.0 / (1.0 + x * x);

      local_pi += term * deltaX;
    }

    #pragma omp critical
    {
      pi += local_pi;
    }
  }

  // Stop measuring the execution time here
  run_time = omp_get_wtime() - start_time;

  printf("\nPi = %f.\nTime to complete pi calculation: %lf\n", pi, run_time);

  return 0;
}
