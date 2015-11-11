//
//  bit_stream_generator.c
//  hw2
//
//  Created by 吳朝成 on 2015/11/7.
//  Copyright © 2015年 吳朝成. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

int main(int argc, const char * argv[]) {
    FILE *fout = fopen("bitstream.txt", "w"); //write only
    for (int k = 0; k < 1048576; k++) {
        fprintf(fout,"%d ",rand()%2);
        //printf("%15f\t%15f\n",x_Re[k],x_Im[k]);
    }
    fclose(fout);
    system("pause");
    return 0;
}