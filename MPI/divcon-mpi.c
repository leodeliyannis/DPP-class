#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define TAM 480000000
#define MAX 100

int ehprimo(int num);

int main(int argc, char **argv){
	int j, k, tag=10;
    int i, meurank, procs, parte, ind=0, primos;
    int *vet;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);

    vet = (int *)malloc(sizeof(int) * TAM);
    if (vet == NULL){
        printf("Nao foi\n");
        exit(1);
    }

    if (meurank == 0){
        srand(313);

        for(i=0; i < TAM; i++)
            vet[i] = rand() % MAX;

        for(i = 1; i <= 2; i++){
            MPI_Send(&vet[ind], TAM/2, MPI_INT, i, tag, MPI_COMM_WORLD);
            ind += (TAM/2);
        }
        primos = 0;
        for(i = 1; i <= 2; i++){
            MPI_Recv(&j, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
            primos += j;
        }
        printf("Primos %d\n", primos);       
    }    
    else{
        MPI_Recv(vet, TAM/2, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        j=0;
        for(i=0; i < TAM/2; i++){
            if (ehprimo(vet[i])){
                j++;
                //printf("%d\n", vet[i]);
            }
        }
        MPI_Send(&j, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }

    free(vet);
    MPI_Finalize();
    return (0);
}


int ehprimo(int num){
    int i,c=0;    

    for(i=3; i < num/2+1; i++)
        if ((num % i ) == 0){
            c++;
            break;
        }
    return (c == 0 ? 1 : 0);
}
