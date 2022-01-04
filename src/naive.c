#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
pthread_mutex_t l1 = PTHREAD_MUTEX_INITIALIZER;

struct range
{
    int start;
    int end;
    int *a;
};

int check_prime(int k){
    for(int i=2;i<=sqrt(k);i++){
        if(k%i==0){
            return 0;
        }
    }
    return 1;
}

void* get_primes(void* ptr){
    clock_t start_t, end_t;
    start_t = clock();
    struct range* r = (struct range*)ptr;
    int start = r->start;
    int end = r->end;
    int* store = r->a;

    for(int i=start;i<end;i++){
        if(check_prime(i)==1){
            store[i] = i;
        }else{
            store[i]=0;
        }
    }
    end_t = clock();
    double total_t = (double)(1.0*(end_t-start_t))/(1.0*CLOCKS_PER_SEC);
    pthread_mutex_lock( &l1 );
    FILE *fp = fopen("./output/naive_time.data","aw");
    fprintf(fp,"%f\n",  total_t);
    fclose(fp);
    pthread_mutex_unlock( &l1 );
    free(r);
}

int main(int argc, char* argv[]){
    int n=atoi(argv[1]);
    int t=atoi(argv[2]);
    int* a = (int*) malloc(sizeof(int)*1000001);
    a[0]=0;
    a[1]=0;
    pthread_t threads[t];
    int s=2;
    int e=n+1;
    int step = (n-1)/t;
    int rc;
    for(int i=0;i<t;i++){
        struct range* r = (struct range*)malloc(sizeof(struct range));
        r->start = s+i*step;
        r->a = a;   
        if(i==t-1){
            r->end = e;   
        }else{
            r->end = s+(i+1)*step;
        }
        rc =  pthread_create( &threads[i], NULL, get_primes, (void*) r);
    }

    for(int i=0;i<t;i++){
        pthread_join(threads[i],NULL);
    }
    
    
    FILE *fp = fopen(argv[3],"w");
    for(int i=2;i<=n;i++){
        if(a[i]!=0){
            fprintf(fp,"%d\n",a[i]);
        }
    }
    fclose(fp);
    free(a);
}