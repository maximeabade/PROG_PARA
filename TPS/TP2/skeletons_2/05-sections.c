#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOL  0.001

int main(int argc, char **argv)
{
	long int N;
	long int i;
	float *A, sum, product;
	float aval;
	double start_time, run_time;
	int tid,nth; // Number of threads

	nth = 2;
    sum = 0.0;
    product = 1.0;

	N = 10;

	aval = 2.0;

	
	A = (float *)malloc(N*sizeof(float));

	for (i=0;i<N;i++)
	{
	  A[i] = aval;
	}

	omp_set_num_threads(nth);
	

	start_time = omp_get_wtime(); 

	#pragma omp parallel sections
	{
		#pragma omp section
            for(i = 0; i < N; i++){
                sum += A[i];
            }
        #pragma omp section
            for(i = 0; i < N; i++){
                product *= A[i];
            }
 	}

 	run_time = omp_get_wtime() - start_time;
	printf("\nTime to complete the matrix product: %lf\n",run_time);
    printf("+ : %f, * : %f\n", sum, product);

}

