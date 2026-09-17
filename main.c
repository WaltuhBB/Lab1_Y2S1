#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PERM {1, 2, 3, 4}
#define PERM_LEN 4

bool Permutation(int* p, size_t n)
{
    bool res = false;

    if (p && n > 1)
    {
        size_t i;

        for (i = n - 2; i && !res; i--)
        {
            if (p[i] < p[i + 1])
            {
                i++;
                res = true;
            }
        }

        if (!res && p[0] < p[1])
        {
            res = true;
        }

        if (res)
        {
            size_t j;

            for (j = n - 1; j > i && p[j] <= p[i]; j--);

            int tmp = p[j];
            p[j] = p[i];
            p[i] = tmp;

            for (size_t k = 0; k + i + 1 < n - k - 1; k++)
            {
                tmp = p[k + i + 1];
                p[k + i + 1] = p[n - 1 - k];
                p[n - 1 - k] = tmp;
            }
        }
    }

    return res;
}

int main()
{
    int p[PERM_LEN] = PERM;
    
    int Mat[4][4] = {

        {0, 10, 5, 17},
        {6, 0, 1, 1},
        {9, 10, 0, 4},
        {16, 3, 7, 0}

    };  

    size_t min_sum = Mat[0][1] + Mat[1][2] + Mat[2][3] + Mat[3][0];
    size_t min_cycle[PERM_LEN + 1] = {1, 2, 3, 4, 1};

    while (Permutation(p, PERM_LEN))
    {
        size_t sum = 0;

        for (size_t i = 0; i < PERM_LEN - 1; i++)
        {
            sum += Mat[p[i] - 1][p[i + 1] - 1];
        }
        sum += Mat[p[PERM_LEN - 1] - 1][p[0] - 1];

        if (sum < min_sum)
        {
            min_sum = sum;

            for (size_t i = 0; i < PERM_LEN; i++)
            {
                min_cycle[i] = p[i];
            }
            min_cycle[PERM_LEN] = min_cycle[0];
        }
    }

    printf("path cost:  %d\n", min_sum);
    for (size_t i = 0; i < PERM_LEN; i++)
    {
        printf("%d-", min_cycle[i]);
    }
    printf("%d\n", min_cycle[PERM_LEN]);

    return 0;
}