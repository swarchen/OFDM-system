//
//  QAM16_mapping.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/9.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define three 0.94868329805
#define two 0.63245553203
#define one 0.31622776601
#define N 1048576
#define bit 4


int main(int argc, const char * argv[]) {
    double *bitstream;
    bitstream=malloc(sizeof(double) * N);

    
    FILE *fin = fopen("bitstream.txt", "r");
    FILE *fout = fopen("QAM16.txt", "w"); //write only
    for (int k = 0; k < N; k++) {
        fscanf(fin,"%15lf",&bitstream[k]);
        //printf("%d \n", bitstream[k]);
    }
    fclose(fin);
    for (int i = 0; i < N; i += 4) {
        if (bitstream[i] == 0 && bitstream[i + 1] == 0 && bitstream[i + 2] == 0 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", -three, -three);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 0 && bitstream[i + 2] == 0 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", -three, -one);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 0 && bitstream[i + 2] == 1 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", -three, three);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 0 && bitstream[i + 2] == 1 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", -three, one);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 1 && bitstream[i + 2] == 0 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", -one, -three);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 1 && bitstream[i + 2] == 0 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", -one, -one);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 1 && bitstream[i + 2] == 1 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", -one, three);
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 1 && bitstream[i + 2] == 1 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", -one, one);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 0 && bitstream[i + 2] == 0 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", three, -three);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 0 && bitstream[i + 2] == 0 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", three, -one);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 0 && bitstream[i + 2] == 1 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", three, three);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 0 && bitstream[i + 2] == 1 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", three, one);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 1 && bitstream[i + 2] == 0 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", one, -three);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 1 && bitstream[i + 2] == 0 && bitstream[i + 3] == 1) {
            fprintf(fout,"%lf %lf \n", one, -one);
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 1 && bitstream[i + 2] == 1 && bitstream[i + 3] == 0) {
            fprintf(fout,"%lf %lf \n", one, three);
        }else{
            fprintf(fout,"%lf %lf \n", one, one);
        }
    }
    
    fclose(fout);
    system("pause");
    return 0;
}