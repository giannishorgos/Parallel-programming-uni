#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"

void printGraph(MM_typecode matcode, int M, int N, int nz, int **graph)
{
    /************************/
    /* print out matrix     */
    /************************/
    mm_write_banner(stdout, matcode);
    mm_write_mtx_crd_size(stdout, M, N, nz);
    for (int i = 0; i < nz; i++)
        fprintf(stdout, "%d\t %d\t %d\n", graph[0][i], graph[1][i], graph[2][i]);
}

int getLength(FILE *f)
{
    int M, N, length;
    /* find out size of sparse matrix */
    if (mm_read_mtx_crd_size(f, &M, &N, &length) != 0)
        exit(1);

    return length;
}

int **readFile(FILE *f, MM_typecode matcode)
{
    /*
    DESC
    ----------
    find size of sparse Matrix, read the matrix

    Parameters
    ----------
    FILE* f -> .mtx file open with read access

    Returns
    ----------
    a 2D array that contains
    at array[0] -> rows
    at array[1] -> col
    at array[2] -> weights (for us all the weights are equal to 1)
    */

    int M, N, nz;
    int i, *I, *J, *val;
    int ret_code;

    /* find out size of sparse matrix */
    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) != 0)
        exit(1);

    /* reserve memory for matrices */
    I = (int *)malloc(nz * sizeof(int));
    J = (int *)malloc(nz * sizeof(int));
    val = (int *)malloc(nz * sizeof(int));

    for (int i = 0; i < nz; i++)
    {
        fscanf(f, "%d %d %d\n", &I[i], &J[i], &val[i]);
        I[i]--; /* adjust from 1-based to 0-based */
        J[i]--; /* adjust from 1-based to 0-based */
    }

    /* populate values array with 1 because we don't care about weights */
    for (int i = 0; i < nz; i++)
    {
        val[i] = 1;
    }

    if (f != stdin)
        fclose(f);

    int **graph = (int **)malloc(3 * sizeof(int *));
    graph[0] = I;
    graph[1] = J;
    graph[2] = val;

    printGraph(matcode, M, N, nz, graph);

    return graph;
}

int main(int argc, char *argv[])
{
    MM_typecode matcode;
    FILE *f;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
        exit(1);
    }
    else
    {
        if ((f = fopen(argv[1], "r")) == NULL)
            exit(1);
    }

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }

    int **g = readFile(f, matcode);
    free(g[0]);
    free(g[1]);
    free(g[2]);
    free(g);
    return 0;
}