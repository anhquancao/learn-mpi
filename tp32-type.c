
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

struct newTypeStruct{
	int a;
	int b;
	int c;
};

int main ( int argc , char ** argv ) {
	struct newTypeStruct data;
	
	MPI_Datatype newType;
	int i;
	MPI_Status status;
	int tag = 333;

	int M=3; // number of block
	int N=1; // block length

	int blockLengths[3]= { 1, 1, 1 };
	MPI_Aint displacements[3] = {0, sizeof(int), 2*sizeof(int)};
	MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};
 
	MPI_Init(NULL,NULL);
	
	MPI_Type_create_struct(3,blockLengths , displacements, types, &newType);
	MPI_Type_commit(&newType);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (0 == rank){
		data.a = 1;
		data.b = 2;
		data.c = 3;
		MPI_Send(&data,1,newType,1,tag,MPI_COMM_WORLD);
	} else if (1== rank){
		MPI_Recv(&data, 1, newType, 0,tag, MPI_COMM_WORLD, &status);
		printf(" %d %d %d",data.a, data.b, data.c);	
	}
	
		

	MPI_Finalize();
	return EXIT_SUCCESS ;
}

