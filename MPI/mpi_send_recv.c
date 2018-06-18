#include<stdio.h>
#include<mpi.h>
 int main(int argc, char const *argv[])
 {
 	int rbuf[3],i,rank,name,size;
 	MPI_Init(&argc,&argv);
 	MPI_Status status;
 	MPI_Comm_size(MPI_COMM_WORLD,&size);
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 	if(rank == 0){
 		name = rank+1;
 		MPI_Send(&name,1,MPI_INT,1,1,MPI_COMM_WORLD);
 	}
 	else if(rank == 1)
 		MPI_Recv(&name,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
 	printf("%d\n",name );
 	
 	MPI_Finalize();
 	return 0;
 }
