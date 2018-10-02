#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv){
    int meurank, procs;
    int tag = 10;
    MPI_Status status;
    int envia, recebe;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);

    srand(101);
    if (meurank != 0)
        MPI_Recv(&recebe, 1, MPI_INT, meurank-1, tag, MPI_COMM_WORLD, &status);
    
    if (meurank == 0)
        envia = 100 + rand() % 1000;
    else if (meurank == 1)
        envia = recebe * recebe;
    else if (meurank == 2)
        envia = recebe % 100;
    else if (meurank == 3)
        envia = recebe * 2;
    else 
        printf("Valor %d\n", recebe);

    if (meurank != procs-1)    
        MPI_Send(&envia, 1, MPI_INT, meurank+1, tag, MPI_COMM_WORLD);
    
    MPI_Finalize();
}
