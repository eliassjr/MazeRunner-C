#include "funcoes.h"

int matriz(valor)
{
    if (valor == 1)
    {
        fp = fopen("Matriz1.txt","r");
        linhas = 35;
        colunas = 40;
    }
    if (valor == 2)
    {
        fp = fopen("Matriz2.txt","r");
        linhas = 29;
        colunas = 40;
    }
    if (valor == 3)
    {
        fp = fopen("Matriz3.txt","r");
        linhas = 29;
        colunas = 40;
    }
    if (valor == 4)
    {
        fp = fopen("Matriz4.txt","r");
        linhas = 29;
        colunas = 55;
    }
    if (valor == 5)
    {
        fp = fopen("Matriz5.txt","r");
        linhas = 29;
        colunas = 55;
    }

        matriz_ptr = (int**)malloc(linhas*sizeof(int*));

        for(i = 0; i < linhas; i ++)
            matriz_ptr[i] = (int*)malloc(colunas * sizeof(int));

        for(i = 0; i < linhas; i ++)
        {
            for(j = 0; j < colunas; j++)
                fscanf(fp,"%d", &matriz_ptr[i][j]);
        }

        for(i = 0; i < linhas; i ++)
        {
            for(j = 0; j < colunas; j++)
            {
                gotoxy(j + posx_inicial ,i + posy_inicial );
                printf("%c",matriz_ptr[i][j]);
            }
        }
        fclose(fp);
}
