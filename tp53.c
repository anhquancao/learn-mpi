#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    MPI_Init(NULL,NULL);
    int rank,seed;
    MPI_Win win;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Win_create(&seed, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    if (rank == 0) {
        seed = 22;
    }
    MPI_Win_fence(0,win);
    if (rank != 0){
        MPI_Get(&seed,1,MPI_INT,0,0,1,MPI_INT,win);
    }
    MPI_Win_fence(0,win);

    printf("seed: %d\n",seed);
    int a[5],i;
    srand(seed);
    for (i=0;i<5;i++){
        a[i] = rand();
        printf("process %d: %d \n",rank, a[i]);
    }
    

    MPI_Win_free(&win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}