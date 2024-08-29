#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "MatOp.h"


// for i in range(10000000):
//      A + B = C
int AddMatrix (struct Matrix mat1, struct Matrix mat2, struct Matrix *matout){

    assert (mat1.mat != NULL);
    assert (mat2.mat != NULL);

    assert (mat1.rows == mat2.rows);
    assert (mat1.cols == mat2.cols);

    for (size_t y = 0; y < mat1.rows; y++){
        for (size_t x = 0; x < mat1.cols; x++){
            matout->mat[y][x] = mat1.mat[y][x] + mat2.mat[y][x];
        }
    }
    return 1;
}

struct Matrix MatInit(size_t Rows, size_t Cols){

    struct Matrix out = {
        (TypeOfMassive**) calloc (Rows, sizeof(TypeOfMassive*)),
        Rows,
        Cols
    };

    for (size_t i = 0; i < Rows; i++){
        out.mat[i] = (TypeOfMassive*) calloc (Cols, sizeof(TypeOfMassive));
    }
    return out;
}

int MulMatrix(struct Matrix mat1, struct Matrix mat2, struct Matrix *matout){

    assert (mat1.mat != NULL);
    assert (mat2.mat != NULL);

    assert (mat1.cols == mat2.rows);

    for (size_t y = 0; y < mat1.rows; y++){
        for (size_t x = 0; x < mat2.cols; x++){
            TypeOfMassive cell = 0;
            for (size_t i = 0; i < mat1.cols; i++){
                cell += mat1.mat[y][i] * mat2.mat[i][x];
            }
            matout->mat[y][x] = cell;
        }
    }
    return 1;
}

TypeOfMassive ComputeDetByLaplas (struct Matrix mat){

    struct Matrix *Memory = (struct Matrix*) calloc (mat.cols - 1, sizeof(mat));

    for (size_t i = 1; i < mat.cols; i++){
        Memory[i - 1] = MatInit (i, i);
    }

    // for (size_t i = 0; i < mat.cols - 1; i++){
    //     printf("%llu\n", Memory[i].cols);
    // }
    return DetByLaplas(&mat, Memory);
    //return 1.111111111;
}

TypeOfMassive DetByLaplas (struct Matrix *mat, struct Matrix Memory[]){
    // cringe
    assert (mat->cols == mat->rows);
    assert (mat->mat != NULL);

    //Print2dimMassive(*mat);
    if (mat->cols == 1)
        return mat->mat[0][0];
    else {
        TypeOfMassive partdt = 0;
        size_t n = mat->cols;
        for (size_t i = 0; i < n; i++){
            //Print2dimMassive(*mat);
            int sign = (i % 2 == 0) ? 1 : -1;
            //printf("%llu %llu\n", (Memory[(mat->cols) - 2]).cols, mat->cols);
            partdt += sign * mat->mat[0][i] * DetByLaplas (CutMatrix (*mat, i, &Memory[mat->cols - 2]), Memory);
        }


        return partdt;
    }
}

struct Matrix *CutMatrix (struct Matrix mat, size_t col, struct Matrix *cell){

    assert (mat.cols == mat.rows);
    assert (mat.cols > 1);
    assert (col < mat.cols);
    assert (cell != 0);
    //printf("%llu\n", cell->cols);
    for (size_t y = 1; y < mat.cols; y++) {
        for (size_t x = 0; x < mat.cols - 1; x++) {

            int IsSkipped = (x >= col);
            cell->mat[y - 1][x] = mat.mat[y][x + IsSkipped];
            //printf("%lld %lld\n", y, x);
        }
    }
    //Print2dimMassive(*cell);
    return cell;
}
