#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
 
int main( int argc, char* argv[] )
{
 
    // Size of vectors
    int n = 1000000;
 
    // Input vectors
    double *restrict a;
    double *restrict b;
    // Output vector
    double *restrict c;

    struct timeval start_time, stop_time, elapsed_time;
 
    gettimeofday(&start_time,NULL);

    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);
 
    // Allocate memory for each vector
    a = (double*)malloc(bytes);
    b = (double*)malloc(bytes);
    c = (double*)malloc(bytes);
 
    // Initialize content of input vectors, vector a[i] = sin(i)^2 vector b[i] = cos(i)^2
    int i;
    for(i=0; i<n; i++) {
        a[i] = sin(i)*sin(i);
        b[i] = cos(i)*cos(i);
    }   
 
    // sum component wise and save result into vector c
     #pragama acc kernels
     for(i=0; i<n; i++) {
        c[i] = a[i] + b[i];
    }
 
    // Sum up vector c and print result divided by n, this should equal 1 within error
    double sum = 0.0;

    for(i=0; i<n; i++) {
        sum += c[i];
    }
    sum = sum/(double)n;

    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    printf("final result: %f\n", sum);
    printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

    
 
    // Release memory
    free(a);
    free(b);
    free(c);
 
    return 0;
}
