
# include <stdio.h>
# include <stdlib.h>
# include <mpi.h>
int main ( int argc , char ** argv ) {
	MPI_Datatype dt;
	int i;
	MPI_Status status;
	int tag = 0;

	MPI_Init(NULL,NULL);
	MPI_Type_contiguous(5, MPI_INT, &dt);
	MPI_Type_commit(&dt);
	int data[5];

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (0 == rank){
		for (i = 0; i < 5 ; i++){
			data[i] = i;
		}
		MPI_Send(data,1,dt,1,tag,MPI_COMM_WORLD);
	} else if (1== rank){
		MPI_Recv(data, 1, dt, 0,tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < 5 ; i++){
			printf(" %d ",data[i]);
		}
	}
	
		

	MPI_Finalize();
	return EXIT_SUCCESS ;
}

