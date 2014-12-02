#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include <math.h>
#include <stdarg.h>

// Global vars
double p;
int width, height, t;
double* grid;
int my_id, nb_proc;

// Functions
double delta(double* neighb) {
	return (1 - p)*neighb[4] + (p/4)*(neighb[1]+neighb[3]+neighb[5]+neighb[7]);
}

void init_grid(){ // initialize global vars, parse input data
	printf("Waiting for input\n");
	int i,j, compt = 0;
	int tmp = 0;
	double x;
	scanf("%d", &width);
	scanf("%d", &height);
	scanf("%lf", &p);
	scanf("%d", &t);
	grid = malloc(sizeof(double)*width*height); // convention : grid[i][j] is grid[i*width + j]
	while(scanf("%d", &tmp)){
		if(tmp == 0){
			compt+=1;
			scanf("%d", &i);
			scanf("%d", &j);
			scanf("%lf", &x);
			if(i<height && j < width){
				grid[i*width+j] = x;
				printf("good entry for %lf at %d,%d \n", x, i, j);
			}
			else { printf("bad entry\n"); }
			if(compt > t) {break;}
		}
	}
}

void init_par(){ // initialize comm
	// 9 communicators per PU, there are width*height PUs
	
}

int main(int argc, char **argv) 
{
	init_grid();

	MPI_Init(&argc,&argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
  	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  	init_par();

	return 0; 
}