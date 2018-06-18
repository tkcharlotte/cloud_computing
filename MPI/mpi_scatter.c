#include<stdio.h>
#include<mpi.h>
 int main(int argc, char const *argv[])
 {
 	int rbuf[3],i,rank,*sbuf,size;
 	MPI_Init(&argc,&argv);
 	MPI_Comm_size(MPI_COMM_WORLD,&size);
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
 	if(rank == 0){
 		sbuf = (int*)malloc(sizeof(int)*3*size);
 		for(i=0;i<3;i++)
 			sbuf[i] = 1+i;
 	}
 	MPI_Scatter(sbuf,3,MPI_INT,rbuf,3,MPI_INT,0,MPI_COMM_WORLD);;
 	printf("Process %d receives :",rank);
 	for(i=0;i<3;i++)
 		printf("%d",rbuf[i] );
 	
 	MPI_Finalize();
 	return 0;
 }
