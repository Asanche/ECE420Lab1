/*
    Authors: Adam Sanche & Niko Somos
    Class: ECE 420 Lab H42
    Professor: D. Niu

    == Explanation ==

    == Global Variables ==
        int** matrix_a - the first input matrix
        int** matrix_b - the second otput matrix
        int** matrix_c - the output matrix
        int size - a dimension of a square size X size matrix

    == Functions == 
        void* Calculate_element(void* arg_p) - Calculates the elements of the output matrix
        int main(int argc char* argv[]) - takes a thread count from the command line, reads
            two input matrices, and creates threads to calculate the output matrix in parallel
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab1_IO.h"
#include "timer.h"

//Memory locations of matrices and sizes as global variables.
int** matrix_a; int** matrix_b; int**matrix_c;
int size;

void freeMatrix(int **matrix, int dimension) {
    /*
    == Explanation ==
        Frees all arrays within the square matrix passed to it preventing memory leaks
    == Inputs ==
        int ** matrix - pointer to the matrix
        int dimension - dimension of the square matrix
    == Outputs ==
        N/A
    */

    int i;
    for (i = 0; i < dimension; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void* Calculate_element (void* arg_p)
{
    /*
    == Explanation ==
        This function calculates the individual element of the output matrix.
        If follows the matri multiplication algorithm, meaning that it 
        performs element-wise multiplication between a row "x" in matrix_a
        and column "y" in matrix_b and sums the products.

    == Inputs ==
        void* arg_p - this exact value corresponds to which thread this is,
            not as in current thread, but as in absolute count. If it is 
            the 100th thread made, but there are only 5 threads running
            in parallel, arg_p is 99, not 5. Used to calculate the x row
            and y column for the element to be calculated.

    == Outputs ==
        N/A
    */
    long element_index = (long) arg_p;
    long x = element_index % size;
    long y = element_index / size;
    matrix_c[x][y] = 0;
    
    for (int i = 0; i < size; i++)
    {
        matrix_c[x][y] += matrix_a[x][i] * matrix_b[i][y];
    }
    pthread_exit(NULL);
} 

int main (int argc, char* argv[])
{
    /*
    == Explanation ==
        This takes an argument from the command line (argv[1]) that corresponds
        to the quantity of threads to be used for the matrix multiplication.
        It calls a function in lab1_IO.c that reads matrix_a and matrix_b from 
        data_input.txt.
        It instantiates a number of threads (at a time) equivalent to the 
        quantity specified by the user, and then joins the threads, repeating 
        this process until all of the elements of the result matrix (global 
        variable int** matrix_c have been calculated)

    == Inputs ==
        int argc - number of command line arguments
        char* argv[] - array of command line arguments
            - argv[1] should be # of threads to be used

    == Outputs ==
        N/A
    */

    //Checks to make sure that there was an inputted number of threads
    if(argc < 2)
    {
        printf("You didn't input a number of threads... please rerun like \"./main <threads>\"");
        return 1;
    }

    //calculation timint values
    double start; double end;

    //threads ininitialization and mallocing for the threads
    int thread_count = strtol(argv[1], NULL, 10);
    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t));

    //loads from input_data.txt to the matrix pointers
    Lab1_loadinput(&matrix_a, &matrix_b, &size);

    matrix_c = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
      matrix_c[i] = malloc(size * sizeof(int));
    }

    int area = size * size;

    //caculates time as well as initiating the threads etc...
    GET_TIME(start);
    for(long i = 0; i < area;){

        //create allowed amount of threads
        for(long thread = 0; thread < thread_count; thread++)
        {
            pthread_create(&thread_handles[thread], NULL, Calculate_element, (void*)i);
            i++;
        }
    
        //joint created threads
        for(long thread = 0; thread < thread_count; thread++)
        {
            pthread_join(thread_handles[thread], NULL);
        }
    }
    GET_TIME(end);

    //Creates data_output.txt with results
    Lab1_saveoutput(matrix_c, &size, end-start);

    //free all memory used
    freeMatrix(matrix_a, size);
    freeMatrix(matrix_b, size);
    freeMatrix(matrix_c, size);
    free(thread_handles);

    pthread_exit(NULL);
}



