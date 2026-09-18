#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PERM {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
#define PERM_LEN 11

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

unsigned int** createMatrix_r(size_t size)
{
    unsigned int **ptrM = NULL;
    
    if (size)
    {   
        ptrM = (unsigned int**)calloc(size, sizeof(unsigned int*));

        if (ptrM)
        {
            bool flagN = false;
            
            for (size_t i = 0; i < size && !flagN; i++)
            {
                ptrM[i] = (unsigned int*)calloc(size, sizeof(unsigned int));

                if (ptrM[i])
                {
                    for (size_t j = 0; j < size; j++)
                    {
                        if (i == j)
                        {
                            ptrM[i][j] = 0;
                        }
                        else
                        {
                            ptrM[i][j] = rand() % 5000;
                        }
                    }
                }
                else
                {
                    for (size_t k = 0; k < i; k++)
                    {
                        free(ptrM[k]);
                        ptrM[k] = NULL;
                    }
                    free(ptrM);
                    ptrM = NULL;
                    
                    flagN = true;
                }
            }
        }
    }

    return ptrM;
}

void clearMemory(unsigned int*** ptrM, size_t row)
{
    if (ptrM && *ptrM)
    {
        for (size_t i = 0; i < row; i++)
        {
            free((*ptrM)[i]);
            (*ptrM)[i] = NULL;
        }

        free(*ptrM);
        *ptrM = NULL;
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    
    int p[PERM_LEN] = PERM;
    
    // unsigned int Mat[PERM_LEN][PERM_LEN] = {

    //     {0, 10, 5, 17},
    //     {6, 0, 1, 1},
    //     {9, 10, 0, 4},
    //     {16, 3, 7, 0}

    // };
    
    unsigned int **Mat = createMatrix_r(PERM_LEN);

    if (Mat)
    {    
        for (size_t i = 0; i < PERM_LEN; i++)
        {
            for (size_t j = 0; j < PERM_LEN; j++)
            {
                printf("%d  ", Mat[i][j]); 
            }
            printf("\n");
        }
        printf("\n");

        unsigned int min_sum = 0;

        for (size_t i = 0; i < PERM_LEN - 1; i++)
        {
            min_sum += Mat[p[i] - 1][p[i + 1] - 1];
        }
        min_sum += Mat[p[PERM_LEN - 1] - 1][p[0] - 1];

        int min_cycle[PERM_LEN + 1];

        for (size_t i = 0; i < PERM_LEN; i++)
        {
            min_cycle[i] = p[i];
        }
        min_cycle[PERM_LEN] = min_cycle[0];

        while (Permutation(p, PERM_LEN))
        {
            unsigned int sum = 0;

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

        clearMemory(&Mat, PERM_LEN);
    }
    else
    {
        printf("couldn't allocate memory\n");
    }

    return 0;
}