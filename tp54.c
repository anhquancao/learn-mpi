#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    MPI_Init(NULL,NULL);
    int max,counter,rank,size;
    

    max = 0;
    MPI_Win win1,win2;
    MPI_Group group;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Win_create(&counter, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win1);
    MPI_Win_create(&max, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win2);

    if (rank != 0){
        counter = 1;
        int a[5],i,max;
        srand(rank);
        for (i=0;i<5;i++){
            a[i] = rand();
        }
        max = a[0];
        for (i=1;i<5;i++){
            if (a[i] > max) {
                max = a[i];
            }
        }
        printf("process: %d max: %d\n",rank,max);
        MPI_Win_fence(0,win1);
        MPI_Accumulate(&counter, 1, MPI_INT, 0, 0, 1, MPI_INT, MPI_SUM, win1);
        MPI_Win_fence(0, win1);

        MPI_Win_fence(0, win2);
        MPI_Accumulate(&max, 1, MPI_INT, 0, 0, 1, MPI_INT, MPI_MAX, win2);
        MPI_Win_fence(0, win2);
    } else {
        counter = 0;
        // while (counter < size) {
        MPI_Win_fence(0,win1);
        MPI_Win_fence(0,win1);
        MPI_Win_fence(0,win2);
        MPI_Win_fence(0,win2);
        printf("process 0: counter %d\n",counter);
        printf("process 0: max %d\n",max);
        // }
    }

    MPI_Win_free(&win1);
    MPI_Finalize();
    return EXIT_SUCCESS;
}