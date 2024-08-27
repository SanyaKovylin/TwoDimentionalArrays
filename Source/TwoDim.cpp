#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "MatOp.h"

struct Matrix Get2dimFromFile (const char *file);
int *Get1dimFromFile (size_t *NumOfEls, const char *file);
int CompareDoubles(double Value1, double Value2);
void PrintMassiveAsSteps (TypeOfMassive *massive, size_t size);


int main(void){

    struct Matrix Mass = Get2dimFromFile("Build/Input.txt");

    Print2dimMassive(Mass);
/*
    size_t Mass1Els = 0;
    int *Mass1 = Get1dimFromFile(&Mass1Els, "Build/Input.txt");

    PrintMassiveAsSteps(Mass1, Mass1Els);
*/
    struct Matrix Arr1 = Get2dimFromFile("Build/Input.txt");

    struct Matrix ArrSum = MulMatrix(Mass, Arr1);

    //Print2dimMassive(CutMatrix(Arr1, 0ull));
    printf(Form, DetByLaplas(Mass));

    return 0;
}


struct Matrix Get2dimFromFile (const char *file){

    assert(file != NULL);

    size_t NumOfLines = 0;
    size_t NumOfCols = 0;

    FILE *fp;
    // 1 2 3
    // 4 5 6
    // 7 8 9

    // 1 2 3 4 5 6 7 8 9
    // 2 3 4 5 6 7 8 9 0
    fp = fopen(file, "r");

    assert(fp != NULL);

    int c = 0;

    while ((c = getc(fp)) != '\n'){
        if (isspace(c)){
            NumOfCols++;
        }
    }
    NumOfCols++;

    while ((c = getc(fp)) != EOF){
        if (c == '\n'){
            NumOfLines++;
        }
    }
    NumOfLines++;

    rewind (fp);
    struct Matrix mat = {

        (TypeOfMassive**) calloc (NumOfLines, sizeof(TypeOfMassive*)),
        NumOfLines,
        NumOfCols
    };


    for (size_t i = 0; i < mat.rows; i++){
        mat.mat[i] = (TypeOfMassive*) calloc (NumOfCols, sizeof(TypeOfMassive));
    }

    for (size_t y = 0; y < mat.rows; y++){
        for (size_t x = 0; x < mat.cols; x++){

            fscanf (fp, Form, &mat.mat[y][x]);
        }
    }
    return mat;
}

int *Get1dimFromFile (size_t *NumOfEls, const char *file){

    assert(NumOfEls != NULL);
    assert(file != NULL);

    *NumOfEls = 0;

    FILE *fp;
    fp = fopen(file, "r");

    assert(fp != NULL);

    int c = 0;
    while ((c = getc(fp)) != EOF){
        if (isspace(c)){
            (*NumOfEls)++;
        }
    }

    rewind (fp);

    TypeOfMassive *mas = (TypeOfMassive*) calloc (*NumOfEls, sizeof(TypeOfMassive));

    for (size_t x = 0; x < *NumOfEls; x++){

        fscanf (fp, Form, &mas[x]);
    }
    return mas;
}

void Print2dimMassive (struct Matrix mat){

    assert(mat.mat != NULL);

    for (size_t y = 0; y < mat.rows; y++){
        for (size_t x = 0; x < mat.cols; x++){

            printf(Form "  ", mat.mat[y][x]);
        }
        printf("\n \n");
    }
}


void PrintMassiveAsSteps (TypeOfMassive *massive, size_t size){

    assert(massive != NULL);

    double disc = sqrt(1 + 8*size);

    bool extrastep = !CompareDoubles(disc, floor(disc));

    size_t steps = (size_t) ((disc - 1) / 2 );

    size_t x = 1;
    for (;x <= steps; x++){
        for (size_t y = 0; y < x; y++){
            printf(Form "  ", massive[x * (x - 1) / 2 + y]);
        }
        printf("\n \n");
    }

    if (extrastep){
        for (size_t i = 0; (x * (x - 1) / 2 + i) < size; i++){
            printf(Form "  ", massive[x * (x - 1) / 2 + i]);
        }
    }
}


const double EPS = 0.00001;

int CompareDoubles(double Value1, double Value2){

    assert (isfinite (Value1));
    assert (isfinite (Value2));

    return EPS > fabs (Value1 - Value2);
}
