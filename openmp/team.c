#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tid, teamid;
#pragma omp target teams num_teams(2) thread_limit(2)
    {
#pragma omp parallel private(tid, teamid)
        {
            teamid = omp_get_team_num();
            tid = omp_get_thread_num();
            printf("Thread: %d, Team: %d\n", tid, teamid);
        }
    }
    return EXIT_SUCCESS;
}