#include<stdio.h>
#include"mpi.h"
int main(int argc, char const *argv[])
{
	int rank,size,arr[3],i;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	if(rank == 0){

		for(i=0;i<3;i++)
			arr[i] = i+1;
	}
	MPI_Bcast(arr,3,MPI_INT,0,MPI_COMM_WORLD);	
	for(i=0;i<3;i++)
		printf("%d",arr[i] );
	putchar("\n");
	MPI_Finalize();
	


	
	return 0;
	}
