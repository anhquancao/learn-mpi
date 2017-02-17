#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>

float *create_rand_nums(int num_elements) {
	float *rand_nums = (float*) malloc(sizeof(float)*num_elements);
	int i;
	for (i=0;i< num_elements;i++){
		rand_nums[i] = (rand() / (float)RAND_MAX);
	}
	return rand_nums;
}

float compute_avg(float *array, int num_elements){
	float sum = 0.f;
	int i;
	for (i=0; i < num_elements; i++) {
		sum += array[i];
	}
	return sum / num_elements;
}

int main() {
	int num_elements_per_proc = 10;
	srand(time(NULL));

	MPI_Init(NULL, NULL);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	float *rand_nums = NULL;
	if (world_rank == 0) {
		rand_nums = create_rand_nums(num_elements_per_proc * world_size);
	}

	// For each process, create a buffer that will hold a subset of the entire
  	// array
  	float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
  	MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums, num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  	// compute the average of your subset
  	float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

  	// Gather all partial averages to the root process
  	float *sub_avgs = NULL;
		sub_avgs = (float *)malloc(sizeof(float)*world_size);
  	MPI_Allgather(&sub_avg,1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, MPI_COMM_WORLD);


  	//compute the total average	
		float avg = compute_avg(sub_avgs,world_size);
		printf("Process %d: Avg of all elements is %f\n",world_rank ,avg);

  	//clean up
  	if (world_rank == 0) {
  		free(rand_nums);
  		free(sub_avgs);
  	}
  	
  	free(sub_rand_nums);
  	MPI_Barrier(MPI_COMM_WORLD);
  	MPI_Finalize();
  	return EXIT_SUCCESS;
}