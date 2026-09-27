#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define PERM {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
#define PERM_LEN 13

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

int HeuristicAlg(unsigned int** Mat, int* cycle, size_t node_amount)
{
    if (!Mat || !cycle || !node_amount)
    {
        return -1;
    }
    for (size_t i = 0; i < node_amount; i++)
    {
        if (!Mat[i])
        {
            return -1;
        }
    }

    unsigned char *visits = (unsigned char*)calloc((node_amount - 1) / 8 + 1, sizeof(unsigned char));

    if (!visits)
    {
        return -2;
    }

    visits[0] |= 128;

    size_t k = 0;

    int next_node;
    int curr_node = 0;

    int sum = 0;

    do
    {
        next_node = -1;
        int cost = 0;

        for (size_t j = 0; j < node_amount; j++)
        {
            if (Mat[curr_node][j] && !(visits[j / 8] & (128 >> j % 8)) && ((!cost) || (Mat[curr_node][j] < cost)))
            {
                next_node = j;
                cost = Mat[curr_node][j];
            }
        }

        cycle[k] = curr_node + 1;
        k++;

        if (next_node != -1)
        {    
            visits[next_node / 8] |= 128 >> next_node % 8;
            sum += cost;
            curr_node = next_node;
        }

    } while (next_node != -1);

    sum += Mat[curr_node][0];
    cycle[node_amount] = 1;

    free(visits);

    return sum;
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
    
    unsigned int **Mat = createMatrix_r(PERM_LEN);

    if (Mat)
    {   
        // Mat[0][1] = 10;
        // Mat[0][2] = 5;
        // Mat[0][3] = 17;
        // Mat[1][0] = 6;
        // Mat[1][2] = 1;
        // Mat[1][3] = 1; 
        // Mat[2][0] = 9;
        // Mat[2][1] = 10;
        // Mat[2][3] = 4;
        // Mat[3][0] = 16;
        // Mat[3][1] = 3;
        // Mat[3][2] = 7;

        for (size_t i = 0; i < PERM_LEN; i++)
        {
            for (size_t j = 0; j < PERM_LEN; j++)
            {
                printf("%d  ", Mat[i][j]); 
            }
            printf("\n");
        }
        printf("\n");

        //эвристика

        int cycle[PERM_LEN + 1];
        printf("Heuristic result: %d\n", HeuristicAlg(Mat, cycle, PERM_LEN));
        for (size_t i = 0; i < PERM_LEN; i++)
        {
            printf("%d-", cycle[i]);
        }
        printf("%d\n\n", cycle[PERM_LEN]);

        //перебор

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

        while (Permutation(p, PERM_LEN) && p[0] == 1)
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