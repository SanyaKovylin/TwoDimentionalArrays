#ifndef MatOp_H_INCLUDED
#define MatOp_H_INCLUDED

#define TypeOfMassive int
#define Form "%3d"

struct Matrix {
    TypeOfMassive **mat;
    size_t rows;
    size_t cols;
};

struct Matrix AddMatrix(struct Matrix mat1, struct Matrix mat2);
TypeOfMassive **MatInit(size_t Rows, size_t Cols);
struct Matrix MulMatrix(struct Matrix mat1, struct Matrix mat2);
struct Matrix CutMatrix(struct Matrix mat, size_t col);
TypeOfMassive DetByLaplas(struct Matrix mat);
void Print2dimMassive (struct Matrix mat);

#endif
