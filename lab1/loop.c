#include <stdio.h>
#include <stdlib.h>

void loop(float a[], float b[], float c[]){
    for(int i = 0; i < 4; i++){
        c[i] = a[i] + b[i];
    }
}

int main(int argc, char** argv){
    int iteration_num = atoi(argv[1]);
    float a[4] = {300.0, 4.0, 4.0, 12.0};
    float b[4] = {1.5, 2.5, 3.5, 4.5};
    float c[4] = {0.0, 0.0, 0.0, 0.0};

    for(int i = 0; i < iteration_num; i++){
        loop(a, b, c);
    }
    
    return 0;
}