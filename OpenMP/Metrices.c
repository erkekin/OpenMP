    //
    //  Metrices.c
    //  OpenMP
    //
    //  Created by Erk EKİN on 28/11/15.
    //  Copyright © 2015 erkekin. All rights reserved.
    //

#include "Metrices.h"
#include <stdlib.h>

struct element
{
    int number;
    int i;
    int j;
};


int RdRowSize(FILE *file)
{
    int row;
    fscanf(file, "%d", &row);
    return row;
}

int RdColumnSize(FILE *file)
{
    int col;
    fscanf(file, "%d", &col);
    return col;
}

void printMatrix(int(**matrix), int row, int col)
{
    int i, j;
    for (i = 0; i <  row; i++){
        for (j = 0; j < col; j++){
            printf("%d \t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int getNeighboorsMatrix(int(**bigmatrix), int row, int col){
    
    int r,c;
    int size = 3;
    int middleNumber;
    struct element minimum;
    minimum.number = bigmatrix[row][col];
    minimum.i = row;
    minimum.j = col;
    
    middleNumber = bigmatrix[row+1][col+1];
    
    for (r = row; r<size+row; r++) {
        
        for (c = col; c<size+col; c++) {
            
            if (minimum.number > bigmatrix[r][c]) {
                minimum.number = bigmatrix[r][c]; // fin the minimum
                
                minimum.i = r;
                minimum.j = c;
            }
        }
    }
    switch (size*(minimum.i-row) + (minimum.j-col)) { // the order of the minimum number
        case 0:
            
            return 8;
            break;
        case 1:
            
            return 1;
            break;
        case 2:
            
            return 2;
            break;
        case 3:
            
            return 7;
            break;
        case 4:
            
            return 0;
            break;
        case 5:
            
            return 3;
            break;
        case 6:
            
            return 6;
            break;
        case 7:
            
            return 7;
            break;
        case 8:
            
            return 8;
            break;
        default:
            return -1;
            break;
    }
}
int**  createMatrix(int row, int col){
    
    int i;
    int **matrix = (int **)malloc( row * sizeof(int *));
    for (i=0; i< row; i++)
        matrix[i] = (int *)malloc( col * sizeof(int));
    return matrix;
}

int** readMatrix(int* row, int* col){
    FILE *fpin;
    
    /*open input file - file name is hardcoded*/
    fpin = fopen("matrix.txt", "r"); /* open the file for reading */
    if (fpin == NULL)
    {
        fprintf(stdout, "Cannot open input file  - Bye\n");
        
        return NULL;
    }
    
        //  printf("direction  %d  \n \n", getDirectionOfPixel(&B));
    
    int data;
    *row = RdRowSize(fpin);
    *col = RdColumnSize(fpin);
    
    int i, j;
    int **matrix = createMatrix(*row, *col);
    
    for (i = 0; i <  *row; i++)
        for (j = 0; j < *col; j++){
            fscanf(fpin, "%d", &data);
            matrix[i][j] = data;
        }
    fclose(fpin);  /* close the file */
    
    return matrix;
}

int getWeightedDirection(int(**directionMatrix), int row, int col){
    
    int array[9] = {0,0,0,0,0,0,0,0,0};
    int r,c;
    int size = 5;

    for (r = row; r < size + row; r++) {
        
        for (c = col; c < size + col; c++) {
            
            array[directionMatrix[r][c]]++;
            
        }
        
    }
    
    for (r = 0; r<9; r++) {
        if (array[r]>12) {
            
            return r;
        }
    }
    
    return 0;
}

void drawAbsoluteDirections(int(**directionMatrix), int row, int col)
{
    int r = row - 4;
    int c = col - 4;
    int i, j;
    
    int **mat = createMatrix(r, c);
    
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            
                // printf("(%d) için ", matrix[i+1][j+1]);
            mat[i][j] = getWeightedDirection(directionMatrix, i ,j);
                //printf("direction: %d \n",mat[i][j]);
            
        }
            //printf("\n");
    }
        //printf("\n");
    
    printMatrix(mat, r, c);
    
}

void drawArrows(int(**matrix), int row, int col)
{
    
    int r = row - 2;
    int c = col -2;
    int i, j;
    
    int **mat = createMatrix(r, c);
    
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++){
            
                // printf("(%d) için ", matrix[i+1][j+1]);
            mat[i][j] = getNeighboorsMatrix(matrix, i ,j);
                // printf("ağırlık: %d \n",mat[i][j]);
            
        }
    }
    printMatrix(mat, r, c);
    drawAbsoluteDirections(mat, r, c);
    
}
