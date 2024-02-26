# include <omp.h>
# include <stdio.h>
# include <stdlib.h>
#include <time.h>
#include <math.h>

int main () { 

 int N, int_aire, int_r;
 float pi, flt_x, flt_y;
 double start_time, run_time;

 N = 10000;

 omp_set_num_threads(4);

 //Start measuring the execution time here 
 start_time = omp_get_wtime();

 //Initialisation des variables
 int_aire = 0;
 int_r = 1;

 //On initialise la fonction rand
 srand(time(NULL));

 #pragma omp parallel 
 {
  #pragma omp for
   //Calcul de l'aire : pour n points on compte ceux qui sont dans le cercle
    for(int i = 0; i < N; i++){   
        //on génère un point aléatoirement
        flt_x = (float)rand()/RAND_MAX;
        flt_y = (float)rand()/RAND_MAX;

        //on regarde si il est dans le cercle
        if(sqrt(pow(flt_x, 2) + pow(flt_y, 2)) <= int_r){
            int_aire++;
        } 
    }
 }

 pi = (float)4 * int_aire / N;

 //Stop measuring the execution time here 
 run_time =  omp_get_wtime() - start_time;
	
 printf("\nPi = %f.\nTime to complete pi calculation: %lf\n",pi, run_time);

 return 0;
}