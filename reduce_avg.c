#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>

// Creates an array of random numbers. Each number has a value from 0 - 1
float *create_rand_nums(int num_elements) {
    float *rand_nums = (float *) malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++) {
        rand_nums[i] = (rand() / (float) RAND_MAX);
    }
    return rand_nums;
}

int main() {
    int num_elements_per_proc = 3;
    float *rand_nums = NULL;
    rand_nums = create_rand_nums(num_elements_per_proc);

    float local_sum = 0;
    int i;
    for (i = 0; i < num_elements_per_proc; i++) {
        local_sum += rand_nums[i];
    }

    // Print the random numbers on each process
    printf("Local sum for process %d - %f, avg = %f\n",
           world_rank, local_sum, local_sum / num_elements_per_proc);

    float global_sum;
    MPI_Reduce(&local_sum,&global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result
    if (world_rank == 0) {
        printf("Total sum = %f, avg = %f\n", global_sum,
               global_sum / (world_size * num_elements_per_proc));
    }
}