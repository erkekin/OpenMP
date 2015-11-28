#include <stdio.h>
#include "Metrices.h"

#include <stdlib.h>

void rgb(){
    
    int width = 512;
    int height = 512;
    
    int image[width*height][3]; // first number here is 1024 pixels in my image, 3 is for RGB values
    FILE *streamIn;
    int i,j;
    streamIn = fopen("lena.bmp", "r");
    if (streamIn == (FILE *)0){
        printf("File opening error ocurred. Exiting program.\n");
        exit(0);
    }
    
    int byte;
    
    for(i=0;i<54;i++){
        
        byte = getc(streamIn);
        
    }
    
    int **matrix = (int **)malloc( width * sizeof(int *));
    for (i=0; i< width; i++)
        matrix[i] = (int *)malloc( height * sizeof(int));
    
    
    for(i=0;i<width;i++){
        
        for(j=0;j<height;j++){
            
            image[width*j+i][2] = getc(streamIn);  // use BMP 24bit with no alpha channel
            image[width*j+i][1] = getc(streamIn);  // BMP uses BGR but we want RGB, grab byte-by-byte
            image[width*j+i][0] = getc(streamIn);  // reverse-order array indexing fixes RGB issue...
            
            matrix[i][j] = (image[width*j+i][0]+image[width*j+i][1]+image[width*j+i][2])/3;
        }
        
        
    }
    
        // printMatrix(matrix, width, height);
    drawArrows(matrix, width, height);
    fclose(streamIn);
    
}

int main(void)
{
    rgb();
        //    int row=0, col=0;           /* the row and column sizes of A */
        //    int **matrix = readMatrix(&row, &col);
        //    printMatrix(matrix, row, col);
        //
        //    drawArrows(matrix, row, col);
    
    return (0);
}
