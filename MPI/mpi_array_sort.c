#include<stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include<time.h>
int max_num(int lower,int high,int a[]);
 int main(int argc, char** argv)
 {
	int size,rank,data[10000],per_proc_result,div,a,max_max,temp_max;
	srand((int)time(NULL));

 	for(int i=0;i<10000;i++){
			data[i] = rand()%10000+1;
			     }
 	MPI_Init(&argc,&argv);
 	MPI_Status Stas;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	div = 10000/size;
	per_proc_result = max_num(rank*div,(rank+1)*div-1,data);
	
	if(rank == 0){
			for(int i=1;i<size;i++)
			{
				MPI_Recv(&temp_max,1,MPI_INT,i,0,MPI_COMM_WORLD,&Stas);
				if(temp_max > max_max){
					max_max = temp_max;
				printf(" receive from %d and the  current max num is %d\n",i,max_max);

					}
				else
				printf("receive from %d and the  current max num is %d\n",i,max_max);
				
			}
			printf("then max num is %d\n",max_max );
		    }
	else
		{
		MPI_Send(&a,1,MPI_INT,0,0,MPI_COMM_WORLD);

		}
	MPI_Finalize();

 	return 0;
 }
 int max_num(int lower,int high,int a[]){
 	int max = 0,id,sum;
 	for(int i = lower;i<=high;i++)
 		if(a[i]>max)
 		{
 			max = a[i];
 			
 		}
 	return  max;


 }
