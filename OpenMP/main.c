#include <stdio.h>
#include "Metrices.h"

#include <stdlib.h>



int main(void)
{
    
    int row=0, col=0;           /* the row and column sizes of A */
    int **matrix = readMatrix(&row, &col);
    printMatrix(matrix, row, col);
    
    drawArrows(matrix, row, col);
    
    return (0);
}


