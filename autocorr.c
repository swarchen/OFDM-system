//
//  autocorr.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/8.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Num 1048576
#define bit 2


double autocorr(double x_pre[15], double x_last[15]){
    double total = 0;
    double mult_xy = 0;
    double sum_x = 0, sum_y = 0; // sum of x , y
    double sum_x2 = 0,sum_y2 = 0;// sum of square of x , y
    
    for (int i = 0; i < 16; i++) {
        mult_xy += x_pre[i] * x_last[i];
        sum_x += x_pre[i];
        sum_y += x_last[i];
        sum_x2 += x_pre[i] * x_pre[i];
        sum_y2 += x_last[i] * x_last[i];
    }
    
    
    total = (16 * mult_xy - sum_x * sum_y)/(sqrt(16 * sum_x2 - sum_x * sum_x))/(sqrt(16 * sum_y2 - sum_y * sum_y));
    return total;
}


int main(int argc, const char * argv[]) {
    if ( argc != 3 )  //argc should be 2 for correct execution
    {
        //We print argv[0] assuming it is the program name
        printf( "need 3 arguments\n");
        printf( "1st is this prgram, 2rd is input data filename, 3nd is the output filename. \n");
        exit(1);
    }
    
    double *x_Re, *x_Im;
    x_Re=malloc(sizeof(double)*((Num/bit/64)*80));
    x_Im=malloc(sizeof(double)*((Num/bit/64)*80));
    
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
    
    for (int j = 0; j < ((Num/bit/64)*80) - 80; j++) {
        fprintf(fout,"%15f\t%15f\n",autocorr(&x_Re[j], &x_Re[j + 64]),autocorr(&x_Im[j], &x_Im[j + 64]));
        
    }

    fclose(fin);
    fclose(fout);
    


    return 0;
}
 