#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
	int rank;
	int data;
	int tag = 0;
	MPI_Status status;
	MPI_Request request;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (0 == rank){
		data = 22;
		MPI_Isend(&data, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		MPI_Irecv(&data, 1, MPI_INT, 1, tag, MPI_COMM_WORLD,&request);
		MPI_Wait(&request, &status);
		printf("Process 1 received %d from process 0\n",data);
	}
	if (1 == rank){
		MPI_Irecv(&data, 1, MPI_INT, 0, tag,MPI_COMM_WORLD, &request);
		MPI_Wait(&request, &status);
		printf("Process 1 receives %d from process 0\n",data);
		data += 1;
		MPI_Isend(&data, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &request);
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
