// Exercise 5.1: Intermediate
// Write a program that runs with at least three processes. 
// Process 0 initializes an integer with its pid. 
// Process 1 fetches it with an MPI_Get and writes it to Process 2 with an MPI_Put.
#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    MPI_Init(NULL,NULL);
    int rank,data;
    MPI_Win win;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Win_create(&data, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    if (rank == 0) {
        data = 99;
        
        printf("Process %d: init data: %d\n", rank, data);
        MPI_Win_fence(MPI_MODE_NOPRECEDE,win);
        MPI_Win_fence(0,win);
        MPI_Win_fence(0,win);
    } 
    
    if (rank == 1){
        MPI_Win_fence(MPI_MODE_NOPRECEDE,win);
        
        MPI_Get(&data, 1, MPI_INT, 0, 0, 1, MPI_INT, win);
        
        int target_rank = 2;
        MPI_Win_fence(0,win);
        printf("Process %d: receive data: %d\n", rank, data);
        MPI_Put(&data, 1, MPI_INT ,target_rank, 0, 1, MPI_INT, win);
        printf("Process %d: send data: %d to %d\n", rank, data, target_rank);
        MPI_Win_fence(0,win);
    } 
    
    if (rank == 2) {
        MPI_Win_fence(MPI_MODE_NOPRECEDE,win);
        MPI_Win_fence(0,win);
        MPI_Win_fence(0,win);
        printf("Process %d: receive data: %d\n", rank, data);
    }
    MPI_Win_free(&win);
    MPI_Finalize();
    return EXIT_SUCCESS;
}