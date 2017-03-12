#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
    int *a;
    MPI_Win win;
    MPI_Init(NULL,NULL);
    
    /* collectively create remote accessible memory in a window */
    MPI_Win_allocate(1000*sizeof(int),sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, a, &win);

    MPI_Win_free(&win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}