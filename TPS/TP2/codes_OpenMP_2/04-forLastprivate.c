#include <omp.h>
#include <stdio.h>

int show(int, int);

int main () { 
 int a = 2;
 int tid;

 omp_set_num_threads(4);

 # pragma omp parallel for firstprivate(a) lastprivate(a) private(tid)
 for (int i = 0; i < 5; i++)
 {
   tid = omp_get_thread_num();
   a++; 
   show(tid,a);
 }

 printf("Master. a: %d\n",a);
 return 0;
}

int show(int id, int a)
{ 
 // ignore this pragma for now
 #pragma omp critical
 {
   printf("Thread %d. a: %d\n",id,a);
 }
 return 0;
}
