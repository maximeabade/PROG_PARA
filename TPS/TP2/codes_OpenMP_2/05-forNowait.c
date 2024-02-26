# include <omp.h>
# include <stdio.h>

int main () { 

 int i;
 const int SIZE = 12;
 int A[SIZE];
 int B[SIZE];
 int C[SIZE];
 int D[SIZE];

 omp_set_num_threads(4);

 // Initialisation
 for (i = 0; i < SIZE; i++) 
 {  
  A[i] = 100;
  B[i] = 100;
  C[i] = 100;
  D[i] = 100;
 }

 #pragma omp parallel private(i) shared(A,B,C,D)  
 { 
   #pragma omp for nowait
   for (i = 0; i < SIZE-1; i++)
   {
    B[i] = (A[i] + A[i+1])/2;
   }

   #pragma omp for 
   for (i = 0; i < SIZE;i++)
   {
    D[i] = 1/C[i];
   }
 }

 return 0;
}

