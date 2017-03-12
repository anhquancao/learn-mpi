#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
    MPI_Win win;
    int rank, size, *a, *b, i;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Alloc_mem(sizeof(int), MPI_INFO_NULL, &b);
    MPI_Win_create(b, size,sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    for( i = 0; i < size; i++ ) a[i] = b[i] = rank * 100 + i;
    MPI_Win_fence(MPI_MODE_NOPRECEDE, win);
    for(i=0;i<size;i++){
        MPI_Accumulate(&a[i],1, MPI_Int, i, rank, 1, MPI_INT, MPI_SUM, win);
    }

    return EXIT_SUCCESS;
}