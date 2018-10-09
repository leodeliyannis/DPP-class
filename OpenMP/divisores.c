#include <stdio.h>
#include <stdlib.h>

#define MAXNUMBER 100000
#define SEED      313
#define TAM       500000

int main(){
    int i, j, aux, sum=0;
    int vet[TAM];
    
    srand(SEED);
    for(i=0; i< TAM; i++)
        vet[i] = rand() % MAXNUMBER + 1;
    
    for(i=0; i < TAM; i++){
        aux = 0;
        for(j=1; j <= vet[i]; j++)
            if (vet[i] % j == 0)
                aux++;
        sum += aux;
    }
    printf("A soma dos divisores de todos os numeros no vetor eh: %d\n", sum);
    
    return 0;
}
