#include <stdio.h>
#include <omp.h>
int main () {
   int nthreads, tid; 

   #pragma omp parallel private(nthreads, tid)
   { // Obtem e escreve thread­id
       tid = omp_get_thread_num();
       printf("Hello World from thread = %d\n", tid);                          
       if (tid == 0){   // apenas o master thread faz isto
           nthreads = omp_get_num_threads();
           printf("Number of threads = %d\n", nthreads);
       }
    } /* Todos os theards juntam­se no master */
    return 0;
}
