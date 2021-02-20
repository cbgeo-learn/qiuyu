#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <cuda.h>

__global__ void vector_sum_kernel(int* vec_gpu,int N,int* vec_sum_device)
{
   // kernel function cannot be a member function of class
   // caculate the summation of a vector on device
   for (int i = 0; i<N; ++i)vec_sum_device[0]+=vec_gpu[i];
}

class GpuVector
{
public:
  //To transfer the vector from cpu to gpu
  GpuVector(int* ,int);
 ~GpuVector();
  void sum();
  int* vec_sum_device=0;
  int vec_sum_host=0; 
  int* vec_gpu;

private:
  int N_;//the number of integers
};

