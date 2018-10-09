#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int procs;
    int meurank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    printf("Oi Mundo!! Sou o processo %d de %d "
        "sendo executado\n", meurank, procs);
    MPI_Finalize();
    return 0;
}
