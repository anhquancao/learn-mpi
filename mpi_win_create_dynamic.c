#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
    int *a;
    MPI_Win win;

    MPI_Init(NULL,NULL);
    MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    // create private memory
    a = (int*) malloc(1000* sizeof(int));
    a[0] = 1;
    a[1] = 2;

    // locally declare memory as remotely accessible
    MPI_Win_attach(win, a, 1000*sizeof(int));

    // array a is now accessible from all processes

    // undeclare remotely accessible memory
    MPI_Win_detach(win, a);
    free(a);
    MPI_Win_free(&win);

    MPI_Finalize();
    return EXIT_SUCCESS;
}