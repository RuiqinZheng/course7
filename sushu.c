//#include "stdafx.h"
#include "string.h"
#include "stdio.h"
#include "math.h"
#include "mpi.h"
//#include <cstring>
int isPrime(int n)
{
	int m;
        int  flag=1;
		for(m=2;m<=sqrt(n*1.0);m++)
		{
			if(n%m==0)
			{
				flag=0;
				break;
			}
		}
		return flag;
}
int main(int argc, char *argv[])
{

    int a,mypid,sum=0,local=0,size,i;
	int flag;
    double starttime1,endtime1,starttime2,endtime2,t1,t2;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&mypid);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(mypid==0)
    {
        scanf("%d",&a);
    }
    MPI_Bcast(&a,1,MPI_INT,0,MPI_COMM_WORLD);
	starttime1=MPI_Wtime();
    for(i=mypid*2+1; i<=a; i+=size*2) //每个进程算自己的任务，保存在local中
    {
		local+=isPrime(i);
 
    }
    MPI_Reduce(&local,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);//进行归约，就是把所有进程的local加起来，得到总的素数个数
	endtime1=MPI_Wtime();
	t1=endtime1-starttime1;	
    if(mypid==0)
    {             
		 printf("并行时间=%f\n",t1);
        printf("并行素数个数是： %d\n",sum);     
    }


	

	
	sum=0;	
	starttime2=MPI_Wtime();
    if(mypid==0)
	{		
		
		    for(i=1; i<=a; i+=2) //每个进程算自己的任务，保存在local中
			{
				sum+=isPrime(i);
			}
	 endtime2=MPI_Wtime();
	 t2=endtime2-starttime2;
	 printf("串行素数个数是： %d\n",sum);

     printf("串行时间=%f\n",t2); 
     double d;
     d=t2/t1;	
     printf("speedup:%.9f\n",d);	
	} 	
	MPI_Finalize();
    return 0;
}
