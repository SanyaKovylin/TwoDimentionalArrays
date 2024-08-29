#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include "MatOp.h"

struct Matrix Get2dimFromFile (const char *file);
struct matrix Get1dimFromFile (const char *file);

void PrintMassiveAsSteps (struct matrix *mat, size_t size);

struct JaggedArr GetJagged (void);
void PrintJagged(struct JaggedArr mat);


int main(void){

    struct Matrix Mass = Get2dimFromFile ("Source/Input.txt");

    //printf("%d %d", Mass.cols, Mass.rows);
    Print2dimMassive (Mass);

/*
    size_t Mass1Els = 0;
    int *Mass1 = Get1dimFromFile(&Mass1Els, "Build/Input.txt");

    PrintMassiveAsSteps(Mass1, Mass1Els);
*/
    struct Matrix Arr1 = Get2dimFromFile ("Source/Input.txt");
    struct Matrix E = MatInit (2ll,2ll);

    //Print2dimMassive(*CutMatrix(Arr1, 1ull, &E));
    struct timeval stop, start;
    gettimeofday (&start, NULL);
    printf (Form"\n", DetByGauss (Mass));
    gettimeofday (&stop, NULL);
    printf ("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    struct timeval stop1, start1;
    gettimeofday (&start1, NULL);
    printf(Form"\n", ComputeDetByLaplas (Mass));
    gettimeofday (&stop1, NULL);
    printf ("took %lu us\n", (stop1.tv_sec - start1.tv_sec) * 1000000 + stop1.tv_usec - start1.tv_usec);

    struct JaggedArr Arr2 = GetJagged ();
    PrintJagged(Arr2);
    return 0;
}



struct Matrix Get2dimFromFile (const char *file){

    assert(file != NULL);

    size_t NumOfLines = 0;
    size_t NumOfCols = 0;

    FILE *fp;

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
    struct Matrix mat = MatInit(NumOfLines, NumOfCols);

    for (size_t y = 0; y < mat.rows; y++){
        for (size_t x = 0; x < mat.cols; x++){

            fscanf (fp, Form, &mat.mat[y][x]);
        }
    }
    return mat;
}

struct matrix Get1dimFromFile (const char *file){

    assert(file != NULL);

    size_t NumOfLines = 0;
    size_t NumOfCols = 0;

    FILE *fp;

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

    struct matrix out = {
        (TypeOfMassive*) calloc (NumOfCols * NumOfLines, sizeof(TypeOfMassive)),
        NumOfLines,
        NumOfCols,
        NumOfCols*NumOfLines
    };
    for (size_t x = 0; x < out.size; x++){

        fscanf (fp, Form, &out.mat[x]);
    }
    return out;
}



void Print2dimMassive (struct Matrix mat){

    assert(mat.mat != NULL);

    for (size_t y = 0; y < mat.rows; y++){
        for (size_t x = 0; x < mat.cols; x++){

            printf(Form " ", mat.mat[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}


void PrintMassiveAsSteps (struct matrix *mat, size_t size){

    assert(mat != NULL);

    double disc = sqrt(1 + 8*(mat->size));

    bool extrastep = !CompareDoubles(disc, floor(disc));

    size_t steps = (size_t) ((disc - 1) / 2 );

    size_t x = 1;
    for (;x <= steps; x++){
        for (size_t y = 0; y < x; y++){
            printf(Form "  ", mat->mat[x * (x - 1) / 2 + y]);
        }
        printf("\n \n");
    }

    if (extrastep){
        for (size_t i = 0; (x * (x - 1) / 2 + i) < size; i++){
            printf(Form "  ", mat->mat[x * (x - 1) / 2 + i]);
        }
    }
}


const double EPS = 0.00001;

int CompareDoubles (double Value1, double Value2){

    assert (isfinite (Value1));
    assert (isfinite (Value2));

    return EPS > fabs (Value1 - Value2);
}

int IsZero (double Value){

    assert (isfinite(Value));

    return EPS > fabs (Value);
}

struct JaggedArr GetJagged (void){

    size_t numlines = 0;
    printf ("Please, enter the number of lines\n");
    scanf ("%llu", &numlines);

    struct JaggedArr out = {

        (TypeOfMassive**) calloc (numlines, sizeof (TypeOfMassive*)),
        numlines,
        (size_t*) calloc (numlines, sizeof (size_t))
    };

    for (size_t i = 0; i < numlines; i++) {

        printf("Please, enter the length of the next line\n");
        size_t linelen = 0;
        scanf ("%llu", &linelen);

        out.lines[i] = linelen;
        out.mat[i] = (TypeOfMassive*) calloc (linelen, sizeof (TypeOfMassive));

        printf ("Please, enter the line\n");
        for (size_t j = 0; j < linelen; j++) {

            scanf (Form, &out.mat[i][j]);
        }
    }
    return out;
}


void PrintJagged(struct JaggedArr mat){

    assert(mat.mat != NULL);

    for (size_t y = 0; y < mat.rows; y++) {
        for (size_t x = 0; x < mat.lines[y]; x++) {

            printf(Form " ", mat.mat[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
