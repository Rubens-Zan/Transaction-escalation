#include <stdlib.h>
#include "transaction.h"

/* Function to swap values at two pointers */
void swap(tCommand *x, tCommand *y)
{
    tCommand temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Function permute the given commands array
This function takes three parameters:
1. All commands array
2. Starting index of the array
3. Ending index of the array. 
4. All permutations matrix. 
5. Index of the current permutation. 
*/
void permute(tCommand *a, int l, int r, tCommand **allPerm, int *idx)
{
    if (l == r)
    {
        for (int k = 0; k <= r; k++)
        {
            allPerm[(*idx)][k] = a[k];
        }

        (*idx)++; 
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap((a + l), (a + i));
            permute(a, l + 1, r, allPerm, idx);
            swap((a + l), (a + i)); // backtrack
        }
    }
}

/* -------------------------------------------------------------------------- */
void printAllPermutations(tCommand **allPermutations, int lines, int cols){
    for (int i=0;i < lines;i++){
        for (int j=0;j < cols;j++){
            printf("%d ",allPermutations[i][j].time);
        }
        printf("\n");
    }
}

/* -------------------------------------------------------------------------- */

int fact(int n)
{
    if (n == 1)
    {
        return n;
    }

    return n * fact(n - 1);
}

/* -------------------------------------------------------------------------- */

tCommand **alocateMat(int lin, int col)
{
    tCommand **mat;
    mat = malloc(lin * sizeof(tCommand *));
    mat[0] = malloc(lin * col * sizeof(tCommand));

    for (int i = 1; i < lin; i++)
        mat[i] = mat[0] + i * col;

    return mat;
}