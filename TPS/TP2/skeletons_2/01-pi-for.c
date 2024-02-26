# include <omp.h>
# include <stdio.h>
# include <stdlib.h>

int main () { 

 int N, deltaX;
 float pi;
 double start_time, run_time;

 N = 10;
 deltaX = 1/N;

 pi = 0.0;

 omp_set_num_threads(4);

 //Start measuring the execution time here 
 start_time = omp_get_wtime();

 #pragma omp parallel 
 {
  #pragma omp for
   for (int i=0;i<N;i++){
    pi += deltaX * (4 / (1 + (i*deltaX + deltaX/2.0) * (i*deltaX + deltaX/2.0)));
   }
 }

 //Stop measuring the execution time here 
 run_time =  omp_get_wtime() - start_time;
	
 printf("\nPi = %f.\nTime to complete pi calculation: %lf\n",pi, run_time);

 return 0;
}