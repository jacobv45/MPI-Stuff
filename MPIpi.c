#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv){

int rank;
int size;

int i,j;
int x,y,r;
int count=0;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

srand((unsigned)time(NULL));

for(j=0,j<size,j++){
	if(j==rank){
		for(i=0,i<100,i++){
			x=rank/size+(double)rand()/(size*RAND_MAX);
			y=(double)rand()/RAND_MAX;
			r=x*x+y*y;
			if(r<=1){count=count+1}
		}		
	}
}




MPI_Finalize();
return 0;
}
