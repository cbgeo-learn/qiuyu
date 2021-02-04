#include <iostream>
#include "vector_summation.cuh"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cuda.h>

GpuVector::GpuVector(int* vec_cpu,int nbytes){
  /* allocate GPU mem */    
  cudaMallocManaged(&vec_gpu,nbytes);
  cudaMemcpy(vec_gpu, vec_cpu, nbytes, cudaMemcpyHostToDevice);
}

void GpuVector::sum()
{vector_sum_kernel<<<1, 1>>>(vec_gpu,length_,vec_sum);}

GpuVector::~GpuVector(){cudaFree(vec_gpu);}

int main()
{ /*Declare a vector on the host*/
  int* vec_cpu;
  int N=100;
  int nbytes = N * sizeof(int);
  vec_cpu = (int *) malloc(nbytes);
  for (int i = 0; i < N; ++i)vec_cpu[i]=10;
  
  cudaThreadSynchronize();
  
  // Run kernel on 1M elements on the GPU
  GpuVector vec_gpu(vec_cpu,nbytes);
  
  std::cout<<vec_gpu.vec_sum<<std::endl;
  vec_gpu.sum();
  std::cout<<vec_gpu.vec_sum<<std::endl;
  
  cudaDeviceSynchronize();
  int vec_cpu_sum=0;
  for( size_t i = 0 ; i < N ; i++ )
  {vec_cpu_sum+=vec_cpu[i];}
  std::cout<<vec_cpu_sum<<std::endl;
  
  free(vec_cpu); 
}

