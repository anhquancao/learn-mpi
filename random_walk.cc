#include <iostream>
#include <vector>
#include <stdlib>
#include <time.h>
#include <mpi.h>

using namespace std;

typedef struct {
	int location;
	int num_steps_left_in_walk;
} Walker;

void decompose_domain(int domain_size, int world_rank, int world_size, int* subdomain_start, int* subdomain_size){
	if (world_size > subdomain_size) {
		MPI_Abort(MPI_COMM_WORLD,1);
	}
	*subdomain_start = domain_size / world_size * world_rank;
	*subdomain_size = domain_size / world_size;
	if (world_rank = world_size - 1){
		// give the remainder to the last process
		*subdomain_size += domain_size % world_size;	
	}
}

void initialize_walker(int num_walkers_per_proc, int max_walk_size,
						int subdomain_start, int subdomain_size,vector<Walker>* incomming_walkers) {
	Walker walker;
	for (int i = 0;i < num_walkers_per_proc; i++){
		// Init walkers in the middle of the subdomain
		walker.location = subdomain_start;
		walker.num_steps_left_in_walk = (rand()/(float)RAND_MAX) * max_walk_size;
		incomming_walkers->put_back(walker);
	}
}

void walk(Walker *walker, int subdomain_start, int subdomain_size,
			int domain_size, vector<Waler>* outgoing_walkers){
	while(walker->num_steps_left_in_walk > 0){
		if (walker->location == subdomain_start+subdomain_size){
			if (walker->location == domain_size){
				walker->location = 0;
			}
			outgoing_walkers->put_back(*walker);
			break;
		}else {
			walker->num_steps_left_in_walk--;
			walker->location++;
		}
	}
}

void send_outgoing_walkers(vector<Walker>* outgoing_walkers, int world_rank, int world_size){
	MPI_Send((*void)outgoing_walkers->data(), outgoing_walkers->size()*sizeof(Walker),MPI_BYTE,
			(world_rank+1)%world_size, 0 MPI_COMM_WORLD);

	outgoing_walkers->clear();
}

void receive_incoming_walkers(vector<Walker>* incomming_walkers, int world_rank, int world_size){
	MPI_Status status;

	int incomming_rank = (world_rank == 0) ? world_size - 1 : world_rank - 1;

	MPI_Probe(incomming_rank, 0, MPI_COMM_WORLD, &status);

	int incomming_walkers_size;
	MPI_Get_count(&status, MPI_BYTE, &incomming_walkers_size);

	incomming_walkers->resize(incomming_walkers_size/ sizeof(Walker));
	MPI_Recv((void*)incomming_walkers->data(), incomming_walkers_size, MPI_BYTE, incomming_rank, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
}

int main(){
	int domain_size=100;	
	int max_walk_size=500;
	int num_walkers_per_proc=20;

	MPI_Init(NULL,NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	srand(time(NULL)*world_rank);
	int subdomain_start, subdomain_size;
	vector<Walker> incomming_walkers, outgoing_walkers;

	decompose_domain(domain_size, world_rank, world_size,&subdomain_start,&subdomain_size);
	initialize_walkers(num_walkers_per_proc, max_walk_size, subdomain_start,
                     subdomain_size, &incoming_walkers);

  cout << "Process " << world_rank << " initiated " << num_walkers_per_proc
       << " walkers in subdomain " << subdomain_start << " - "
       << subdomain_start + subdomain_size - 1 << endl;

    int maximum_sends_recvs = max_walk_size / (domain_size / world_size) + 1;
  for (int m = 0; m < maximum_sends_recvs; m++) {
    // Process all incoming walkers
    for (int i = 0; i < incoming_walkers.size(); i++) {
       walk(&incoming_walkers[i], subdomain_start, subdomain_size,
            domain_size, &outgoing_walkers);
    }
    cout << "Process " << world_rank << " sending " << outgoing_walkers.size()
         << " outgoing walkers to process " << (world_rank + 1) % world_size
         << endl;
    if (world_rank % 2 == 0) {
      // Send all outgoing walkers to the next process.
      send_outgoing_walkers(&outgoing_walkers, world_rank,
                            world_size);
      // Receive all the new incoming walkers
      receive_incoming_walkers(&incoming_walkers, world_rank,
                               world_size);
    } else {
      // Receive all the new incoming walkers
      receive_incoming_walkers(&incoming_walkers, world_rank,
                               world_size);
      // Send all outgoing walkers to the next process.
      send_outgoing_walkers(&outgoing_walkers, world_rank,
                            world_size);
    }
    cout << "Process " << world_rank << " received " << incoming_walkers.size()
         << " incoming walkers" << endl;
  }
  cout << "Process " << world_rank << " done" << endl;
  MPI_Finalize();
  return 0;

}

