#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){
    int outbox, inbox;
    int procs, myRank;
    int tag = 10;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if(myRank > 0)
        MPI_Recv(&inbox, 1, MPI_INT, myRank-1, tag, MPI_COMM_WORLD, &status);
    else srand(1903);
        
    switch(myRank){
        case 0: outbox = (rand() % 10000) + 101; 
            break;
        case 1: outbox = inbox*inbox; 
            break;
        case 2: outbox = inbox%100; 
            break;
        case 3: outbox = inbox*2; 
            break;
        case 4: outbox = inbox;
            break;
    }

    if (myRank <= 3)
        MPI_Send(&outbox, 1, MPI_INT, myRank+1, tag, MPI_COMM_WORLD);
    else
        printf("Resultado final: %d\n", inbox);

    MPI_Finalize();
    return(0); 
}

