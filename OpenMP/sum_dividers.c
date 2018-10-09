#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define TAM 100000
#define MAX 100000

int countDivs(int n){
    int i, ans = 0;
    for(i = 1; i*i <= n; i++)
        if(n%i == 0)
            ans += (i*i != n) ? 2 : 1;
    return ans;
}

int main(){
    int i, sum = 0;
    printf("Now generating %d random numbers.\n", TAM);
    srand(313);
    for(i = 0; i < TAM; i++)
        sum += countDivs(rand()%MAX);
    printf("Sum of all dividers = %d\n", sum);
    return 0;
}
