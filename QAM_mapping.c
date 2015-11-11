//
//  QAM_mapping.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/7.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1048576
#define bit 2


int main(int argc, const char * argv[]) {
    double *bitstream;
    bitstream=malloc(sizeof(double) * N);
    
    
    FILE *fin = fopen("bitstream.txt", "r");
    FILE *fout = fopen("QAM.txt", "w"); //write only
    for (int k = 0; k < N; k++) {
        fscanf(fin,"%15lf",&bitstream[k]);
        //printf("%d \n", bitstream[k]);
    }
    fclose(fin);
    for (int i = 0; i < N; i += 2) {
        if (bitstream[i] == 0 && bitstream[i + 1] == 0) {
            fprintf(fout,"-0.707 -0.707 \n");
        }else if (bitstream[i] == 0 && bitstream[i + 1] == 1) {
            fprintf(fout,"-0.707 0.707 \n");
        }else if (bitstream[i] == 1 && bitstream[i + 1] == 0) {
            fprintf(fout,"0.707 -0.707 \n");
        }else{
            fprintf(fout,"0.707 0.707 \n");
        }
    }

    fclose(fout);
    system("pause");
    return 0;
}