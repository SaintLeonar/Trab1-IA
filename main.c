#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
/**

Variaveis Globais

*/

void menu();

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

/**

    VERIFICA SE UM DETERMINADO VALOR ESTA CONTIDO EM UM VETOR

*/
bool exists(int val, int *v, int tam)
{
    int i;

    for(i = 0 ; i < tam ; i++)
    {
        if(v[i] == val)
            return true;
    }
    return false;
}
/**

    GERA UM VETOR DE NUMEROS ALEATÓRIOS

*/
void setVetRandom(int *vRandom)
{
    srand(time(NULL));
    int i, val;
    vRandom[0] = 0;

    for(i = 1 ; i < dimension ; i++)
    {
        val = rand() % dimension;
        while(exists(val, vRandom, i))
        {
            val = rand() % dimension;
        }

        vRandom[i] = val;
    }
}

/**

    UPPER_DIAG_ROW, LOWER_DIAG_ROW E UPPER_ROW
    ORGANIZAM A MATRIZ DE ADJACÊNCIAS

*/
void UPPER_DIAG_ROW (int m[][dimension], int *v, int dimension)
{
int i,k=1,j=0,diag=0;

for(i = 0 ; i < (dimension*dimension+dimension)/2 ; i++)
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

/**

    PRINTA A INFORMAÇÃO DO ARQUIVO

*/
void showInfo(char *str)
{
    printf("%s", str);
}

/**

    PRINTA UM VETOR

*/
void showVet(int *v,int tam)
{
    int i;

    for(i = 0 ; i < tam ; i++)
    {
        printf("%d ", v[i]);
    }
}

/**

    PRINTA A MATRIZ DE ADJACÊNCIAS

*/
void showMat(int m[][dimension])
{
    int i, j;
    printf("\n");
    for(i = 0 ; i < dimension ; i++)
    {
        for(j = 0 ; j < dimension ; j++)
        {
            printf("%d  ",m[i][j]);
        }
        printf("\n");
    }
}

/**

    INICIALIZA UM VETOR COM -1

*/
void inicializaVetor(int *v, int tam)
{
    int i;
    for(i = 0 ; i < tam ; i++)
    {
        v[i] = -1;
    }
}

/**

    FAZ A COPIA DE UM VETOR

*/
void vetcpy(int *dest, int *orig, int tam)
{
    int i;

    for(i = 0 ; i < tam ; i++)
    {
        dest[i] = orig[i];
    }
}

/**

    RETORNA O CUSTO DE UM VETOR DE DISTANCIAS

*/
int getCusto(int *vDist)
{
    int i, sum = 0;
    for(i = 0 ; i < dimension ; i++)
    {
        sum = sum + vDist[i];
    }

    return sum;
}

/**

    BUSCA META-HEURÍSTICA: Simulated Annealing

*/
void simulatedAnnealing(int m[][dimension])
{
    int custo, vDist[dimension], vRandom[dimension], vAux[dimension], route[dimension], controle = 0;
    int nParada = 50000, menorCusto = 9999999;
    int i, k, j = 0;
    int retMenu = -1;
    clock_t iniTempo = 0;
    clock_t fimTempo;
    double tempoCPU;

    system("cls");

    inicializaVetor(vDist, dimension);
    inicializaVetor(vRandom, dimension);
    inicializaVetor(vAux, dimension);
    setVetRandom(vRandom);

    for(k = 0 ; k < nParada ; k++)
    {
        printf("==> Tentativa numero: %d\n==> Controle: %d\n\n", k, controle);
        setVetRandom(vRandom); // GERA UMA ROTA ALEATORIA

        for(i = 1 ; i < dimension ; i++)
        {
            vAux[i-1] = m[j][vRandom[i]]; //PEGA AS DISTANCIAS DA ROTA ALEATORIA
            j = vRandom[i]; // j = CIDADE VISITADA
        }
        vRandom[dimension-1] = 0; // ULTIMA CIDADE ==> CIDADE INICIAL
        vAux[dimension-1] = m[j][0]; // ULTIMA POSIÇÃO ==> DISTANCIA DA ULTIMA CIDADE VISITADA ATÉ A CIDADE ORIGINAL
        custo = getCusto(vAux); // CALCULA DO CUSTO DA ROTA

        printf("(!) Busca parcial: \n");

        printf("\n[SIMULATED ANNEALING] Rota Percorrida: ");
        showVet(vRandom, dimension);
        printf("\n\n[SIMULATED ANNEALING] Custo total: %d\n\n", custo);
        printf("_________________________________________________________________________________________________________");

        // VERIFICA SE CUSTO ATUAL É MENOR QUE O ANTERIOR
        if(custo < menorCusto)
        {
            //SE FOR MENOR ATUALIZA A ROTA E O CUSTO
            menorCusto = custo;
            vetcpy(route, vRandom, dimension);
            controle = 0;
        }
        else{controle++;}

        if(controle == 1000)
        {
            system("cls");

            break;
        }

        printf("\n\n(!) Melhor rota ate agora: \n");

        printf("\n[SIMULATED ANNEALING] Rota Percorrida: ");
        showVet(route, dimension);
        printf("\n\n[SIMULATED ANNEALING] Custo total: %d\n\n", menorCusto);
        system("cls");
    }
    fimTempo = clock();
    tempoCPU = ((double) (fimTempo - iniTempo)) / CLOCKS_PER_SEC; // CALCULA O TEMPO DE EXECUÇÃO DA BUSCA

    printf("==> Tentativa numero: %d\n\n", k);
    printf("\n\n[SIMULATED ANNEALING] Rota Percorrida: ");
    showVet(route, dimension);
    printf("\n\n[SIMULATED ANNEALING] Custo total: %d\n\n", menorCusto);
    printf("[SIMULATED ANNEALING] Tempo cronometrado: %f segundos\n", tempoCPU);

    printf("\n(1)    : SIM\n(ELSE) : NAO\n\n==>Deseja retornar ao menu principal? ");
    scanf("%d", &retMenu);
    if(retMenu == 1)
        menu();

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

    printf("_________________________________________________________________________________________________________\n");

    return dimension;
}

void readFile (char *path)
{
    int escolha = -1, i, tam = 0;
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
        LOWER_DIAG_ROW(m, v, dimension);
        printf("\n\n(1)    : Simulated Annealing\n(2)    : Iterated Local Search\n(ELSE) : Voltar\n\n==>Qual algoritmo de busca deseja utilizar? ");
            scanf("%d", &escolha);
            switch(escolha)
            {
                case 1 :
                    simulatedAnnealing(m);
                    break;

                case 2 :
                    printf("VOCE CHAMOU O Iterated Local Search!\n");
                    // YURI CHAMA A FUNÇÃO ILS AQUI <===
                    break;
                default :
                    menu();
                    break;
            }
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
            UPPER_DIAG_ROW(m, v, dimension);

            printf("\n\n(1)    : Simulated Annealing\n(2)    : Iterated Local Search\n(ELSE) : Voltar\n\n==>Qual algoritmo de busca deseja utilizar? ");
            scanf("%d", &escolha);
            switch(escolha)
            {
                case 1 :
                    simulatedAnnealing(m);
                    break;

                case 2 :
                    printf("VOCE CHAMOU O Iterated Local Search!\n");
                    // YURI CHAMA A FUNÇÃO ILS AQUI <===
                    break;
                default :
                    menu();
                    break;
            }
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
            UPPER_ROW(m, v, dimension);

            printf("\n\n(1)    : Simulated Annealing\n(2)    : Iterated Local Search\n(ELSE) : Voltar\n\n==>Qual algoritmo de busca deseja utilizar? ");
            scanf("%d", &escolha);
            switch(escolha)
            {
                case 1 :
                    simulatedAnnealing(m);
                    break;

                case 2 :
                    printf("VOCE CHAMOU O Iterated Local Search!\n");
                    // YURI CHAMA A FUNÇÃO ILS AQUI <===
                    break;
                default :
                    menu();
                    break;
            }
        }

    fclose(arq);
}

