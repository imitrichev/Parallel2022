//mpicxx -std=c++11 armiya3.cpp && mpirun -np 21 ./a.out
#include <thread>
#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <vector>
#include <random>
using namespace std;

int main(int argc, char* argv[])
{
	int rank,size;
	vector<int> recieved_data;
	int* data;

	int errcodes;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm intercomm, parentcomm;

	MPI_Comm_get_parent(&parentcomm);

if (parentcomm == MPI_COMM_NULL)
{
	data=new int[size];
 	data[rank] = (rank + 1) * 10;						//теперь data создаётся внутри каждого процесса

	for (int i = 0; i <= 20; ++i) {
		MPI_Bcast(&data[i], 1, MPI_INT, i, MPI_COMM_WORLD);
		recieved_data.push_back(data[i]);
	}

	if (rank == 0) {
		cout << "recieved data in " << rank << endl;
		for (int n : recieved_data) {
			cout << n << " ";
		}
		fflush(stdout);
	}

// should be called from EVERY process!
//https://stackoverflow.com/a/43052633
		MPI_Comm_spawn("./a.out", MPI_ARGV_NULL, 1, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm, &errcodes);

	if (rank == 0) {
		int size = recieved_data.size();
		for (int n=0; n<size; n++) {
			data[n]=recieved_data[n];
		}

		MPI_Send(&size, 1, MPI_INT, 0, 1, intercomm);
		MPI_Send(data, size, MPI_INT, 0, 0, intercomm);
	}

}
else
{
	MPI_Status status;
	int size;
	cout << "I'm the spawned";
	MPI_Recv(&size, 1, MPI_INT, 0, 1, parentcomm, &status);
	data=new int[size];
	MPI_Recv(data, size, MPI_INT, 0, 0, parentcomm, &status);
	cout << "recieved data" << endl;
	for (int n=0; n<size; n++) {
		cout << data[n] << " ";
	}
	fflush(stdout);
}
	delete data;
	MPI_Finalize();
	return 0;
}
//int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info,
//                 int root, MPI_Comm comm, MPI_Comm * intercomm, int array_of_errcodes[])
//comm (in) = intracommunicator containing group of spawning processes
//intercomm (out) = intercommunicator between original group and the newly spawned group (handle)
//intercomm = between groups. Rank is relative. Does not support collective operations.
//intracommunicator = 1 group (e.g., MPI_COMM_WORLD)