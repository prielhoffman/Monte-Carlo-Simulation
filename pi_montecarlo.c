#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define PI25DT 3.141592653589793238462643 // reference value accurate to 25 digits

int main(int argc, char** argv) 
{
  int rank, size;
  int Nc = 10000000; // number of total points
  int num_inside = 0, Ns = 0;
  double x, y, z, d;
  double start_time, end_time; // for calc computation time
  int i, j, n;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  n = size; // number of random seeds
  int* seeds = (int*) malloc(sizeof(int) * n);

  // Rank 0 generates n random seeds.
  if (rank == 0) 
  {
    for (i = 0; i < n; i++) 
    {
      seeds[i] = rand(); // Generate random seeds
    }
  }
   // start timer
   start_time= MPI_Wtime();

  // Rank 0 broadcasts all random seeds to the n ranks (including itself).
  MPI_Bcast(seeds, n, MPI_INT, 0, MPI_COMM_WORLD);

  // Receive corresponding seed
  srand(seeds[rank]);

  // Generate points and count number inside unit sphere
  for (j = 0; j < Nc / n; j++) 
{  
    x = ((double) rand() / RAND_MAX + rank) / n;
    y = (double) rand() / RAND_MAX;
    z = (double) rand() / RAND_MAX;
    d = x * x + y * y + z * z; // compute the distance d = x^2 + y^2 + z^2 
    if (d <= 1.0) // increment num_inside
    {
      num_inside++;
    }
  }

  // Send number inside back to rank 0
  MPI_Reduce(&num_inside, &Ns, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
  if (rank == 0) 
{
    // stop timer
    end_time = MPI_Wtime();
    // Compute Pi and print results
    double Pi = 6.0 * (double) Ns / (double) Nc;
    printf("Pi = %f\n", Pi); // Rank 0 print Pi = 6 * Ns / Nc
    printf("Absolute difference = %.25f\n", fabs(Pi - PI25DT)); // absolute difference between the obtained Pi and PI25
    printf("Computation time = %f seconds\n", end_time - start_time); // Rank 0 print the computation time using MPI_Wtime()
    fflush(stdout); // clean stdout
 }

  MPI_Finalize();
  return 0;
}
