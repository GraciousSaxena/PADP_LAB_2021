#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    for(int size = 250; size<=1000; size+=250){
        int n_t = 1;
        printf("%d\t", size);
        while(n_t <= 8){
            int **arr1 = (int**)malloc(size*sizeof(int**));
            int **arr2 = (int**)malloc(size*sizeof(int**));
            int **mul  = (int**)malloc(size*sizeof(int**));
            for(int i=0; i<size; i++){
                arr1[i] = (int*)malloc(size*sizeof(int*));
                arr2[i] = (int*)malloc(size*sizeof(int*)); 
                mul[i]  = (int*)malloc(size*sizeof(int*)); 
            }
            int count = 1;
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    arr1[i][j] = count++;
                }
            }
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    arr2[i][j] = count++;
                }
            }
            int j,k;
            double x = omp_get_wtime();
            omp_set_num_threads(n_t);
            #pragma omp parallel for
            for(int i=0; i<size; i++){
                for(j=0; j<size; j++){
                    mul[i][j] = 0;
                    for(k=0; k<size; k++){
                        mul[i][j] += arr1[i][k] * arr2[k][j];
                    }
                }
            }
            n_t*=2;
            double y = omp_get_wtime();
            printf("%lf\t", y-x);
        }
        printf("\n");

    }
}