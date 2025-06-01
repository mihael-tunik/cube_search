#include <stdio.h>
#include <gmp.h>
#include <omp.h>

typedef unsigned long long ull;
#define THREADS 16

#define TARGET  8
#define START   0
#define FINISH  50000000000

void check(mpz_t cube, ull n){
    char stats[10] = {0}, s[50] = {0}, pos = 0, cnt, pivot;
    mpz_get_str(s, 10, cube);

    while(s[pos])
        ++stats[pivot = s[pos++]-'0'];
    
    cnt = stats[pivot]; 
    for(int i = 0; i < 10; ++i)
        if(stats[i] && stats[i] != cnt)
            return;

    if(cnt == TARGET) 
        printf("%i : %llu : %s\n", cnt, n, s);
}

int main(void) {
    omp_set_num_threads(THREADS);

    ull task_start = START, task_finish = FINISH;
    ull start[THREADS] = {0}, finish[THREADS] = {0}, subtask_size = (task_finish-task_start)/THREADS;

    printf("run from %llu to %llu, target: %i\n", task_start, task_finish, TARGET);
    
    for(int i = 0; i < THREADS; ++i){
         start[i] = task_start + i*subtask_size;
         finish[i] = (i == THREADS-1) ? task_finish : (start[i] + subtask_size - 1);
         printf("thread %i: from %llu to %llu\n", i, start[i], finish[i]);
    }

    #pragma omp parallel for
    for(int t = 0; t < THREADS; ++t){
        mpz_t b, c;
        ull l = start[t], r = finish[t];
        
        mpz_init(b);
        mpz_init(c);
        mpz_ui_pow_ui(b, l, 2);
        mpz_mul_ui(b, b, 3);

        mpz_ui_pow_ui(c, l, 3);
       
        check(c, start[t]);

        for(ull n = l; n <= r; ++n){
            check(c, n);
            mpz_add_ui(c, c,  3*n+1);
            mpz_add(c, c, b);
            mpz_add_ui(b, b,  6*n+3);
        }

        mpz_clear(b);
        mpz_clear(c);
    }
    #pragma omp barrier
    return 0;
}
