#include <omp.h>
#include <stdio.h>

int main() {
    long start_time;
    long end_time;

    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < i; j++) {

            }
        }
    }
    end_time = omp_get_wtime();

    printf("Threaded time: %d\n", end_time-start_time);

    start_time = omp_get_wtime();
    //#pragma omp parallel
    {
        //#pragma omp for
        for (int i = 0; i < 100000; i++) {
            for (int j = 0; j < i; j++) {

            }
        }
    }
    end_time = omp_get_wtime();

    printf("Unthreaded time: %d\n", end_time-start_time);
}
