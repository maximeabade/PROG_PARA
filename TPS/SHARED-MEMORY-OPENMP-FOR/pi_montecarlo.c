#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    int num_points = 1000000;
    int num_inside = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();

        #pragma omp for reduction(+:num_inside)
        for (int i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (sqrt(x * x + y * y) <= 1.0) {
                num_inside++;
            }
        }
    }

    double pi = 4.0 * num_inside / num_points;
    printf("Approximation of Pi: %f\n", pi);

    return 0;
}
