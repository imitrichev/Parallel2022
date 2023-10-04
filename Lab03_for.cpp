#include <iostream>       // std::cout
#include <omp.h>
#include <vector>
using namespace std;
const int P = 4;
int main()
{
//measure execution time
	int tid, time;
	vector<int> vec(10000,1);
	vector<int> res(P,0);
	omp_set_num_threads(P);
	#pragma omp parallel private(time,tid)
	{
		tid = omp_get_thread_num();
		#pragma omp for
		for (int i=0; i<10000;i++)
		    res[tid]+=vec[i];
		time = omp_get_wtime();
		#pragma omp critical
		    cout << "Thread:" << tid << " sum: " << res[tid]<< endl;
		cout<< omp_get_wtime()-time << endl;
	}
	return 0;
}
