#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, peer;
    int *token;
    MPI_Win win;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Win_allocate(sizeof(int),sizeof(int), MPI_INFO_NULL,MPI_COMM_WORLD, &token, &win);
    

    *token = rank;
    if (0==rank){
        peer = 1;
        MPI_Get(token, 1, MPI_INT, peer, 0, 1, MPI_INT, win);
        printf("process %d token: %d\n", rank,*token);
    }

    MPI_Win_free(&win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}