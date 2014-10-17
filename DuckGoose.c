#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main(argc, char **argv){

int rank,size;
int firsttag;
char *string;
string="Tag! You're It!";

int i;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

if(rank==0){
//send message to random (different) rank "Tag! You're It!"
srand(time(NULL));
firsttag=rand()%size+1
MPI_Send(string,100,MPI_CHAR,firsttag,MPI_ANY_TAG,MPI_COMM_WORLD);
}

if(rank==firsttag){
MPI_Recv(string,100,MPI_CHAR,0,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
MPI_Send(string,100,MPI_CHAR,firsttag+1,MPI_ANY_TAG,MPI_COMM_WORLD);
printf("%s, %d",string,rank)
}

for(i=firsttag+1,i<(size-1),i++){
	if(rank==i){
MPI_Recv(string,100,MPI_CHAR,i-1,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
MPI_Send(string,100,MPI_CHAR,i+1,MPI_ANY_TAG,MPI_COMM_WORLD);
printf("%s, %d",string,rank)
}
}

if(rank==size-1){
MPI_Recv(string,100,MPI_CHAR,size-2,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}

MPI_Finalize();
return 0;
}



