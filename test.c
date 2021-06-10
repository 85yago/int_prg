#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CALLOC(number, type) \
    ((type *)calloc(number, sizeof(type)))

#define RANGE_MAX 1000
/* RANGE_MINは4以上であること */
#define RANGE_MIN 6

struct _has_size_array {
    int *data;
    int size;
};

typedef struct _has_size_array has_size_array;

has_size_array prime_list_func(int n) {
    /*
    エラトステネスの篩

    偶数は探索しない。
    探索はsqrt(n)まででよい、なぜならsqrt(n)〜nの整数は合成数ならばsqrt(n)までで割り切れているからである。

    またiが素数の時、2i, 3i, 4i, ...と印をつけるのではなく、3i, 5i, 7i, ...でよい。
    なぜなら偶数倍は2で割り切れるからである。
    さらにi=7の時を考えてみると、3iは3の、5iは5のそれぞれ倍数であるから、
    印をつけるのは7i, 9i, 11i, ...でよい。
    つまり、一般的にはiが素数の時印をつけるのは、i^2, i^2 + 2i, i^2 + 4i, ...
    でよい。
    */

    double x = n + 0.001;
    /* P. Dusart (2010), Estimates of Some Functions Over Primes without RH, arXiv preprint arXiv:1002.0442v1 p. 2. */
    int mayby_prime_count = ceil((x / log(x)) * (1 + (1.2762 / log(x))));
    int *large_prime_list = CALLOC(mayby_prime_count, int);

    int prime_count = 0;
    int *is_prime = CALLOC(n + 1, int);
    int i;
    for (i = 0; i <= n; i++) {
        is_prime[i] = true; /* 初期化 */
    }
    is_prime[0] = false;
    is_prime[1] = false;
    is_prime[2] = true;

    int search_limit = sqrt(n + 1); /* 探索限界 */
    for (i = 3; i <= search_limit; i += 2) {
        if (is_prime[i]) {
            int ii = i * i;
            int j;
            for (j = 0; ii + i * j <= n; j += 2) {
                is_prime[ii + i * j] = false; /* ふるう */
            }
        }
    }

    large_prime_list[prime_count] = 2;
    prime_count++;
    for (i = 3; i <= n; i += 2) {
        if (is_prime[i]) {
            large_prime_list[prime_count] = i;
            prime_count++;
        }
    }

    /* 適したサイズへのコピー */
    int *prime_list = CALLOC(prime_count, int);
    memmove(prime_list, large_prime_list, prime_count * sizeof(int));
    free(large_prime_list);

    has_size_array ret = {prime_list, prime_count};
    return ret;
}

int main() {
    has_size_array prime_list_struct;
    prime_list_struct = prime_list_func(RANGE_MAX);

    int *prime_list = prime_list_struct.data;
    int list_size = prime_list_struct.size;

    int count = (((RANGE_MAX)-RANGE_MIN) / 2) + 1;
    int ans_count = 0;

    int i;
    for (i = RANGE_MIN; i <= RANGE_MAX; i += 2) {
        int odd_j, odd_k;
        for (odd_j = 0; odd_j < list_size; odd_j++) {
            char flag = 0;

            for (odd_k = 0; odd_k < list_size; odd_k++) {
                int sum = prime_list[odd_j] + prime_list[odd_k];

                if (i == sum) {
                    printf("%d: %d, %d\n", i, prime_list[odd_j], prime_list[odd_k]);

                    flag = 1;
                    ans_count++;
                    break;
                }
            }

            if (flag == 1) {
                break;
            }
        }
    }

    printf("count: %d ans_count: %d\n", count, ans_count);
    if (count == ans_count) {
        printf("ok!\n");
    } else {
        printf("bad...\n");
    }

    return 0;
}
