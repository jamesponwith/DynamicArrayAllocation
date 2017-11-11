/* 
 * James Ponwith
 * Project03
 * ReadInTestResults
 * This program will dynamically allocate memory to a data set
 * of test results and preform a few statistical equations.
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readfile.h"

/* Function forward declarations */
double *getValues(int *size, int *capacity, char *filename);
double getMean(double *array, int *size);
double getMedian(double *array, int *size);
double getStdDev(double *array, int *size, double mean);

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf ("usage: ./stats filename\n");
		exit(1);
	}

    /* argv[1] contains file name */
	printf("filename %s\n\n", argv[1]);

	int size = 0;
	int capacity = 20;

	double *array = getValues(&size, &capacity, argv[1]);
	double mean = getMean(array, &size);
	double median = getMedian(array, &size);
	double stddev = getStdDev(array, &size, mean);

	printf("\nStatistics:\n");
	printf("-------------\n");
	
	printf("%s%f\n", "Mean:", mean);
	printf("%s%f\n", "Median:", median);
	printf("%s%f\n", "Standard deviation:", stddev); 
	printf("%s%u\n\n", "Unused slots:", (capacity - size));	
	
	free(array);
	return 0;
}

/** 
 * Takes size and capacity of a array which will be allocated within the function. The 
 * array will be filled with the values that are read in from the file (the third parameter).
 * As it reads in values, if the number of elements read in reaches the original capacity, it 
 * will double and continue reading values. 
 * @param Pointer to the size of the array which starts as zero and is represented  by i
 * @param Pointer to the capacity of the array which is doubles if i (the size) reaches capacity
 * @param Pointer to file name which is stored in argv[1]
 * @return A full array with the correctly allocated amount of memory 
 */
double *getValues(int *size, int *capacity, char *filename) {
	 double x;
	 double *array = malloc( *capacity * sizeof(double)); // Allocates memory for 20 ints
     int ret = openFile(filename);

	/* File validation */
     if(ret == -1) {
        printf("open file failed\n\n");
        exit(1);
     }
     else {
         printf("%s\n", "open file success");
     }

     ret = readDouble(&x);
     
	 int i = 0; 
	
	/* Loop while the file is open and has more numbers to be read */
	 while(ret != -1) {
	    
        /* Doubles memory allocation if array becomes to large */
		if(i == *capacity) {
		 	double *array2 = malloc(2 * (*capacity) * sizeof(double));
			int j;

            /* Transfers original array to doubled memory array */
			for(j = 0; j < *capacity; j++) {
				array2[j] = array[j]; 
			} 

			free(array);
			array = array2;
			*capacity *= 2;
		}	// End of if statement to check if array needs doubling
		array[i] = x; // Assigns the file values to array
		i++; // Number of used slots
		ret = readDouble(&x);
     } // End while loop checking is file is open or has more contents
	*size = i; // Transfer number of slots used to pointer size
	
	closeFile(); 
	return array;
}

/*
 * Gets the mean of the array
 * @param Pointer to array created by getValues
 * @param Pointer to size for looping purposes
 * @return mean value
 */
double getMean(double *array, int *size) {
	double mean = 0;
	double total = 0;
	
	int i;
	for(i = 0; i < *size; i++) {
		total += array[i];
	}

	mean = total / *size;
	return mean;
}

/*
 * Sorts the array and returns the median number
 * @param Pointer to the array created in getValues
 * @param Pointer to size for looping purposes
 * @return median number
 */ 
double getMedian(double *array, int *size) {	
    double median = 0;
	int i, n;

	/* Sorts array*/
    for(i = 0; i < *size; i++) {
		for(n = 1; n < *size; n++) {
			if(array[i] > array[n]) {
				double swap;
				swap = array[i];
				array[i] = array[n];
				array[n] = swap;
			}
		}
	}
    
    /* Checks if array has even number of elements */
	if(*size % 2 == 0) {
		median = (array[*size/2] + array[(*size/2) - 1]) / 2;
	}
    
    /* If not even */
	else {
		median = array[*size/2];
	}

	return median;
}

/*
 * Finds standard deviation of the array
 * @param Pointer to array created by getValues
 * @param Pointer to size for looping purposes 
 * @param Mean value because the average is required for standard deviation 
 * @return Standard Deviation 
 */
double getStdDev(double *array, int *size, double mean) {	
	double stddev = 0;
	double  sum = 0;
	int counter = 0;

	int i;

    /* Sums the squares of the differnece of mean */
	for(i = 0; i < *size; i++) {
		sum += pow((array[counter] - mean), 2);
		counter++;
	}
	double variance = sum / (*size - 1);
	stddev = sqrt(variance);

	return stddev;
}

