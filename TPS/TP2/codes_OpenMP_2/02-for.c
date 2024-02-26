# include <omp.h>
# include <stdio.h>

int main () 
{ 
 int tid;
 omp_set_num_threads(4);

 #pragma omp parallel private(tid)
{ 
  for (int i=0;i<10;i++)
  {
   tid = omp_get_thread_num();
   printf("Thread %d  i = %d\n",tid,i);
  }
}
 return 0;
}

