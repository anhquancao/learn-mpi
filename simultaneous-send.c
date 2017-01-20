#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
	int rank;
	int data;
	int tag = 0;
	MPI_Status status, send_status1, send_status2;
	MPI_Request request, send_req1, send_req2;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (0 == rank){
		data = 22;
		while(1){
			MPI_Isend(&data, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &send_req1);
			MPI_Wait(&send_req1, &send_status1);
			data += 1;
			MPI_Isend(&data, 1, MPI_INT, 1 , tag, MPI_COMM_WORLD, &send_req2);
			MPI_Wait(&send_req2, &send_status2);
		}
	}
	if (1 == rank){
		while(1) {
			MPI_Irecv(&data, 1, MPI_INT, 0, tag,MPI_COMM_WORLD, &request);
			MPI_Wait(&request, &status);
			printf("Process 1 receives %d from process 0\n",data);
		}
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
