#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<time.h>

typedef struct {
    int comm_rank;
    union {
        float f;
        int i;
    } number;
} CommRankNumber;

void *gather_numbers_to_root(void *number, MPI_Datatype datatype, MPI_Comm comm) {
    int comm_rank, comm_size;
    MPI_Comm_rank(comm, &comm_rank);
    MPI_Comm_size(comm, &comm_size);

    int datatype_size;
    MPI_Type_size(datatype, &datatype_size);
    void *gathered_numbers;
    if (comm_rank == 0) {
        gathered_numbers = malloc(datatype_size * comm_size);
    }
    MPI_Gather(number, 1, datatype, gathered_numbers, 1, datatype, 0, comm);

    return gathered_numbers;
}

// A comparison function for sorting float CommRankNumber values
int compare_float_comm_rank_number(const void *a, const void *b) {
    CommRankNumber *comm_rank_number_a = (CommRankNumber *) a;
    CommRankNumber *comm_rank_number_b = (CommRankNumber *) b;
    if (comm_rank_number_a->number.f < comm_rank_number_b->number.f) {
        return -1;
    } else if (comm_rank_number_a->number.f > comm_rank_number_b->number.f) {
        return 1;
    } else {
        return 0;
    }
}

// A comparison function for sorting int CommRankNumber values
int compare_int_comm_rank_number(const void *a, const void *b) {
    CommRankNumber *comm_rank_number_a = (CommRankNumber *) a;
    CommRankNumber *comm_rank_number_b = (CommRankNumber *) b;
    if (comm_rank_number_a->number.i < comm_rank_number_b->number.i) {
        return -1;
    } else if (comm_rank_number_a->number.i > comm_rank_number_b->number.i) {
        return 1;
    } else {
        return 0;
    }
}

int *get_ranks(void *gathered_numbers, int gathered_number_count, MPI_Datatype datatype) {
    int datatype_size;
    MPI_Type_size(datatype, &datatype_size);

    CommRankNumber *comm_rank_numbers = malloc(gathered_number_count * sizeof(CommRankNumber));
    int i;
    for (i = 0; i < gathered_number_count; i++) {
        comm_rank_numbers[i].comm_rank = i;
        memcpy(&(comm_rank_numbers[i].number), gathered_numbers + (i * datatype_size), datatype_size);
    }

    // Sort the comm rank numbers based on the datatype
    if (datatype == MPI_FLOAT) {
        qsort(comm_rank_numbers, gathered_number_count,
              sizeof(CommRankNumber), &compare_float_comm_rank_number);
    } else {
        qsort(comm_rank_numbers, gathered_number_count,
              sizeof(CommRankNumber), &compare_int_comm_rank_number);
    }

    int *ranks = (int *) malloc(sizeof(int) * gathered_number_count);
    for (i = 0; i < gathered_number_count; i++) {
        ranks[comm_rank_numbers[i].comm_rank] = i;
    }
    free(comm_rank_numbers);
    return ranks;
}

int TMPI_Rank(void *send_data, void *recv_data, MPI_Datatype datatype, MPI_Comm comm) {
    int comm_size, comm_rank;
    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &comm_rank);

    void* gathered_numbers = gather_numbers_to_root(send_data,datatype,comm);

    int *ranks = NULL;
    if (comm_rank == 0){
        ranks = get_ranks(gathered_numbers, comm_size, datatype);
    }

    MPI_Scatter(ranks, 1, MPI_INT, recv_data, 1 , MPI_INT, 0, comm);

    // Do clean up
    if (comm_rank == 0) {
        free(gathered_numbers);
        free(ranks);
    }
    return 1;
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Seed the random number generator to get different results each time
    srand(time(NULL) * world_rank);

    float rand_num = rand() / (float)RAND_MAX;
    int rank;
    TMPI_Rank(&rand_num, &rank, MPI_FLOAT, MPI_COMM_WORLD);
    printf("Rank for %f on process %d - %d\n", rand_num, world_rank, rank);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}