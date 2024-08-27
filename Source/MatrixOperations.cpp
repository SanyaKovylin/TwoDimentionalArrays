#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "MatOp.h"



struct Matrix AddMatrix(struct Matrix mat1, struct Matrix mat2){

    assert(mat1.mat != NULL);
    assert(mat2.mat != NULL);

    assert(mat1.rows == mat2.rows);
    assert(mat1.cols == mat2.cols);

    struct Matrix matout = {MatInit(mat1.rows, mat1.cols), mat1.rows, mat1.cols};

    for (size_t y = 0; y < mat1.rows; y++){
        for (size_t x = 0; x < mat1.cols; x++){
            matout.mat[y][x] = mat1.mat[y][x] + mat2.mat[y][x];
        }
    }
    return matout;
}

TypeOfMassive **MatInit(size_t Rows, size_t Cols){

    TypeOfMassive ** Mat = (TypeOfMassive**) calloc (Rows, sizeof(TypeOfMassive*));
    for (size_t i = 0; i < Rows; i++){
        Mat[i] = (TypeOfMassive*) calloc (Cols, sizeof(TypeOfMassive));
    }
    return Mat;
}

struct Matrix MulMatrix(struct Matrix mat1, struct Matrix mat2){

    assert(mat1.mat != NULL);
    assert(mat2.mat != NULL);

    assert(mat1.cols == mat2.rows);

    struct Matrix matout = {MatInit(mat1.rows, mat2.cols), mat1.rows, mat2.cols};

    for (size_t y = 0; y < mat1.rows; y++){
        for (size_t x = 0; x < mat2.cols; x++){
            TypeOfMassive cell = 0;
            for (size_t i = 0; i < mat1.cols; i++){
                cell += mat1.mat[y][i] * mat2.mat[i][x];
            }
            matout.mat[y][x] = cell;
        }
    }
    return matout;
}

TypeOfMassive DetByLaplas(struct Matrix mat){

    assert(mat.cols = mat.rows);

    if (mat.cols == 1)
        return mat.mat[0][0];
    else{
        TypeOfMassive partdt = 0;
        size_t n = mat.cols;
        for (size_t i = 0; i < n; i++){
            int sign = (i % 2 == 0) ? 1 : -1;
            partdt += sign * mat.mat[0][i] * DetByLaplas(CutMatrix(mat, i));
        }
        return partdt;
    }
}

struct Matrix CutMatrix(struct Matrix mat, size_t col){

    assert(mat.cols == mat.rows);
    assert(mat.cols > 1);
    assert(col < mat.cols);

    struct Matrix outmat = {MatInit(mat.cols - 1, mat.cols -1), mat.cols - 1, mat.cols - 1};

    for (size_t y = 1; y < mat.cols; y++){
        for (size_t x = 0; x < mat.cols - 1; x++){

            int IsSkipped = (x >= col);
            outmat.mat[y - 1][x] = mat.mat[y][x + IsSkipped];
            // printf("%lld %lld\n", y, x);
        }
    }
    return outmat;
}
