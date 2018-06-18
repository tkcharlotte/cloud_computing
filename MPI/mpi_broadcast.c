#include<stdio.h>
#include<mpi.h>
 int main(int argc, char const *argv[])
 {
 	int arr[3],i,rank;
 	MPI_Init(&argc,&argv);
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 	if(rank == 0)
 	{
 		for(i=0;i<3;i++)
 			arr[i] = i+1;
 	}
 	MPI_Bcast(arr,3,MPI_INT,0,MPI_COMM_WORLD);
 	printf("Process %d receives:\n",rank );
 	for(i=0;i<3;i++)
 	{
 		printf("%d\n",arr[i] );
 	}
 	putchar('\n');
 	MPI_Finalize();
 	return 0;
 }