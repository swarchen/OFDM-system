//
//  AWGN.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/8.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926536
#define Num 1048576
#define bit 2


double AWGN_generator(double x , int db)
{/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
    
    double temp1;
    double temp2;
    double result;
    double sigma = 0;
    int p;
    
    p = 1;
    
    while( p > 0 )
    {
        temp2 = ( rand() / ( (double)RAND_MAX ) ); /*  rand() function generates an
                                                    integer between 0 and  RAND_MAX,
                                                    which is defined in stdlib.h.
                                                    */
        
        if ( temp2 == 0 )
        {// temp2 is >= (RAND_MAX / 2)
            p = 1;
        }// end if
        else
        {// temp2 is < (RAND_MAX / 2)
            p = -1;
        }// end else
        
    }// end while()
    
    temp1 = cos( ( 2.0 * (double)PI ) * rand() / ( (double)RAND_MAX ) );
    sigma = sqrt(1/(64 * pow(10 ,((double) db / 10) )));
    result = sigma / 2 * sqrt( -2.0 * log( temp2 ) ) * temp1;
    
    return result;	// return the generated random sample to the caller
    
}// end AWGN_generator()

int main(int argc, const char * argv[]) {
    // insert code here...
    if ( argc != 4 )  //argc should be 2 for correct execution
    {
        //We print argv[0] assuming it is the program name
        printf( "need 3 arguments\n");
        printf( "1st is this prgram, 2rd is input data filename, 3nd is the output filename.  4th is db\n");
        exit(1);
    }
    int db = atoi(argv[3]);
    double *x_Re, *x_Im;
    x_Re=malloc(sizeof(double)* ((Num/bit/64)*80));
    x_Im=malloc(sizeof(double)* ((Num/bit/64)*80));
    
    FILE *fin  = fopen(argv[1], "r"); // read only
    FILE *fout = fopen(argv[2], "w"); //write only
    // test for files not existing.
    if (fin == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    
    for (int i = 0; i < ((Num/bit/64)*80); i++)
    {
        fscanf(fin,"%lf%lf",&x_Re[i],&x_Im[i]);
        //printf("\t%15f\t%15f\n",x_Re[i],x_Im[i]);
    }
    
    for (int j = 0; j < ((Num/bit/64)*80); j ++) {
            fprintf(fout,"%15f\t%15f\n",x_Re[j] + AWGN_generator(x_Re[j], db),x_Im[j] + AWGN_generator(x_Im[j], db));
        
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}
