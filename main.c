#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
                res = true;
            }
        }

        if (res)
        {
            size_t j;

            for (j = n - 1; j > i && p[j] > p[i]; j--);

            int tmp = p[j];
            p[j] = p[i];
            p[i] = tmp;

            for (size_t k = 0; k + i + 1 < n; i++)
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


    return 0;
}