#include <iostream>
#include <omp.h>  
using namespace std; 
int main() {
  #pragma omp parallel num_threads(3)
  {
      #pragma omp task
      {
        std::cout << "1 ";
      }
      std::cout << "2 ";
      #pragma omp taskwait
      std::cout << "3 ";
  }
  std::cout << std::endl;
}