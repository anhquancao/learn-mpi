#include<omp.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    omp_lock_t lock;
    omp_init_lock(&lock);
    int id;

    #pragma omp parallel private (id)
    {
        id=omp_get_thread_num();
        omp_set_lock(&lock);
        printf("%d\n", id);
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    return EXIT_SUCCESS;
}