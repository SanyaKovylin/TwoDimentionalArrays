#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "MatOp.h"

bool FindNonZeroRow(struct Matrix mat, size_t startpoint);

TypeOfMassive DetByGauss(struct Matrix mat){

    assert(mat.mat != NULL);
    assert(mat.cols == mat.rows);

    for (size_t x = 0; x < mat.rows; x++){
        double key = mat.mat[x][x];
        if (!IsZero(key)){
            for (size_t y = x + 1; y < mat.rows; y++){
                double linekey = mat.mat[y][x] / key;
                for (size_t yx = x; yx < mat.cols; yx++){
                    mat.mat[y][yx] -= mat.mat[x][yx] * linekey;
                    //printf("\nPP%llu %llu %lluPP\n", x, y, yx);
                }
                //Print2dimMassive(mat);
            }

        }
        else {
            if (!FindNonZeroRow(mat, x)) return 0;
            x--;
        }
    }
    double ans = 1;
    for (size_t x = 0; x < mat.rows; x++){
        ans *= mat.mat[x][x];
    }
    return ans;
}


bool FindNonZeroRow(struct Matrix mat, size_t startpoint){

    size_t i = startpoint;
    for (; i < mat.cols && IsZero(mat.mat[i][startpoint]); i++)
        ;

    if (i == mat.cols) return 0;
    //printf("\nEEE%d\n%d  %lg",i, IsZero(mat.mat[i][i]), mat.mat[i][i]);
    TypeOfMassive *buf = mat.mat[startpoint];
    mat.mat[startpoint] = mat.mat[i];
    mat.mat[i] = buf;
    return 1;
}

// form * (int) (*(mat.mat + mat.rows * y + x))
