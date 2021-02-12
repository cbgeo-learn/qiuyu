#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cuda.h>
#include <stdio.h>
#include <cassert>

//! Get the block id
__device__ int block_idx(int grid_dim) {
  int block_id = blockIdx.x + (grid_dim == 2 ? 1 : 0) * blockIdx.y * gridDim.x +
                 (grid_dim == 3 ? 1 : 0) * blockIdx.z * gridDim.x * gridDim.y;
  return block_id;
}

//! Get the global thread id
__device__ int thread_idx(int grid_dim, int block_dim) {
  // thread id inside a block
  unsigned long int threadIdInBlock =
      threadIdx.x + (block_dim == 2 ? 1 : 0) * threadIdx.y * blockDim.x +
      (block_dim == 3 ? 1 : 0) * threadIdx.z * blockDim.x * blockDim.z;
  // block id
  unsigned long int block_id = block_idx(grid_dim);
  // block size
  unsigned long int threadsPerblock = blockDim.x *
                                      (block_dim == 2 ? blockDim.y : 1) *
                                      (block_dim == 3 ? blockDim.z : 1);
  unsigned long int thread_id = block_id * threadsPerblock + threadIdInBlock;
  return thread_id;
}

//! Get the transposed matrix
__global__ void gpu_array_swap(int* ptr_gpu, int nbrows, int nbcols,
                               int grid_dim, int block_dim) {
  int thread_id = thread_idx(grid_dim, block_dim);
  // check if the array is correct.
  printf("%d %d\n", ptr_gpu[thread_id], thread_id);

  // pass the matrix to shared memory
  extern __shared__ int sdata[];
  sdata[thread_id] = ptr_gpu[thread_id];

  __syncthreads();
  int row = floorf((thread_id + 1) / nbcols);
  int col = thread_id + 1 - row * nbcols;
  int swap_thread_id = col * nbcols + row - 1;
  ptr_gpu[thread_id] = sdata[swap_thread_id];
  printf("%d %d\n", ptr_gpu[thread_id], thread_id);
}

void print_array(int** array, int nbrows, int nbcols) {
  for (int i = 0; i < nbrows; ++i) {
    for (int j = 0; j < nbcols; ++j) {
      std::cout << array[i][j] << "  ";
      if (j == (nbcols - 1)) std::cout << std::endl;
    }
  }
}

int main() {
  // declare a vector on the host
  int **ptr_cpu = NULL, *ptr_gpu = NULL;
  const int nbcols = 4, nbrows = 5;
  int N = nbrows * nbcols;
  int nbytes = N * sizeof(int);
  ptr_cpu = new int*[nbrows];
  // for (int i = 0; i < nbrows; i++) ptr_cpu[i] = new int[nbcols];

  // !The memory should be contiguous on the host
  ptr_cpu[0] = (int*)malloc(nbytes);
  // ptr_cpu[0]=new int[N];
  for (int i = 1; i < nbrows; ++i) ptr_cpu[i] = ptr_cpu[i - 1] + nbcols;

  int k = 0;
  for (int i = 0; i < nbrows; ++i) {
    for (int j = 0; j < nbcols; ++j) ptr_cpu[i][j] = k++;
  };
  print_array(ptr_cpu, nbrows, nbcols);

  // allocate gpu memory
  cudaMalloc(&ptr_gpu, nbytes);

  // copy data to gpu
  cudaMemcpy(ptr_gpu, ptr_cpu[0], nbytes, cudaMemcpyHostToDevice);
  if (ptr_gpu == NULL) {
    printf("Couldn't allocate GPU memory\n");
  };

  // 2d block: threads in x and y directions
  dim3 bs = dim3(nbrows, nbcols);
  // 1d grid: block in x direction
  int grid = 1;  // Only 1 block
  // grid and block dimensions
  int grid_dim = 1, block_dim = 2;
  gpu_array_swap<<<grid, bs, nbytes>>>(ptr_gpu, nbrows, nbcols, grid_dim,
                                       block_dim);

  //! Copy data from device to host
  cudaDeviceSynchronize();
  memset(ptr_cpu, 0, nbytes);
  cudaMemcpy(ptr_cpu[0], ptr_gpu, nbytes, cudaMemcpyDeviceToHost);
  if (cudaMemcpy(ptr_cpu[0], ptr_gpu, nbytes, cudaMemcpyDeviceToHost) !=
      cudaSuccess)
    std::cout << "Fail to copy back to cpu!" << std::endl;

  print_array(ptr_cpu, nbrows, nbcols);
  cudaFree(ptr_gpu);
  free(ptr_cpu);
}
