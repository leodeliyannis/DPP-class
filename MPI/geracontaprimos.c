#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
 
#define TAM 120000
#define MAX 100000
 
int GeraPrimos(int num);
 
int main(int argc, char **argv){
    int j, k;
    int i, meurank, procs, parte=TAM/2, total=0;
    int *vet;
    int tag=10;
    MPI_Status status;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
 
    if (meurank == 0){
        srand(313);
        vet = (int *)malloc(sizeof(int) * TAM);
        if (vet == NULL){
            printf("Não deu certo!\n");
            exit(1);
        }
         for(i=0; i < TAM; i++)
            vet[i] = rand() % MAX;
 
    MPI_Send(&vet[0], parte, MPI_INT, 1, tag, MPI_COMM_WORLD);
    MPI_Send(&vet[TAM/2], parte, MPI_INT, 2, tag, MPI_COMM_WORLD);

    MPI_Recv(&j, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    MPI_Recv(&j, 2, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
      
        MPI_Recv(&j, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
        total += j;
        MPI_Recv(&j, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &status);
        total += j;
 
        printf("Quantidade de Primos: %d\n", total);
    }  
    else {
        vet = (int *)malloc(sizeof(int) * parte);
        if (vet == NULL){
            printf("Não deu muito certo!\n");
            exit(1);
        }

        MPI_Recv(vet, parte, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        j=0;
        for(i=0; i < parte; i++){
            if (GeraPrimo(vet[i])){
                j++;
                //printf("%d\n", vet[i]);
            }
        }
        MPI_Send(&j, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
 
    MPI_Finalize();
 
}
 
 
int GeraPrimo(int num){
    int i,c=0;    
 
    for(i=3; i < num/2+1; i++)
        if ((num % i ) == 0){
            c++;
            break;
        }
    return (c == 0 ? 1 : 0);
}

