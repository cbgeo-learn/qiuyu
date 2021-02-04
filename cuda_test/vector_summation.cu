#include <iostream>
#include "vector_summation.cuh"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cuda.h>
#include <stdio.h>

GpuVector::GpuVector(int* vec_cpu,int N):N_(N)
{
  // allocate GPU mem
  int nbytes=N_*sizeof(int);
  cudaMallocManaged((void **)&vec_gpu,nbytes);
  cudaMallocManaged((void **)&vec_sum_device,sizeof(int));
  cudaMemcpy(vec_gpu, vec_cpu, nbytes, cudaMemcpyHostToDevice);
  if(vec_gpu == NULL || vec_sum_device == NULL )
  {printf("couldn't allocate GPU memory\n");}
}

void GpuVector::sum()
{
  // 1D block
  int bs = 256;
  // 2D grid 
  int s = ceil(sqrt((N_/sizeof(int) + bs - 1.) / bs));
  dim3 grid = dim3(s, s);

  // call kernel function from the host
  vector_sum_kernel<<<grid, bs>>>(vec_gpu,N_,vec_sum_device);

  // transfer summation from device to host
  cudaThreadSynchronize();
  cudaMemcpy(&vec_sum_host, vec_sum_device, sizeof(int), cudaMemcpyDeviceToHost);
}

GpuVector::~GpuVector(){cudaFree(vec_gpu);}

int main()
{
  // declare a vector on the host
  int* vec_cpu;
  int N=100;
  int vec_cpu_sum=0;

  // allocate CPU mem
  int nbytes = N * sizeof(int);
  vec_cpu = (int *) malloc(nbytes);
  for (int i = 0; i < N; ++i)vec_cpu[i]=10;
  
  // declare a constructor
  GpuVector vec_gpu(vec_cpu,N);

  // calculate the sum on gpu
  std::cout<<"before running on gpu, sum="<<vec_gpu.vec_sum_host<<std::endl;
  vec_gpu.sum();

  // see if the summation is copied from gpu to cpu
  cudaDeviceSynchronize();
  std::cout<<"After running on gpu, sum="<<vec_gpu.vec_sum_host<<std::endl;

  // calculate the sum on cpu
  std::cout<<"Before running on cpu, sum="<<vec_cpu_sum<<std::endl;
  cudaDeviceSynchronize();
  for( size_t i = 0 ; i < N ; i++ )
  {vec_cpu_sum+=vec_cpu[i];}
  std::cout<<"After running on cpu, sum="<<vec_cpu_sum<<std::endl;
  
  free(vec_cpu); 
}

