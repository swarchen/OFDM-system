//
//  QAM_demapping.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/9.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Num 1048576
#define bit 2

int main(int argc, const char * argv[]) {
    
    if ( argc != 3 )  //argc should be 2 for correct execution
    {
        //We print argv[0] assuming it is the program name
        printf( "need 3 arguments\n");
        printf( "1st is this prgram, 2rd is input data filename, 3nd is the output filename.\n");
        exit(1);
    }
    double *x_Re, *x_Im;
    x_Re=malloc(sizeof(double)*(Num/bit));
    x_Im=malloc(sizeof(double)*(Num/bit));
    
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w"); //write only
    for (int k = 0; k < (Num/bit); k++) {
        fscanf(fin,"%lf%lf",&x_Re[k],&x_Im[k]);
        //printf("%d \n", bitstream[k]);
    }
    fclose(fin);
    
    for (int i = 0; i < (Num/bit); i ++) {
        if (x_Re[i] < 0 && x_Im[i] < 0) {
            fprintf(fout,"0 0 ");
        }else if (x_Re[i] < 0 && x_Im[i] > 0) {
            fprintf(fout,"0 1 ");
        }else if (x_Re[i] > 0 && x_Im[i] < 0) {
            fprintf(fout,"1 0 ");
        }else{
            fprintf(fout,"1 1 ");
        }
    }
    
    fclose(fout);
    system("pause");
    return 0;
}