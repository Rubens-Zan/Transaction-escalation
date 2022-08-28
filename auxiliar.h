#ifndef _AUXILIAR_H_
#define _AUXILIAR_H_

int fact(int n);
void permute(tCommand *a, int l, int r, tCommand **allPerm, int *idx);
tCommand **alocateMat(int lin, int col); 
void swap(tCommand *x, tCommand *y);
void printAllPermutations(tCommand **allPermutations, int lines, int cols); 

#endif