# Implementing a Parallel Monte Carlo Pi Estimation Using MPI

This repository contains a parallelized Monte Carlo simulation program for estimating the value of Pi (π) using MPI (Message Passing Interface). The simulation divides the work of generating random points and counting how many fall inside a sphere, allowing for efficient computation across multiple processes.

## Overview

The simulation models a sphere circumscribed by a cube and estimates Pi by randomly generating points in the cube and counting those that fall within the sphere. The program uses MPI to distribute the computation among multiple processes, each of which handles a portion of the total points.

## Key Features

- **Parallel Computation**: Utilizes MPI to parallelize the simulation across multiple processes, improving performance and efficiency.
- **Random Point Generation**: Generates random points uniformly within the cube in the first octant of the coordinate system.
- **Estimation of Pi**: Computes the value of Pi based on the ratio of points inside the sphere to the total points generated.
- **Performance Metrics**: Measures and reports the execution time and compares the estimated Pi with a reference value (PI25) accurate to 25 decimal places.
- **Execution on Virtual Machine**: Supports execution on a Virtual Machine, with additional performance analysis using Jumpshot and Scalasca.

## How It Works

1. **Random Seed Generation**: The master process (rank 0) generates unique random seeds for each MPI process.
2. **Broadcasting Seeds**: The master process broadcasts the seeds to all MPI processes.
3. **Point Generation and Counting**: Each process generates a subset of points within its assigned segment of the cube and counts how many fall inside the sphere.
4. **Aggregation of Results**: The master process collects results from all processes, calculates the estimated Pi, and prints the value along with the execution time.

## Running the Program

### 1. Compile the Program:

```bash
mpicc -o pi_montecarlo pi_montecarlo.c
```

### 2. Execute the Program with Nc = 100,000,000 points and varying numbers of tasks (n):

```bash
mpirun -np [number_of_tasks] ./pi_montecarlo
```
Example for 4 tasks:
```bash
mpirun -np 4 ./pi_montecarlo
```
The program will output:
- Estimated value of Pi.
- Absolute difference from the reference Pi value (PI25).
- Computation time.
 
## Notes
- Ensure the MPI environment is properly set up for compilation and execution.
- Execution times and performance may vary based on the number of tasks and the computational resources available.
- The accuracy of the Pi estimation depends on the number of points generated.
