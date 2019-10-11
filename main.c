#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**

	Variaveis Globais

*/

int dimension = 0;

/**

    Retorna o tamanho do vetor de valores baseado na dimensão
    Só funciona para formatos UPPER_DIAG_ROW ou LOWER_DIAG_ROW

*/
int setVetTam_Diag(int dimension)
{
    return (dimension*dimension+dimension)/2;
}

/**

    Retorna o tamanho do vetor de valores baseado na dimensão
    Só funciona para formato UPPER_ROW

*/
int setVetTam_UPPER_ROW(int dimension)
{
    return (dimension*(dimension-1)/2);
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

 		printf("%d\t", m[k][j]);
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

/**

    PRINTA A INFORMAÇÃO DO ARQUIVO

*/
void showInfo(char *str)
{
    printf("%s", str);
}

/**

    PRINTA O VETOR

*/
void showVet(int *v,int tam)
{
    int i;

    for(i = 0 ; i < tam ; i++)
    {
        printf("%d\t", v[i]);
    }
}

/**

    PRINTA A MATRIZ

*/
void showMat(int m[][dimension],int dimension)
{
    int i, j;

    for(i = 0 ; i < dimension ; i++)
	{
 		for(j = 0 ; j < dimension ; j++)
		{
			printf("%d ",m[i][j]);
 	 	}
 		printf("\n");
	}
}

/**

    RETORNA A DIMENSÃO DA MATRIZ E O FORMATO DOS DADOS
    PRINTA INTERNAMENTE AS INFORMAÇÕES DO ARQUIVO

*/
int getDim_Format(FILE *arq, char *format)
{
    char line[50], dimensionC[4];
    int i, aux, cPos, dimension;

    for(i = 0 ; strstr(line, "EDGE_WEIGHT_SECTION") == NULL ; i++)
    {
        fgets(line, 50, arq);
        cPos = 0;
        aux = 0;

        showInfo(line);

        for(; line[aux] != ':' ; aux++) {continue;}
        aux = aux + 2;

        if( strstr(line, "DIMENSION") != NULL )
        {
            for(; line[aux] != '\n' ; aux++)
            {
                dimensionC[cPos] = line[aux];
                cPos++;
            }
            dimensionC[cPos] = '\0';
            dimension = atoi(dimensionC);
        }

        if( strstr(line, "EDGE_WEIGHT_FORMAT") != NULL )
        {
            for(; line[aux] != '\n' ; aux++)
            {
                format[cPos] = line[aux];
                cPos++;
            }
            format[cPos] = '\0';
        }
    }

    return dimension;
}

void readFile (char *path)
{
    int i, tam = 0;
    char format[15];
    strcpy(format, "");

    FILE *arq = fopen(path, "r");

    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo %s", path);
        exit(-1);
    }

    dimension = getDim_Format(arq, format);

    if(strstr(format,"LOWER_DIAG_ROW") != NULL)
    {
        tam = setVetTam_Diag(dimension);
        int v[tam];
        int m[dimension][dimension];
        for(i = 0 ; i < tam ; i++)
        {
            fscanf(arq, "%d", &v[i]);
        }
        showVet(v, tam);

        //LOWER_DIAG_ROW(m, v, dimension);
        //showMat(m, dimension);
    }
    else
        if(strstr(format, "UPPER_DIAG_ROW") != NULL)
        {
            tam = setVetTam_Diag(dimension);
            int v[tam];
            int m[dimension][dimension];
            for(i = 0 ; i < tam ; i++)
            {
                fscanf(arq, "%d", &v[i]);
            }
            showVet(v, tam);

            //UPPER_DIAG_ROW(m, v, dimension);
            //showMat(m, dimension);
        }
    else
        if(strstr(format,"UPPER_ROW") != NULL)
        {
            tam = setVetTam_UPPER_ROW(dimension);
            int v[tam];
            int m[dimension][dimension];
            for(i = 0 ; i < tam ; i++)
            {
                fscanf(arq, "%d", &v[i]);
            }
            showVet(v, tam);

            //UPPER_ROW(m, v, dimension);
            //showMat(m, dimension);
        }

    fclose(arq);
}

int main()
{
    /**
        (!) ESCOLHA O ARQUIVO AQUI

        >>> brazil58.tsp.txt
        >>> gr120.tsp.txt
        >>> hk58.tsp.txt
        >>> si175.tsp.txt
        >>> gr24.tsp.txt
    */

    readFile("si175.tsp.txt");

    return 0;
}
