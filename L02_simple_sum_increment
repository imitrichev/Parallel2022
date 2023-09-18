#include <iostream>
#include <thread>
#include <vector>
using namespace std;

const int num_threads = 10;

void function_to_call(vector<int> & v, int _id)
{
    for (int i=_id+num_threads; i<v.size(); i+=num_threads)
        v[_id]+=v[i];
}

int main()
{
    vector<int> v(10000,1);
	std::thread threads[num_threads];
	for (int i = 0; i < num_threads; i++)
	{
		threads[i] = std::thread(function_to_call, std::ref(v), i);
	}

	for (int i = 0; i < num_threads; ++i)
	{
		threads[i].join();	
	    std::cout << v[i] << std::endl;
	}
	return 0;
}
