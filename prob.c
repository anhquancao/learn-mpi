#include<time.h>
#include<stdlib.h>
#include<mpi.h>
#include<stdio.h>

int main(){

    MPI_Init(NULL,NULL);
    int rank;
    int tag = 999;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number_amount;
    if (rank == 0){
        const int MAX_NUMBER = 100;
        int numbers[MAX_NUMBER];

        number_amount = 60;

        MPI_Send(numbers, number_amount, MPI_INT, 1, tag, MPI_COMM_WORLD);

        printf("0 send %d numbers to 1\n", number_amount);
    } else if (rank == 1) {
        MPI_Status status;

        MPI_Probe(0,tag, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status,MPI_INT, &number_amount);

        int* number_buff = (int*)malloc(sizeof(int) * number_amount);

        MPI_Recv(number_buff,number_amount,MPI_INT,0,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        printf("1 dynamically received %d numbers from 0.\n",number_amount);
        free(number_buff);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}