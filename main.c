#include <stdio.h>
#include <stdlib.h>

/**

	Variaveis Globais

*/

int tam = 0;

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

void UPPER_DIAG_ROW (int m[][tam], int *v, int tam)
{
	int i,k=1,j=0,diag=0;

	for(i = 0 ; i < tam ; i++)
	{
 		if(v[i]==0)
		 {  
  			m[diag][diag]=v[i];
  			k=diag+1;
  			j=diag;
  			diag++;  
		}
 		else
		{
  			m[k][j]= v[i];
  			m[j][k]= v[i];
  			k++;
 		}
	}
}

void LOWER_DIAG_ROW (int m[][tam], int *v, int tam)
{
	int i,k=0,j=0,diag=0;

	for(i=0;i<(tam*tam+tam)/2;i++)
	{
 		if(v[i]==0)
		{  
 			m[diag][diag]=v[i];
 		 	k=0;
 		 	j=diag+1;
 		 	diag++;  
		}
 		else
		{
			m[k][j]= v[i];
			m[j][k]= v[i];
  			k++;
 		}
 	}
}

void UPPER_ROW (int m[][tam], int *v, int tam)
{
	int i,k=0,j=1,diag=0;
	
	for(i=0;i<tam;i++)
	{
		m[i][i]=0;
	}
	for(i=0;i<tam*(tam-1)/2;i++)
	{		
		if(j==tam)
		{
			j=diag+2;
			k++;			
			diag++;
		}
		m[j][k]=v[i];
		m[k][j]=v[i];
		j++;	
	}
}

void readFile (char *path)
{
    int i, j, dimension;
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

    tam = count_qtd_upper_diag(dimension);
    printf("%d", tam);
    int v[tam];
    int m[dimension][dimension];

    for(i = 0 ; i < tam ; i++)
    {
        fscanf(arq, "%d", &v[i]);
        printf("%d\t", v[i]);
    }
    
    printf("\n\nFIM VETOR\n\n");
    
    /*
    UPPER_DIAG_ROW(m, v, tam);
    for(i=0;i<tam;i++)
	{
 		for(j=0;j<tam;j++)
		{
			printf("%d\t",m[i][j]);
 	 	}
 		printf("\n");
	}
	*/

    fclose(arq);
}

int main()
{
    readFile("si175.tsp.txt");

    return 0;
}
