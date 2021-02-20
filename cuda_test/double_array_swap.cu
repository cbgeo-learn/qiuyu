#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cuda.h>
#include <stdio.h>
#include <cassert>
//define the chunk sizes that each threadblock will work on
#define BLKXSIZE 32
#define BLKYSIZE 4
#define BLKZSIZE 4
#define Q 19
#define lx 10
#define ly 10
#define lz 5

// for cuda error checking
#define cudaCheckErrors(msg) \
    do { \
        cudaError_t __err = cudaGetLastError(); \
        if (__err != cudaSuccess) { \
            fprintf(stderr, "Fatal error: %s (%s at %s:%d)\n", \
                msg, cudaGetErrorString(__err), \
                __FILE__, __LINE__); \
            fprintf(stderr, "*** FAILED - ABORTING\n"); \
            return 1; \
        } \
    } while (0)

template <typename T> __device__ void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}


__global__ void gpu_array_swap(int ptr_gpu[][ly][lz][Q]) {
  // int thread_id = thread_idx(grid_dim, block_dim);
  unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
  unsigned idy = blockIdx.y * blockDim.y + threadIdx.y;
  unsigned idz = blockIdx.z * blockDim.z + threadIdx.z;
  if ((idx < lx) && (idy < ly) && (idz < lz)) {
    for (size_t i = 1; i <= 9; i++)
          swap(ptr_gpu[idx][idy][idz][i], ptr_gpu[idx][idy][idz][i + 9]);
  }
}

void set_array(int array[][ly][lz][Q]) {
  int m = 0;
  for (int l = 0; l < Q; ++l) {
    for (int i = 0; i < lz; ++i) {
      for (int j = 0; j < ly; ++j) {
        for (int k = 0; k < lx; ++k) {
          array[i][j][k][l] = ++m;
        }
      }
    }
  }
}

void print_array(int array[][ly][lz][Q]) {
  for (int i = 0; i < lx; ++i) {
    for (int j = 0; j < ly; ++j) {
      for (int k = 0; k < lz; ++k) {
        for (int l = 0; l < Q; ++l) {
          std::cout << array[i][j][k][l] << "  ";
          if (l == (Q - 1)) std::cout << std::endl;
        }
      }
    }
  }
}

int main() {
  typedef int array_3d[ly][lz];
  typedef int array_4d[ly][lz][Q];
  const dim3 blockSize(BLKXSIZE, BLKYSIZE, BLKZSIZE);
  const dim3 gridSize(((lx + BLKXSIZE - 1) / BLKXSIZE),
                      ((ly + BLKYSIZE - 1) / BLKYSIZE),
                      ((lz + BLKZSIZE - 1) / BLKZSIZE));

  // pointers for data set storage via malloc
  array_4d* c;    // storage for result stored on host
  array_4d* d_c;  // storage for result computed on device
                  // allocate storage for data set
  if ((c = (array_4d*)malloc((lx * ly * lz * Q) * sizeof(int))) == 0) {
    fprintf(stderr, "malloc1 Fail \n");
    return 1;
  }
  set_array(c);
  print_array(c);
  
  // allocate GPU device buffers
  cudaMalloc((void**)&d_c, (lx * ly * lz * Q) * sizeof(int));
  cudaCheckErrors("Failed to allocate device buffer");
cudaMemcpy(d_c, c, ((lx * ly * lz * Q) * sizeof(int)),
             cudaMemcpyHostToDevice);
  
  // compute result
  gpu_array_swap<<<gridSize, blockSize>>>(d_c);
  cudaCheckErrors("Kernel launch failure");
  // copy output data back to host

  cudaMemcpy(c, d_c, ((lx * ly * lz * Q) * sizeof(int)),
             cudaMemcpyDeviceToHost);
  cudaCheckErrors("CUDA memcpy failure");
  free(c);
  cudaFree(d_c);
  cudaCheckErrors("cudaFree fail");
  return 0;
}
