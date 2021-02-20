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

template <typename Ttype>
Ttype**** create_4d_harray() {
  Ttype**** array;
  array = new Ttype***[lx];
  assert(array != nullptr);
  
  array[0] = (Ttype***)malloc(sizeof(Ttype)*lx*ly*lz*Q);
  for (int i = 1; i < lx; i++) {//from i=0 to i=1;
    // array[i] = new Ttype**[ly];
    array[i] = array[i-1] + ly*lz*Q;
    assert(array[i] != nullptr);
    array[i][0] = (Ttype**)malloc(sizeof(Ttype)*ly*lz*Q);
    for (int j = 1; j < ly; j++) {
      //array[i][j] = new Ttype*[lz];
      array[i][j] = array[i][j-1] + lz*Q;
      assert(array[i][j] != nullptr);
      array[i][j][0] = (Ttype*)malloc(sizeof(Ttype)*Q);
      for (int k = 1; k < lz; k++) {
        //array[i][j][k] = new Ttype[n];  
        array[i][j][k] = array[i][j][k-1]+ Q;
        assert(array[i][j][k] != nullptr);
      }
    }
  }
  return array;
}

template <typename Ttype>
void free_4d_harray(Ttype**** array) {
  for (size_t i = 0; i < lx; ++i) {
    for (size_t j = 0; j < ly; ++j) {
      for (size_t k = 0; k < lz; ++k) {
        delete[] array[i][j][k];
      }
      delete[] array[i][j];
    }
    delete[] array[i];
  }
  delete[] array;
}


template <typename Ttype>
Ttype (*create_4d_darray())[ly][lz][Q] {
  // const int d_lx = lx, d_ly = ly, d_lz = lz, d_n = n;
  //Ttype array_4d[lx][ly][lz][Q];
  //typedef Ttype array_4d[ly][lz][Q];
  //array_4d* dptr_4d_array;
  Ttype(*dptr_4d_array)[ly][lz][Q];
  cudaMalloc((void**)&dptr_4d_array,
             (lx * ly * lz * Q) * sizeof(Ttype));
  return dptr_4d_array;
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

void set_array(int**** array) {
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

void print_array(int**** array) {
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

  //int lx=10,ly=10,lz=5,Q=19;
  int**** host_4d_array=create_4d_harray<int>();
  int(* device_4d_array)[ly][lz][Q]=create_4d_darray<int>();
  
  const dim3 blockSize(BLKXSIZE, BLKYSIZE, BLKZSIZE);
  const dim3 gridSize(((lx + BLKXSIZE - 1) / BLKXSIZE),
                      ((ly + BLKYSIZE - 1) / BLKYSIZE),
                      ((lz + BLKZSIZE - 1) / BLKZSIZE));

  set_array(host_4d_array);
  print_array(host_4d_array);
  
  // allocate GPU device buffers

  cudaCheckErrors("Failed to allocate device buffer");
  cudaMemcpy(device_4d_array, host_4d_array, (lx * ly * lz * Q) * sizeof(int),
             cudaMemcpyHostToDevice);
  
  // compute result
  gpu_array_swap<<<gridSize, blockSize>>>(device_4d_array);
  cudaCheckErrors("Kernel launch failure");
  // copy output data back to host

  cudaMemcpy(host_4d_array, device_4d_array, ((lx * ly * lz * Q) * sizeof(int)),
             cudaMemcpyDeviceToHost);
  cudaCheckErrors("CUDA memcpy failure");
  free_4d_harray(host_4d_array);
  cudaFree(device_4d_array);
  cudaCheckErrors("cudaFree fail");
  return 0;
}
