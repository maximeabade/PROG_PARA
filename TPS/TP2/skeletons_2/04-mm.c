/* Parallel Matrix product A*B=C
Juan Angel Lorenzo (jlo@eisti.eu), 2019.
*/
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOL  0.001


double randomFloat();

int main(int argc, char **argv)
{
	long int M, N, P;   /* A[M][N], B[N][P], C[M][P] */
	long int i,j,k;
	float **A, **B, **C, tmp;
	float aval,bval,cval;
	float err, errsq;
	double start_time, run_time;
	int tid,nth; // Number of threads

	nth = 4;

	M = 1000;
	N = 500;
	P = 750;

	aval = 3.0;
	bval = 2.0;

	
	A = (float **)malloc(M*sizeof(float*));
	B = (float **)malloc(N*sizeof(float*));
	C = (float **)malloc(M*sizeof(float*));

	for (i=0;i<M;i++)
	{
	  A[i] = (float *)malloc(N*sizeof(float));
 	  if (A[i] == NULL){
	 	 printf("A[%ld] null\n",i);
		 exit(-1);
          }

	  C[i] = (float *)calloc(P,sizeof(float));
 	  if (C[i] == NULL){
	 	 printf("C[%ld] null\n",i);
		 exit(-1);
          }
	}


	for (i=0;i<N;i++)
	{
	  B[i] = (float *)malloc(P*sizeof(float));
 	  if (B[i] == NULL){
	 	 printf("B[%ld] null\n",i);
		 exit(-1);
          }
	}


	/* Initialise matrices */

	for (i=0; i<M; i++)
		for (j=0; j<N; j++)
			A[i][j] =  aval;

	for (i=0; i<N; i++)
		for (j=0; j<P; j++)
			B[i][j] =  bval;

	omp_set_num_threads(nth);
	
	/* Do the matrix product */

	start_time = omp_get_wtime(); 

	#pragma omp parallel 
	{
		#pragma omp for

			for(i = 0; i < M; i++){
				for(j = 0; j < P; j++){
					tmp = 0.0;
					printf("i : %ld, j : %ld\n", i, j);
					for(k = 0; k < N; k++){
						tmp += A[i][k] * B[k][j];
					}
					C[i][j] = tmp;
				}
			}
 	}

 	run_time = omp_get_wtime() - start_time;
	printf("\nTime to complete the matrix product: %lf\n",run_time);
	
	/* Check results */
	cval = aval*bval*(float)N;	
	errsq = 0.0; 
	for (i=0; i<M; i++)
       	  for (j=0; j<P; j++){
	    err = C[i][j] - cval; 
	    errsq += err * err;
	   // printf("C[%ld][%ld] = %lf\n",i,j,C[i][j]);
	  }
	
	if (errsq > TOL) 
		printf("\n Errors in multiplication: %f\n",errsq);
	else
		printf("\n The result is correct\n");


}


/* Generates a double value between 0 and 1 */
double randomFloat()
{
    double random_value;
    random_value = (double)rand()/RAND_MAX;
    return random_value;
}
