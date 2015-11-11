//
//  CP_insertion.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/8.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define Num 1048576
#define bit 2

int main(int argc, const char * argv[]) {
    // insert code here...
    if ( argc != 3 )  //argc should be 2 for correct execution
    {
        //We print argv[0] assuming it is the program name
        printf( "need 3 arguments\n");
        printf( "1st is this prgram, 2rd is input data filename, 3nd is the output filename. \n");
        exit(1);
    }

    double *x_Re, *x_Im;
    x_Re=malloc(sizeof(double)* (Num/bit - 1));
    x_Im=malloc(sizeof(double)* (Num/bit - 1));

    FILE *fin  = fopen(argv[1], "r"); // read only
    FILE *fout = fopen(argv[2], "w"); //write only
    // test for files not existing.
    if (fin == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    
    for (int i = 0; i < Num/bit; i++)
    {
        fscanf(fin,"%lf%lf",&x_Re[i],&x_Im[i]);
        //printf("the %d term is :\t%15f\t%15f\n",i,x_Re[i],x_Im[i]);
        
    }

    for (int j = 0; j < Num/bit; j += 64) {
        for (int q = 16; q > 0; q--) {
            fprintf(fout,"%15f\t%15f\n",x_Re[j + 64 - q],x_Im[j + 64 - q]);
            //printf("the %d term is : %15f\t%15f\n",j + 64 - q,x_Re[j + 64 - q],x_Im[j + 64 - q]);
        }
        for (int k = 0; k < 64; k++) {
            fprintf(fout,"%15f\t%15f\n",x_Re[k + j],x_Im[k + j]);
            //printf("%15f\t%15f\n",x_Re[k],x_Im[k]);
        }
    }

    fclose(fin);
    fclose(fout);
    
    return 0;
}
