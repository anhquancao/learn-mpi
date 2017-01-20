
# include <stdio.h>
# include <stdlib.h>
# include <mpi.h>
int main ( int argc , char ** argv ) {
int size , rank , len ;
char name [ MPI_MAX_PROCESSOR_NAME];
MPI_Init ( NULL ,NULL ) ;
MPI_Comm_rank ( MPI_COMM_WORLD , &rank ) ;
MPI_Comm_size ( MPI_COMM_WORLD , &size ) ;
MPI_Get_processor_name(name , &len ) ;
fprintf ( stdout , "Je suis le processus % d parmi % d sur % s \n" ,rank , size , name ) ;
MPI_Finalize () ;
return EXIT_SUCCESS ;
}
