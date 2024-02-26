# include <omp.h>
# include <stdio.h>

int main () { 

 int i,id;
 const int SIZE = 12;
 int A[SIZE];

 omp_set_num_threads(4);

 #pragma omp parallel 
 {
  #pragma omp for private(id)
  for (i=0; i<SIZE;i++)
  {
   id=omp_get_thread_num();
   A[i] = id;
  }
 }

 for (i=0; i<SIZE; i++) { 
   printf(" | %d",A[i]); 
 }
   printf(" | \n"); 

 return 0;
}

