#include<stdio.h>
#include<iostream>
#include<math.h>
#include<omp.h>
using namespace std;
int main(){
    double st, end, z, pi;
    int count=0;
    printf("iter/threads\t");
    for(int i=1; i<=8; i*=2){
        printf("pi\t\t%d\t\t", i);
    }
    for(int n = 1000; n<=1000000; n*=10){
        int n_threads = 1;
        printf("\n%d\t\t", n);
        while(n_threads<=8){
            count = 0;
            st = omp_get_wtime();
            omp_set_num_threads(n_threads);
            #pragma omp parallel for
            for(int i=0; i<n; i++){
                double x = (double)rand()/RAND_MAX;
                double y = (double)rand()/RAND_MAX;
                z = x*x+y*y;
                if(z<=1)
                    count++;
            }
            pi = (double)count/n*4;
            end = omp_get_wtime();
            n_threads*=2;
            printf("%lf\t%lf\t", pi, end-st);
        }
        cout<<endl;
    }
}