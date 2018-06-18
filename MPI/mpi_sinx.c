#include<stdio.h>
#include<mpi.h>
#include<math.h>
#define PI 3.1415926
#define N 10000
double calculate(double a,double b);
int main(int argc, char const *argv[])
{

	int rank,size;
	int a=0;
	MPI_Init(&argc,&argv);
	MPI_Status Stas;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	//source=rank==0?size-1:rank-1;
	//dest = (rank+1)%size;
	if(rank == 0){
			double result;
			result = calculate(0,2*PI/40);
			double sum=0;
			for(int i=1;i<40;i++){
					MPI_Recv(&result,10,MPI_INT,i,0,MPI_COMM_WORLD,&Stas);
					sum = sum + result;
					printf("part sum = %lf\n",sum);
			}

			printf("the sum is %lf\n",sum);


	}
	else {
		double result ;
		result =calculate(2*PI/40*rank,2*PI/40*(rank+1));
		MPI_Send(&result,10,MPI_INT,0,0,MPI_COMM_WORLD);



	}

	MPI_Finalize();


	return 0;
}

double calculate(double a,double b){  
    double s=0,x=a;  
    for(int i=1;i<N+1;i++){//i从0开始从1开始是没有任何印象的  
        //以下两条语句的先后顺序可以任意，即取矩形的左边高或者右边的高度  
        x=(x+(b-a)/N);  
        s=s+sin(x)*((b-a)/N);//被积分的函数sin(x)写在这里  
    }  
    return s;  
} 


