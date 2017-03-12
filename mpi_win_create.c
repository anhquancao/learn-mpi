#include<stdlib.h>
#include<mpi.h>
#include<stdio.h>

int main() {
    int *a;
    MPI_Win win;

    MPI_Init(NULL,NULL);
    
    /* create private memory */
    MPI_Alloc_mem(1000*sizeof(int), MPI_INFO_NULL, &a);
    a[0] = 1;
    a[1] = 2;

    /* collectively declare memory as remotely accessible */
    MPI_Win_create(a, 1000*sizeof(int), sizeof(int),MPI_INFO_NULL,MPI_COMM_WORLD, &win);

    /* Array a is now accessible by all processes in MPI_COMM_WORLD */
    MPI_Win_free(&win);
    MPI_Free_mem(a);
    MPI_Finalize();
    return EXIT_SUCCESS;

}