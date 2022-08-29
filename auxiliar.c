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

/* -------------------------------------------------------------------------- */

/**
 * @brief Function to permute the all commands array
 * @param array {tCommand *} Array to get all permutations
 * @param init {int} Init range to be permutated
 * @param end {int} end range to be permutated
 * @param allPerm {tCommand **} Matrix with all possible permutations
 * @param idx {int} - Index of the current permutation to atributte to all permutation mat line
 */
void permute(tCommand *array, int init, int end, tCommand **allPerm, int *idx)
{
    if (init == end)
    {
        for (int k = 0; k <= end; k++)
        {
            allPerm[(*idx)][k] = array[k];
        }

        (*idx)++; 
    }
    else
    {
        for (int i = init; i <= end; i++)
        {
            swap((array + init), (array + i));
            permute(array, init + 1, end, allPerm, idx);
            swap((array + init), (array + i)); // backtrack
        }
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief Function to print all permutations 
 * @param allPermutations {tCommand **} - Matrix with all the permutations
 * @param lines {int} - number of lines in the allPermutations matrix
 * @param cols {int} - number of collumns in the allPermutations matrix
 */
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

void freeMat(tCommand **mat)
{
    free(mat[0]);
    free(mat);
}