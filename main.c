#include <stdio.h>
#include <stdlib.h>

/**

    Função auxiliar que calcula a quantidade de itens da matriz triangular superior dada uma dimensão

*/
int count_qtd_upper_diag(int dimension)
{
    int sum = dimension;
    int i;
    for(i = dimension-1 ; i > 0 ; i--)
    {
        sum = sum + i;
    }

    return sum;
}
void readFile (char *path)
{
    int i, dimension;
    char field[20], nome[10], type[4], ewType[9], ewFormat[16], display[14], comment[100];

    FILE *arq = fopen(path, "r");

    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s", path);
        exit(-1);
    }

    fscanf(arq, "%s %s", field, nome);
    fscanf(arq, "%s %s %s", field, type, comment);
    fscanf(arq, "%s %d", field, &dimension);
    fscanf(arq, "%s %s", field, ewType);
    fscanf(arq, "%s %s", field, ewFormat);
    fscanf(arq, "%s %s", field, display);
    fscanf(arq, "%s", field);
    printf("NAME: %s\nTYPE: %s\nCOMMENT: %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nEDGE_WEIGHT_FORMAT: %s\nDISPLAY_DATA_TYPE: %s\n", nome, type, comment, dimension, ewType, ewFormat, display);

    int tam = count_qtd_upper_diag(dimension);
    int v[tam];

    for(i = 0 ; i < tam ; i++)
    {
        fscanf(arq, "%d", &v[i]);
        printf("%d\t", v[i]);
    }

    fclose(arq);
}

int main()
{
    readFile("si175.tsp.txt");

    return 0;
}
