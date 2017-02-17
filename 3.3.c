// The aim of this exercise is to efficiently transpose a distributed matrix on parallel processes.
// 1. Write a parallel program with MPI in which two matrices are distributed on the processes by being stored 
// linearly in one-dimensional arrays. The first matrix is composed of M rows and N columns, 
// the second is composed of N rows and M columns. The matrix is distributed by domain decomposition 
// along the rows: thus, each process has a matrix (M / P) xN and a matrix (N / P) xM. For simplicity, 
// take N = M = P. Thus, each process has a row of each matrix.

#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main() {
	MPI_Init(NULL, NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int row[3];

	// matrix 1
	// [1,2,3]
	// [4,5,6]

	// matrix 2
	// [1,2]
	// [3,4]
	// [5,6]
	if (rank == 0) {
		row[0] = 1;
		row[1] = 2;
		row[2] = 3;
	} else if (rank == 1) {
		row[0] = 4;
		row[1] = 5;
		row[2] = 6;
	} else if (rank == 1) {
		row[0] = 1;
		row[1] = 2;
	}
}