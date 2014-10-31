#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <mpi.h>

extern double montecarlo(int m);

int main(int argc, char** argv){

	int rank;
	int size;

	double partial;
	double total;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	srand((unsigned)time(NULL));         //seed random numbers with timemn

	/*
	   printf("%d %f\n",rank,montecarlo(100));
	   printf("%d %f\n",rank,montecarlo(10000));
	   printf("%d %f\n",rank,montecarlo(1000000));
	   */

	partial = montecarlo(1000000);
	MPI_Reduce(&partial,&total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);       //Awesome call according to Glen

	if(rank==0){
		printf("%d %f\n",rank,total/(size));
	}

	MPI_Finalize();
	return 0;
}

double montecarlo(int m){
	int i,count=0;                   //i, for looping. count number of hits in the circle
	double x,y,z;                    //pairs used for points in the unit square
	for ( i=0; i<m; i++) {              //100 iterations of generating points, calculating
		x = (double)rand()/RAND_MAX;     //length and counting if less than one
		y = (double)rand()/RAND_MAX;
		z = x*x+y*y;
		if (z<=1) count++;
	}
	return (double)count/m*4;
}

