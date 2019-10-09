#include <stdio.h>
#include <stdlib.h>

/**

	Variaveis Globais

*/

int dimension = 0;

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

void UPPER_DIAG_ROW (int m[][dimension], int *v, int dimension)
{
	int i,k=1,j=0,diag=0;

	for(i = 0 ; i < (dimension*dimension+dimension)/2 ; i++)
	{
 		if(v[i]==0)
		{
		 	//printf("acessando diagonal %d\t",diag);  
  			m[diag][diag]=v[i];
  			//printf("posicao diag encontrada %d\t",m[diag][diag]);
  			//printf("posicao do i = %d\t",i);
  			k=diag+1;
  			//printf("novo k=%d\t",k);
  			j=diag;
  			//printf("novo j=%d\n",j);
  			diag++;  
		}
 		else
		{
  			m[k][j]= v[i];
  			//printf("posicao encontrada %d\t",m[k][j]);
  			m[j][k]= v[i];
  			//printf("posicao inv encontrada %d\t",m[j][k]);
  			k++;
  			//printf("novo k=%d\n",k);
 		}
	}
}

void LOWER_DIAG_ROW (int m[][dimension], int *v, int dimension)
{
	int i,k=0,j=0,diag=0;

	for(i=0;i<(dimension*dimension+dimension)/2;i++)
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

void UPPER_ROW (int m[][dimension], int *v, int dimension)
{
	int i,k=0,j=1,diag=0;
	
	for(i=0;i<dimension;i++)
	{
		m[i][i]=0;
	}
	for(i=0;i<dimension*(dimension-1)/2;i++)
	{		
		if(j==dimension)
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
    fscanf(arq, "%s %s", field, type);
    fscanf(arq, "%s", field);
 	fgets(comment, 100, arq);
    fscanf(arq, "%s %d", field, &dimension);
    fscanf(arq, "%s %s", field, ewType);
    fscanf(arq, "%s %s", field, ewFormat);
    fscanf(arq, "%s %s", field, display);
    fscanf(arq, "%s", field);
    printf("NAME: %s\nTYPE: %s\nCOMMENT: %s\nDIMENSION: %d\nEDGE_WEIGHT_TYPE: %s\nEDGE_WEIGHT_FORMAT: %s\nDISPLAY_DATA_TYPE: %s\n", nome, type, comment, dimension, ewType, ewFormat, display);
    printf("%s\n", field);

    int tam = count_qtd_upper_diag(dimension);
    printf("TAMANHO DO VETOR: %d\n\n", tam);
    int v[tam];
    int m[dimension][dimension];

    for(i = 0 ; i < tam ; i++)
    {
        fscanf(arq, "%d", &v[i]);
    }  
    
    LOWER_DIAG_ROW(m, v, dimension);
    
    for(i=0;i<dimension;i++)
	{
 		for(j=0;j<dimension;j++)
		{
			printf("%d\t",m[i][j]);
 	 	}
 		printf("\n");
	}

    fclose(arq);
}

int main()
{
    readFile("gr24.tsp.txt");

    return 0;
}
