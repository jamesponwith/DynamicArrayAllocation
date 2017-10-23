//
//  main.c
//  Comp280-p03
//
//  Created by James Ponwith on 10/7/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.g>
#include <math.h>
#include "readfile.h"



int x, ret, total;

       ret = openFile("input.txt");
       if(ret == -1) {
          printf("open file failed\n");
          exit(1);
       }
       
       total = 0;
       ret = readInt(&x);
       while(ret != -1) {
         total += x;
         ret = readInt(&x);
       }


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
