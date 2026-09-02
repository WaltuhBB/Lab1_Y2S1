#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PERM {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
#define PERM_LEN 10

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
    size_t count = 0;
    
    while (Permutation(p, PERM_LEN))
    {
        for (size_t i = 0; i < PERM_LEN; i++)
        {
            printf("%d", p[i]);
        }

        printf("\n");
        count++;
    }

    printf("\n%d", count);

    return 0;
}