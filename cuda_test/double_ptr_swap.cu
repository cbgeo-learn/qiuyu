#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cuda.h>
#include <iostream>
#include <stdio.h>

__device__ int block_idx(int grid_dim) {
  int block_id = blockIdx.x + (grid_dim == 2 ? 1 : 0) * blockIdx.y * gridDim.x +
                 (grid_dim == 3 ? 1 : 0) * blockIdx.z * gridDim.x * gridDim.y;
  return block_id;
}

__device__ int thread_idx(int grid_dim, int block_dim) {
  // ! thread id inside a block
  unsigned long int threadIdInBlock =
      threadIdx.x + (block_dim == 2 ? 1 : 0) * threadIdx.y * blockDim.x +
      (block_dim == 3 ? 1 : 0) * threadIdx.z * blockDim.x * blockDim.z;
  //! block id
  unsigned long int block_id = block_idx(grid_dim);
  // ! block size
  unsigned long int threadsPerblock = blockDim.x *
                                      (block_dim == 2 ? blockDim.y : 1) *
                                      (block_dim == 3 ? blockDim.z : 1);
  unsigned long int thread_id = block_id * threadsPerblock + threadIdInBlock;
  return thread_id;
}

void show_array(int** array, int nbrows, int nbcols) {
  for (int i = 0; i < nbrows; ++i) {
    for (int j = 0; j < nbcols; ++j) std::cout << array[i][j] << std::endl;
  }
}

__global__ void gpu_array_swap(int** ptr_gpu, int nbrows, int nbcols,
                               int grid_dim, int block_dim) {
  int thread_id = thread_idx(grid_dim, block_dim);
  int i = floorf((thread_id + 1) / nbcols);
  int j = thread_id + 1 - i * nbcols;
  // To test if kernel function runs
  //(Fact:it runs)
  printf("I am running!\n");
  //__syncthreads();

  // To see if ptr_gpu has been transferred
  //(Fact: Not transferred in and the printf command below didn't run)
  ptr_gpu[1][1] = 100;
  printf("%d %d\n", ptr_gpu[1][1], ptr_gpu[i][j]);
}

int main() {
  //! Declare a double pointer on the host
  int **ptr_cpu = NULL, **ptr_gpu = NULL;
  const int nbcols = 4, nbrows = 5;
  int N = nbrows * nbcols;
  ptr_cpu = new int*[nbrows];
  for (int i = 0; i < nbrows; i++) ptr_cpu[i] = new int[nbcols];

  int k = 0;
  for (int i = 0; i < nbrows; ++i) {
    for (int j = 0; j < nbcols; ++j) ptr_cpu[i][j] = k++;
  };

  //! Allocate memory on GPU
  cudaMalloc(&ptr_gpu, nbrows * sizeof(int*));
  cudaMemcpy(ptr_gpu, ptr_cpu, nbrows * sizeof(int*), cudaMemcpyHostToDevice);
  if (ptr_gpu == NULL) {
    printf("Couldn't allocate GPU memory\n");
  };

  // 2d block: threads in x and y directions
  dim3 bs = dim3(nbrows, nbcols);
  // 1d grid: block in x direction
  int grid = 1;  // Only 1 block
  // grid and block dimensions
  int grid_dim = 1, block_dim = 2;

  // ! Call kernel function on a 1d-grid 2d-block
  gpu_array_swap<<<grid, bs>>>(ptr_gpu, nbrows, nbcols, grid_dim, block_dim);

  //! Copy data from device to host
  cudaDeviceSynchronize();
  cudaMemcpy(ptr_cpu, ptr_gpu, nbrows * sizeof(int*), cudaMemcpyDeviceToHost);
  
  //  show_array(ptr_cpu, nbrows, nbcols);

  cudaFree(ptr_gpu);
  free(ptr_cpu);
}
