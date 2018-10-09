#include <stdio.h>
#include <omp.h>

int main () {
    int i, f;
    int a[20], b[20];
    
    for(i = 0; i < 20; i++){
        b[i] = (i < 2) ? i : b[i-1] + b[i-2];
    }
    
    /*
    #pragma omp parallel private (f)
    {
        f = 7;
        #pragma omp for
        for(i=0; i<20; i++)
            a[i] = b[i] + f * (i+1);
    }
    */
    /* outra forma */
    f= 7;
    #pragma omp parallel for firstprivate(f)
    for(i=0; i<20; i++)
        a[i] = b[i] + f * (i+1);
    
    
    for(i = 0; i < 20; i++){
        printf("[%d] = %d\n", i, a[i]);
    }
    
    return 0;
}

