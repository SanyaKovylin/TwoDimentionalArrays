#ifndef MatOp_H_INCLUDED
#define MatOp_H_INCLUDED

#define TypeOfMassive double
#define Form "%lg"

struct Matrix {
    TypeOfMassive **mat;
    size_t         rows;
    size_t         cols;
};

struct JaggedArr {
    TypeOfMassive **mat;
    size_t         rows;
    size_t       *lines;
};

struct matrix {
    TypeOfMassive *mat;
    size_t         rows;
    size_t         cols;
    size_t         size;
};

struct Matrix MatInit(size_t Rows, size_t Cols);

int AddMatrix   (struct Matrix mat1, struct Matrix mat2, struct Matrix *mat3);
int MulMatrix   (struct Matrix mat1, struct Matrix mat2, struct Matrix *mat3);

void Print2dimMassive (struct Matrix mat);

TypeOfMassive ComputeDetByLaplas (struct Matrix mat);
TypeOfMassive DetByLaplas (struct Matrix *mat, struct Matrix *Memory);
struct Matrix *CutMatrix   (struct Matrix mat, size_t col, struct Matrix *Memory);

TypeOfMassive DetByGauss (struct Matrix mat);

int IsZero         (double Value);
int CompareDoubles (double Value1, double Value2);


#endif
