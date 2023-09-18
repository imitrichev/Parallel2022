#include <iostream>
#include <thread>
#include <vector>
using namespace std;

const int num_threads = 10;

void function_to_call(vector<int> & v, int a, int b)
{
    for (int i=a+1; i<b; i++)
        v[a]+=v[i];
}

int main()
{
    vector<int> v(10000,1);
	std::thread threads[num_threads];
	int amount_of_work=v.size()/num_threads;
	for (int i = 0; i < num_threads; i++)
	{
		threads[i] = std::thread(function_to_call, std::ref(v), amount_of_work*i, (i==num_threads+1?v.size():amount_of_work*(i+1)));
	}

	for (int i = 0; i < num_threads; ++i)
	{
		threads[i].join();	
	    std::cout << v[amount_of_work*i] << std::endl;
	}
	return 0;
}
