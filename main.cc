#include <iostream>
#include <stdlib.h>
#include <time.h> 

int main(void)
{
srand((unsigned)time(NULL)); 
for(int i = 0; i < 100;i++ ) 
    std::cout << rand() / double(RAND_MAX) << std::endl;
return 0;
}

