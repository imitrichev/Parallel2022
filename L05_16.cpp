#include <iostream>       // std::cout
#include <omp.h>
using namespace std;
const int N = 1000;

int main()
{
	int A[N],B[N],C[N], i,n,nums=0;
	for (i=0;i<N;i++)
	{
		A[i]=i; B[i]=2*i;C[i]=0;
	}
	#pragma omp parallel shared (A,B,C) private (i,n,nums) num_threads(3)
	{
		n = omp_get_thread_num();
		#pragma omp for
		for (i=0;i<N;i++)
		{
			C[i]=A[i]+B[i];
			nums++;
		}
    	#pragma omp critical
    	{
    	    cout<<n<< " done "<<nums<<" iterations\n";
    	}
	}
	return 0;
}