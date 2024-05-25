#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

 //defining array size
#define ARRAY_SIZE 107374182
static unsigned long array[ARRAY_SIZE];
static unsigned long sum = 0;

//function for initializing the array with numbers ranging from 1 to array size
void load_array(unsigned long array[]) {
	for (unsigned long i = 0;i < ARRAY_SIZE;i++)
	{
		array[i] = 10;
	}

}

int main() {

	load_array(array);
	double start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:sum)
	for (unsigned long j = 0;j < ARRAY_SIZE;j++)
	{
		sum = sum + array[j];
	}

	double end_time = omp_get_wtime();
	printf("Parallel Reduction Sum of the array: %lu\n", sum);
	printf("Parallel Reduction Execution Time: %f\n", (end_time - start_time));

	return(0);
}