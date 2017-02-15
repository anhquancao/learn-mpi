#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char ** argv){

    int rank;
    int tag = 999;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    int number_amount;

    if (rank == 0) {
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
        MPI_Send(numbers,number_amount, MPI_INT, 1, tag , MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Status status;

        MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_INT, &number_amount);

        printf("1 received %d from 0. Message source = %d, tag = %d\n",
            number_amount,status.MPI_SOURCE,status.MPI_TAG);

    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;

}