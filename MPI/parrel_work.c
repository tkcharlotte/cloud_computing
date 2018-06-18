#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
struct ownership{
	int owner;
	int number;
};

int main(int argc, char** argv){
	int rank,size;
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	int init[1];
	int *buff;
	int i,j,temp1,temp2;
	int final[1];
	srand(time(NULL)*rank);
	init[0]=rand()%100;
	printf("Process %d : %d first.\n", rank, init[0]);
	if(rank==0){
		buff=(int*)malloc(sizeof(int)*size);
	}
	MPI_Gather(init, 1, MPI_INT, buff, 1, MPI_INT, 0, comm);
	if(rank==0){
		struct ownership ship[size];
		for(i=0; i<size; i++){
			ship[i].owner=i;
			ship[i].number=buff[i];
		}
		qsort(ship,size,sizeof(ship[0],cmp));
		for(i=0; i<size; i++){
			buff[i]=ship[i].owner;
		}
	}
	MPI_Scatter(buff, 1, MPI_INT, final, 1, MPI_INT, 0, comm);
	printf("Process %d : %d finally.\n", rank, final[0]);
	MPI_Finalize();
	return 0;
}
int cmp(const void *a,const void *b){
	struct ownership * p1 = (struct ownership*)a;
	struct ownership * p2 = (struct ownership*)b;
	return p1->number < p2->number;
}