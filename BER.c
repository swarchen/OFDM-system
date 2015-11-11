//
//  BER.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/9.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Num 1048576

int main(int argc, const char * argv[]) {
    
    
    if ( argc != 3 )  //argc should be 2 for correct execution
    {
        //We print argv[0] assuming it is the program name
        printf( "need 3 arguments\n");
        printf( "1st is this prgram, 2rd is input data filename, 3nd is the input filename.\n");
        exit(1);
    }
    double *bitstream, *demapping;
    bitstream=malloc(sizeof(double)*Num);
    demapping=malloc(sizeof(double)*Num);

    FILE *fin = fopen(argv[1], "r");
    FILE *fin2 = fopen(argv[2], "r"); //write only
    for (int k = 0; k < Num; k++) {
        fscanf(fin,"%15lf",&bitstream[k]);
        fscanf(fin2,"%15lf",&demapping[k]);
        //printf("%d \n", bitstream[k]);
    }
    fclose(fin);
    
    float totalerror = 0;
    for (int i = 0; i < Num; i ++) {
        if (bitstream[i] != demapping[i]) {
            totalerror++;
        }
    }
    
    printf("BER = %f / %d = %f \n",totalerror, Num, totalerror/Num);
    
    system("pause");
    return 0;
}