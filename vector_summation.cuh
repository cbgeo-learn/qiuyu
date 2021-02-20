#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

__global__ void vector_sum_kernel(int* vec_gpu,int length_,int& vec_sum){
for (int i = 0; i<length_; i++)vec_sum+=vec_gpu[i];
}

class GpuVector
{
public:
  //To transfer the vector from cpu to gpu
  GpuVector(int* ,int);
 ~GpuVector();
  void sum();
  int vec_sum=0.;

public:
  int* vec_gpu;
  int length_;//the length of the pointer transfered
};

