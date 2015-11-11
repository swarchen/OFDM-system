//
//  main.c
//  fft
//
//  Created by 吳朝成 on 2015/10/17.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#define Num 1048576
#define bit 2

// bit reverse function
int IBR(int M, int NU){
    int IBR = 0;
    int J2 = 0;
    int I1;
    for (I1 = 1; I1 <= NU; I1++) {
        J2 = M / 2;
        IBR = 2 * IBR + (M - 2 * J2);
        M = J2;
    }
    return IBR;
}

//



//fft function
void fft(int N, double x_Re[N], double x_Im[N], int inverse){
    int r = log2(N);
    int NU = r; // total stage of butterfly
    int N2 = N / 2; // half the number of points in FFT
    int NU1 = r - 1;
    int k = 0;
    int l = 1;
    int M = 0;
    int P = 0;
    double T3_Re = 0;
    double T3_Im = 0;
    double T1_Re = 0;
    double T1_Im = 0;
    int i = 0;
    int I = 0;
    
   
    while (l <= r) {
        //printf("l=%d\n\n",l);
        do{
            for (I = 1; I <= N2; I++) {
                M = (int) k / pow(2, NU1);
                P = IBR(M, NU);
                //printf("M=%d \n",M);
                //printf("k=%d \t I = %d \t k+N2=%d\n",k,I,(k+N2));
                //printf("I = %d \t",I);
                
                //inverse == 1 means IFFT
                if (!inverse) {
                    T1_Re = cos(2 * P * M_PI / N) * x_Re[k + N2] + sin(2 * P * M_PI / N) * x_Im[k + N2];
                    T1_Im = cos(2 * P * M_PI / N) * x_Im[k + N2] - sin(2 * P * M_PI / N) * x_Re[k + N2];
                }else{
                    T1_Re = cos(2 * P * M_PI / N) * x_Re[k + N2] - sin(2 * P * M_PI / N) * x_Im[k + N2];
                    T1_Im = cos(2 * P * M_PI / N) * x_Im[k + N2] + sin(2 * P * M_PI / N) * x_Re[k + N2];
                }
                x_Re[k + N2] = x_Re[k] - T1_Re;
                x_Re[k] = x_Re[k] + T1_Re;
                
                x_Im[k + N2] = x_Im[k] - T1_Im;
                x_Im[k] = x_Im[k] + T1_Im;
                k += 1;
                
            }
            k += N2;
        }while (k < N - 1);
        l += 1;
        N2 /= 2;
        NU1 -= 1;
        k = 0;
    }
    for (k = 0; k < N; k++) {
        i = IBR(k, NU);
        if (i > k) {
            //printf("i = %d \t k = %d \n",i,k);
            T3_Re = x_Re[k];
            x_Re[k] = x_Re[i];
            x_Re[i] = T3_Re;
            
            T3_Im = x_Im[k];
            x_Im[k] = x_Im[i];
            x_Im[i] = T3_Im;
        }
        if (inverse) {
            x_Re[k] /= N;
            x_Im[k] /= N;
        }
    }
    
};

int main(int argc, char* argv[]) {
    // insert code here...
    
    if ( argc != 6 )  //argc should be 2 for correct execution
    {
         //We print argv[0] assuming it is the program name
        printf( "need 5 arguments\n");
        printf( "1st is this prgram, 2nd is 0 or 1 for FFT or IFFT respectively. \n");
        printf( "3rd is input data filename, 4nd is the output filename, 5nd is number of bits \n");
        printf( "6nd is the guard interval start\n");
        exit(1);
    }
    int N = atoi(argv[4]);
    int CP = atoi(argv[5]);
    double *x_Re, *x_Im;
        x_Re=malloc(sizeof(double) * ((Num/bit/64)*80));
        x_Im=malloc(sizeof(double) * ((Num/bit/64)*80));
    int i = 0;
    int inverse = atoi(argv[1]);
    int k;
    FILE *fin  = fopen(argv[2], "r"); // read only
    FILE *fout = fopen(argv[3], "w"); //write only
    // test for files not existing.
    if (fin == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }
    if (inverse) {
        for (i = 0; i < (Num/bit); i++)
        {
            fscanf(fin,"%lf%lf",&x_Re[i],&x_Im[i]);
            //printf("\t%15f\t%15f\n",x_Re[i],x_Im[i]);
        }
        for (int j = 0; j < (Num/bit); j += 64) {
            fft(N, &x_Re[j], &x_Im[j], inverse);
            for (k = 0; k < N; k++) {
                fprintf(fout,"%15f\t%15f\n",x_Re[k + j],x_Im[k + j]);
                //printf("the %d term is :%15f\t%15f\n",k + j,x_Re[k + j],x_Im[k + j]);
            }
        }

    }else{
        for (i = 0; i < ((Num/bit/64)*80); i++)
        {
            fscanf(fin,"%lf%lf",&x_Re[i],&x_Im[i]);
            //printf("\t%15f\t%15f\n",x_Re[i],x_Im[i]);
        }
        for (int j = 0; j < ((Num/bit/64)*80); j += 80) {
        
            fft(N, &x_Re[j + CP + 16], &x_Im[j + CP + 16], inverse);
            for (k = 0; k < N; k++) {
                fprintf(fout,"%15f\t%15f\n",x_Re[k + j + CP + 16],x_Im[k + j + CP + 16]);
                //printf("the %d term is :%15f\t%15f\n",k + j,x_Re[k + j],x_Im[k + j]);
            }
        }
    }
    
    
    
    
    free(x_Re);
    free(x_Im);
    fclose(fin);
    fclose(fout);
    system("pause");
    return 0;
}


