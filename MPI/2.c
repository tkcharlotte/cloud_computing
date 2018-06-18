#include "stdio.h"
#include "mpi.h"
#include "math.h"
#include "stdlib.h"
 #include <time.h>
int main(int argc, char **argv)
{
    int input,in;
    time_t ts;
    srand((unsigned int )time(&ts));
    sscanf(argv[1],"%d",&input);
    sscanf(argv[2],"%d",&in);
    int rank,size,data[input];
    for(int i=0;i<input;i++)
    {
        int a = rand() % (in)+1;
        data[i]=a;
   //  printf("%d ",a);
    }
  //  printf("\n");
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    int n=input/size;
    int a=input%size;
    if(rank==0)
   {
  int line=rank*n,max=data[line];
  printf("proceess %d computer number %d to number %d\n",rank,line,line+n-1);
   for(int i=0;i<n;i++)
   {
       if(data[line+i]>=max)
       {
           max=data[line+i];
       
       }
   }
    printf("process %d max is %d\n",rank,max);
   for(int i=1;i<size;i++)
   {
       int x;
    MPI_Recv(&x, 1, MPI_DOUBLE, i, 10, comm, MPI_STATUS_IGNORE);
    printf("process %d max is %d\n",i,x);
    if(x>=max)
    {
      max=x;
    }
   }
   printf("final max is %d\n",max);
   }
   else if(rank==size-1)
   {

     int line=rank*n,max=data[line];
     printf("proceess %d computer number %d to number %d\n",rank,line,line+a+n-1);
   for(int i=0;i<a+n;i++)
   {
  
       //printf("max  = %d\n",max);
       if(data[line+i]>=max)
       {
           max=data[line+i];
       } 
    MPI_Send(&max,1,MPI_DOUBLE,0,10,comm);
   }

   }
   else
   { 
       int line=rank*n;
       int max=data[line];
    printf("proceess %d computer number %d to number %d\n",rank,line,line+n-1);
   for(int i=0;i<n;i++)
   {
 
       //printf("max  = %d\n",max);
       if(data[line+i]>=max)
       {
           max=data[line+i];
       }
   }
    //printf("max is %d\n",max);
    MPI_Send(&max,1,MPI_DOUBLE,0,10,comm);
    }
    MPI_Finalize();
}