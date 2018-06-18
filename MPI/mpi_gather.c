#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
 int main(int argc, char const *argv[])
 {
 	int sbuf[3],i,rank,*rbuf,size,name;
 	MPI_Init(&argc,&argv);
 	MPI_Comm_size(MPI_COMM_WORLD,&size);
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// for(i=0;i<3;i++)
 // 			sbuf[i] = rank*10+i;
 	 name = rank+1;
 	if(rank == 0)
 		//rbuf = (int*)malloc(sizeof(int)*3*size);
 	//MPI_Gather(sbuf,3,MPI_INT,rbuf,3,MPI_INT,0,MPI_COMM_WORLD);
 		rbuf = (int*)malloc(sizeof(int)*size);
 	MPI_Gather(&name,1,MPI_INT,rbuf,1,MPI_INT,0,MPI_COMM_WORLD);

 	//MPI_Bcast(arr,3,MPI_INT,0,MPI_COMM_WORLD);
 	//printf("Process %d receives:\n",rank );
 	if(rank ==0){

 		printf("Process 0 receives:");
 		for(i=0;i<size;i++)	
 			printf("%d ",rbuf[i] );
 		
 		putchar('\n');
 	}
 	
 	MPI_Finalize();
 	return 0;
 }