void menu()
{
    int escolha = -1;
    char *file1 = "brazil58.tsp.txt", *file2 = "gr120.tsp.txt", *file3 = "hk48.tsp.txt", *file4 = "si175.tsp.txt", *file5 = "gr24.tsp.txt";

    system("cls");

    printf("(1) : brazil58.tsp.txt\n(2) : gr120.tsp.txt\n(3) : hk48.tsp.txt\n(4) : si175.tsp.txt\n(5) : gr24.tsp.txt\n\n==>Qual algoritmo de busca deseja utilizar?\n");
    scanf("%d", &escolha);

    switch(escolha)
    {
        case 1 :
            printf("VOCE ESCOLHEU O ARQUIVO: %s\n\n", file1);
            system("cls");
            readFile(file1);
            break;
        case 2 :
            printf("VOCE ESCOLHEU O ARQUIVO: %s\n\n", file2);
            system("cls");
            readFile(file2);
            break;
        case 3 :
            printf("VOCE ESCOLHEU O ARQUIVO: %s\n\n", file3);
            system("cls");
            readFile(file3);
            break;
        case 4 :
            printf("VOCE ESCOLHEU O ARQUIVO: %s\n\n", file4);
            system("cls");
            readFile(file4);
            break;
        case 5 :
            printf("VOCE ESCOLHEU O ARQUIVO: %s\n\n", file5);
            system("cls");
            readFile(file5);
            break;
        default :
            system("cls");
            menu();
    }
}

int main()
{
    menu();

    return 0;
}
