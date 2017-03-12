#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
    int rank, data, size;
    MPI_Init(NULL, NULL);
    MPI_Win win;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Win_create(&data, sizeof(int),sizeof(int),MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    if (rank == 0){
        data = 22;
    }
    int target = (rank + 1) % size;
    printf("process %d: target: %d\n",rank, target);
    int i;
    for (i=0;i<size;i++){
        MPI_Win_fence(0, win);
        if (rank == i) {
            printf("process %d send %d to process %d\n",rank, data, target);
            MPI_Put(&data, 1, MPI_INT, target, 0, 1, MPI_INT, win);
        }
        MPI_Win_fence(0, win);
    }
    printf("process %d: data: %d\n",rank, data);
    MPI_Win_free(&win);
    MPI_Finalize();
    return EXIT_SUCCESS;

}