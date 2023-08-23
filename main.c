//****************************************************************************
//*                       Projeto                                            *
//*                     Programa��o 2                                        *
//*                                                                          *
//****************************************************************************
//                     Elias Anzini Junior                                   *
//         IFSC - Instituto Federal de Santa Catarina                        *
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "le_teclas.h"
#include "my_lib.h"

#define lim_x_left  7
#define lim_x_right 50
#define lim_y_top   7
#define lim_y_down  40

#define desl_x      7
#define desl_y      7

#define posx_inicial 6
#define posy_inicial 6

#include "funcoes.c"
#include "funcoes.h"


int x,y,p,c,cont, parede=0, parede1, d=0, a, seta, parede2, parede3=0, parede4=0, parede5=0, parede6=0;
char KEY;



//********************************************************************
//*************** Declara��es para o Ranking *************************

FILE *placar;
int maior, k, j;

struct jogadores
{
    char jogador[50];
    int pontuacao;

}lista[100];


//********************************************************************
//********************************************************************

int main()
{
    textcolor(15);
    gotoxy(60,15);
    printf("******************************************************");
    gotoxy(60,16);
    printf("     ENCONTRE A PASSAGEM PARA O FINAL DO LABIRINTO!");
    gotoxy(60,17);
    printf("    TENTE OBTER O MENOR NUMERO DE PONTOS POSSIVEIS!!");
    gotoxy(60,18);
    printf("******************************************************");;
    gotoxy(60, 20);
    printf("                   PRIMEIRA FASE");

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    placar = fopen("Estrutura.txt","r");

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);

    struct jogadores *ptr;
    ptr = &lista;
    struct jogadores aux;


    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }

    printf("\t\t\t\t\t\t\t\t\t\t Placar Atual\n");
    printf("\t\t\t\t\t\t\t\t ------------------------------------------\n");

    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t\t\t\t   %s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }

    //******************************************************************************
    //******************************************************************************


    cursor_off();
    textcolor(15);


    matriz(1); //Cria��o da Matriz



    //****************************************************
    //          posi��o inicial do personagem
    //****************************************************
    x = desl_x;
    y = desl_y;
    //****************************************************

    gotoxy(80,11);
    printf("\tX = %2d -- Y = %2d", x ,y);
    gotoxy(x,y); // cursor
    printf("%c",207);

    do
    {
      gotoxy(90,5);
      printf("");
      gotoxy(80,11);
      printf("\tX = %2d -- Y = %2d", x ,y);
      KEY = tecla();

      gotoxy(89,9); // posi��o do texto informativo de qual seta foi usada
      printf("                         ");
      gotoxy(89,9);
      if(KEY == 1)
      {
          seta =  1;
          printf("Seta para cima");
          y--;
          gotoxy(x, y+1);
          printf("%c",255);

          //********************************************
          //   Restri��es de passagem
          //********************************************

          if (x!=30 || y!=28) // Passagem secreta ocorre quando x == 30 e y ==28;
          {
             if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17); // texto informativo s� para saber se encntrou uma barreira
                y++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont); //Contador de Pontos
              }
             else //Contador de Pontos
                {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
                }
          }
          else // Se for parede secreta ele ganha mais 5 pontos na primeira vez que passa nela, as outras ocorre a contagem de passos normalmente
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }

          }
          //*********************************************
          if(y < lim_y_top)
            y = lim_y_top;
      }
      else if(KEY == 2)
      {
          printf("Seta para baixo");
          y++;
          gotoxy(x, y-1);
          printf("%c",255);
          seta = 2;

          //********************************************
          //   Restri��es de passagem
          //*******************************************

          if ((x!=30 || y!=28) && ((((x != 9 || y != 10)) || (parede2 == 0))))   //Se n�o for parede secreta
          {
           if(((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)) || (matriz_ptr[y-desl_y +1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                y--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
            else
            {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
            }
          }

          if ((parede2 == 1) && (x==9 && y==10))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              }

          if  (x==30 && y==28) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y > lim_y_down)
            y = lim_y_down;
      }

      else if(KEY == 3)
        {
          printf("Seta para esquerda");
          x--;
          gotoxy(x+1, y);
          printf("%c",255);
          seta = 3;

          //********************************************
          //   Restri��es de passagem
          //********************************************
          if (((x != 13 || y != 11) || (parede1 == 0)) && ((x != 13 || y != 22) || (parede3 == 0)))
          {
          if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) ||  (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17);
                x++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
          else
              {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==13 && y==11))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede3 == 1) && (x==13 && y==22))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x < lim_x_left)
            x = lim_x_left;
        }
      else if(KEY == 4)
        {
           printf("Seta para direita");
           x++;
           gotoxy(x-1, y);
           printf("%c",255);
           seta = 4;

           //********************************************
          //   Restri��es de passagem
          //********************************************

          if (((x != 13 || y != 11) || (parede1 == 0)) && ((x != 13 || y != 22) || (parede3 == 0)))
          {
              if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                x--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
              else
              {
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==13 && y==11)) //Se estiver em cima da parede 1
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede3 == 1) && (x==13 && y==22)) //Se estiver em cima da parede 3
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if(matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)
              {

                gotoxy(60,17);
                x--;
              }
          //*********************************************
          if(x > lim_x_right)
            x = lim_x_right;
        }

      else if(KEY == 5)
      {
      while (d<3)
        {
            if (seta == 4)

            {
                if((((y==11) && (x==12)) && (parede1 == 0))|| (((y==11) && (x==11)) && (parede1 == 0)))        //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if(((((y==22) && (x==12)) && (parede3 == 0))|| (((y==22) && (x==11)) && (parede3 == 0))) || (((y==22) && (x==10)) && (parede3 == 0)))       //Posi��es que vai quebrar a parede e pontuar
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x + d + 2] == 178)
              {
                break;
              }
           gotoxy(x+d+1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x+d+1, y);
           printf("%c", 255);
           d++;
            }
            if (seta == 2 )
            {
                if((((y==8) && (x==9)) && (parede2 == 0))|| (((y==9) && (x==9)) && (parede2 == 0)))   //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 2 + d][x-desl_x + 1] == 178)
              {
                break;
              }
           gotoxy(x, y+d+1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y+d+1);
           printf("%c", 255);
           d++;
            }

            if (seta == 3 )
            {
                if ((((y==11) && (x==16)) && (parede1 == 0))|| (((y==11) && (x==15)) && (parede1 == 0)) || (((y==11) && (x==14)) && (parede1 == 0)))

            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;

            }
            if ((((y==22) && (x==16)) && (parede3 == 0))|| (((y==22) && (x==15)) && (parede3 == 0)) || (((y==22) && (x==14)) && (parede3 == 0)))
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x - d ] == 178)
              {
                break;
              }
           gotoxy(x-d-1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x-d-1, y);
           printf("%c", 255);
           d++;
            }

            if (seta == 1 )
            {
                if (matriz_ptr[y-desl_y - d][x-desl_x +1 ] == 178)
              {
                break;
              }
           gotoxy(x, y-d-1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y - d - 1);
           printf("%c", 255);
           d++;
            }
        }
      d=0;
      }
      else if(KEY == 7)
        printf("Tab esquerdo");
      else if(KEY == 8)
        printf("Tab direito");
      else if(KEY == 6)
      {
      }
      else if (x == 36 && y ==31)
     {
         clrscr();
         break;
     }

     //********************************************
     //          Posi��o do personagem
     //********************************************
            gotoxy(x,y); // cursor
            printf("%c",207);

     //*******************************************

    }while(1);

     parede  = 0;
     parede1 = 0;
     parede2 = 0;
     parede3 = 0;
     free(matriz_ptr);

   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**********************************                                                TELA 2                                               ***********************************
   //**********************************                                                TELA 2                                               ***********************************
   //**********************************                                                TELA 2                                               ***********************************
   //**********************************                                                TELA 2                                               ***********************************
   //**********************************                                                TELA 2                                               ***********************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************

    textcolor(3);
    gotoxy(60,15);
    printf("******************************************************");
    gotoxy(60,16);
    printf("     ENCONTRE A PASSAGEM PARA O FINAL DO LABIRINTO!");
    gotoxy(60,17);
    printf("    TENTE OBTER O MENOR NUMERO DE PONTOS POSSIVEIS!!");
    gotoxy(60,18);
    printf("******************************************************");;
    gotoxy(60, 20);
    printf("                    SEGUNDA FASE");
    gotoxy(90, 5);
    printf(" ");

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    //Leitura do Placar
    gotoxy(60, 20);
    placar = fopen("Estrutura.txt","r");

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);


    //L�gica do Placar
    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }
    //Printf do Placar
    printf("\t\t\t\t\t\t\t\t\t\t Placar Atual\n");
    printf("\t\t\t\t\t\t\t\t ------------------------------------------\n");

    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t\t\t\t   %s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }

    //******************************************************************************
    //******************************************************************************

    textcolor(3);
    matriz(2);
    textcolor(15);

    //****************************************************
    //          posi��o inicial do personagem
    //****************************************************
    x = desl_x;
    y = desl_y;
    //****************************************************
    gotoxy(80,11);
    printf("\tX = %2d -- Y = %2d", x ,y);
    gotoxy(x,y); // cursor
    printf("%c",207);
    do
    {
      gotoxy(80,11);
      printf("\tX = %2d -- Y = %2d", x ,y);
      KEY = tecla();

      gotoxy(89,9); // posi��o do texto informativo de qual seta foi usada
      printf("                         ");
      gotoxy(89,9);
      if(KEY == 1)
      {
          seta =  1;
          printf("Seta para cima");
          y--;
          gotoxy(x, y+1);
          printf("%c",255);

          //********************************************
          //   Restri��es de passagem
          //********************************************

          if ((x!=34 || y!=9) && ((((x != 7 || y != 18)) || (parede2 == 0))))  // Passagem secreta ocorre quando x == 34 e y ==9;
          {
             if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17); // texto informativo s� para saber se encntrou uma barreira
                y++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont); //Contador de Pontos
              }
             else //Contador de Pontos
                {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
                }
          }

          if(x==34 && y==9) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }

          if ((parede2 == 1) && (x==7 && y==18))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(y < lim_y_top)
            y = lim_y_top;
      }
      else if(KEY == 2)
      {
          printf("Seta para baixo");
          y++;
          gotoxy(x, y-1);
          printf("%c",255);
          seta = 2;

          //********************************************
          //   Restri��es de passagem
          //*******************************************

          if ((x!=34 || y!=9) && ((((x != 7 || y != 18)) || (parede2 == 0))))   //Se n�o for parede secreta
          {
           if(((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)) || (matriz_ptr[y-desl_y +1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                y--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
            else
            {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
            }
          }
          if ((parede2 == 1) && (x==7 && y==18))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              }

          if  (x==34 && y==9) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y > lim_y_down)
            y = lim_y_down;
      }

      else if(KEY == 3)
        {
          printf("Seta para esquerda");
          x--;
          gotoxy(x+1, y);
          printf("%c",255);
          seta = 3;

          //********************************************
          //   Restri��es de passagem
          //********************************************

          if ((x != 12 || y != 14) || (parede1 == 0))
          {
          if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) ||  (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17);
                x++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
          else
              {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==12 && y==14))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x < lim_x_left)
            x = lim_x_left;
        }
      else if(KEY == 4)
        {
           printf("Seta para direita");
           x++;
           gotoxy(x-1, y);
           printf("%c",255);
           seta = 4;

           //********************************************
          //   Restri��es de passagem
          //********************************************

          if ((x != 12 || y != 14) || (parede1 == 0))
          {
              if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                x--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
              else
              {
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==12 && y==14)) //Se estiver em cima da parede 1
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if(matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)
              {

                gotoxy(60,17);
                x--;
              }
          //*********************************************
          if(x > lim_x_right)
            x = lim_x_right;
        }

      else if(KEY == 5)
      {
      while (d<3)
        {
            if (seta == 4)

            {
                if((((y==14) && (x==10)) && (parede1 == 0))|| (((y==14) && (x==11)) && (parede1 == 0)))        //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x + d + 2] == 178)
              {
                break;
              }
           gotoxy(x+d+1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x+d+1, y);
           printf("%c", 255);
           d++;
            }
            if (seta == 2 )
            {
                if(((((y==17) && (x==7)) && (parede2 == 0))|| (((y==16) && (x==7)) && (parede2 == 0))) || (((y==15) && (x==7)) && (parede2 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 2 + d][x-desl_x + 1] == 178)
              {
                break;
              }
           gotoxy(x, y+d+1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y+d+1);
           printf("%c", 255);
           d++;
            }

            if (seta == 3 )
            {
                if (matriz_ptr[y-desl_y + 1][x-desl_x - d ] == 178)
              {
                break;
              }
           gotoxy(x-d-1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x-d-1, y);
           printf("%c", 255);
           d++;
            }

            if (seta == 1 )
            {
                if (matriz_ptr[y-desl_y - d][x-desl_x +1 ] == 178)
              {
                break;
              }
           gotoxy(x, y-d-1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y - d - 1);
           printf("%c", 255);
           d++;
            }
        }
      d=0;
      }
      else if(KEY == 7)
        printf("Tab esquerdo");
      else if(KEY == 8)
        printf("Tab direito");
      else if(KEY == 6)
      {

      }
      else if (x == 36 && y ==10)
     {
         clrscr();
         break;
     }

     //********************************************
     //          Posi��o do personagem
     //********************************************
            gotoxy(x,y); // cursor
            printf("%c",207);
     //*******************************************

    }while(1);

     parede  = 0;
     parede1 = 0;
     parede2 = 0;
     parede3 = 0;
     free(matriz_ptr);

    //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**********************************                                                TELA 3                                               ***********************************
   //**********************************                                                TELA 3                                               ***********************************
   //**********************************                                                TELA 3                                               ***********************************
   //**********************************                                                TELA 3                                               ***********************************
   //**********************************                                                TELA 3                                               ***********************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************


    #define lim_x_left  7
    #define lim_x_right 55
    #define lim_y_top   7
    #define lim_y_down  40

    #define desl_x      7
    #define desl_y      7

    #define posx_inicial 6
    #define posy_inicial 6

    parede  = 0;
    parede1 = 0;
    parede2 = 0;
    parede3 = 0;

    textcolor(6);
    gotoxy(60,15);
    printf("******************************************************");
    gotoxy(60,16);
    printf("     ENCONTRE A PASSAGEM PARA O FINAL DO LABIRINTO!");
    gotoxy(60,17);
    printf("    TENTE OBTER O MENOR NUMERO DE PONTOS POSSIVEIS!!");
    gotoxy(60,18);
    printf("******************************************************");;
    gotoxy(60, 20);
    printf("                   TERCEIRA FASE");
    gotoxy(90, 5);
    printf(" ");

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    //Leitura do Placar
    gotoxy(60, 20);
    placar = fopen("Estrutura.txt","r");

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);


    //L�gica do Placar
    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }
    //Printf do Placar
    printf("\t\t\t\t\t\t\t\t\t\t Placar Atual\n");
    printf("\t\t\t\t\t\t\t\t ------------------------------------------\n");

    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t\t\t\t   %s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    matriz(3);
    textcolor(15);

    //****************************************************
    //          posi��o inicial do personagem
    //****************************************************
    x = desl_x;
    y = desl_y;
    //****************************************************
    gotoxy(80,11);
    printf("\tX = %2d -- Y = %2d", x ,y);
    gotoxy(x,y); // cursor
    printf("%c",207);
    do
    {
      gotoxy(80,11);
      printf("\tX = %2d -- Y = %2d", x ,y);
      KEY = tecla();

      gotoxy(89,9); // posi��o do texto informativo de qual seta foi usada
      printf("                         ");
      gotoxy(89,9);
      if(KEY == 1)
      {
          seta =  1;
          printf("Seta para cima");
          y--;
          gotoxy(x, y+1);
          printf("%c",255);
          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((x!=39 || y!=8) && ((((x != 7 || y != 18)) || (parede2 == 0))))  // Passagem secreta ocorre quando x == 39 e y ==8;
          {
             if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17); // texto informativo s� para saber se encntrou uma barreira
                y++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont); //Contador de Pontos
              }
             else //Contador de Pontos
                {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
                }
          }

          if((x==39 && y==8)) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }

          if ((parede2 == 1) && (x==7 && y==18))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(y < lim_y_top)
            y = lim_y_top;
      }
      else if(KEY == 2)
      {
          printf("Seta para baixo");
          y++;
          gotoxy(x, y-1);
          printf("%c",255);
          seta = 2;
          //********************************************
          //   Restri��es de passagem
          //*******************************************

          if ((x!=39 || y!=8) && ((((x != 7 || y != 18)) || (parede2 == 0))))   //Se n�o for parede secreta
          {
           if(((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)) || (matriz_ptr[y-desl_y +1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                y--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
            else
            {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
            }
          }
          if ((parede2 == 1) && (x==7 && y==18))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              }

          if  (x==39 && y==8) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y > lim_y_down)
            y = lim_y_down;
      }

      else if(KEY == 3)
        {
          printf("Seta para esquerda");
          x--;
          gotoxy(x+1, y);
          printf("%c",255);
          seta = 3;

          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((((((((x != 19 || y != 11) || (parede1 == 0)) && ((((x != 15 || y != 13)) || (parede2 == 0)))) && ((((x != 25 || y != 30)) || (parede4 == 0)))) && ((((x != 9 || y != 32)) || (parede3 == 0))))
           && ((((x != 25 || y != 21)) || (parede5 == 0))))) && ((((x != 36 || y != 28)) || (parede6 == 0))))
          {
          if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) ||  (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17);
                x++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
          else
              {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==19 && y==11))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede2 == 1) && (x==15 && y==13))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede3 == 1) && (x==9 && y==32))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede4 == 1) && (x==25 && y==30))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede5 == 1) && (x==25 && y==21))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede6 == 1) && (x==36 && y==28))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x < lim_x_left)
            x = lim_x_left;
        }
      else if(KEY == 4)
        {
           printf("Seta para direita");
           x++;
           gotoxy(x-1, y);
           printf("%c",255);
           seta = 4;

           //********************************************
          //   Restri��es de passagem
          //********************************************

          if ((((((((x != 19 || y != 11)) || (parede1 == 0)) && ((((x != 15 || y != 13)) || (parede2 == 0)))) && ((((x != 9 || y != 32)) || (parede3 == 0)))) && ((((x != 25 || y != 30)) ||
        (parede4 == 0)))) && ((((x != 25 || y != 21)) || (parede5 == 0))))  &&   ((((x != 36 || y != 28)) || (parede6 == 0))))     //   Restri��es de passagem ocorrem em todas as coordenadas menos na passagem secreta, al�m de quando quebrar o bloco a restri��o � desabilitada naquele ponto
          {
              if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                x--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
              else
              {
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==19 && y==11)) //Se estiver em cima da parede 1
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
           if ((parede2 == 1) && (x==15 && y==13)) //Se estiver em cima da parede 2
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede3 == 1) && (x==9 && y==32)) //Se estiver em cima da parede 3
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede4 == 1) && (x==25 && y==30)) //Se estiver em cima da parede 4
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
           if ((parede5 == 1) && (x==25 && y==21)) //Se estiver em cima da parede 5
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede6 == 1) && (x==36 && y==28)) //Se estiver em cima da parede 6
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x > lim_x_right)
            x = lim_x_right;
        }

      else if(KEY == 5)
      {
      while (d<3)
        {
            if (seta == 4)

            {
                if(((((y==11) && (x==16)) && (parede1 == 0)) || (((y==11) && (x==17)) && (parede1 == 0))) || (((y==11) && (x==18)) && (parede1 == 0))) //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
            if(((y==13) && (x==14)) && (parede2 == 0)) //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
             if(((y==32) && (x==8)) && (parede3 == 0)) //Posi��es que vai quebrar a parede e pontuar
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

            if((((y==21) && (x==23)) && (parede5 == 0)) || ((y==21) && (x==24)) && (parede5 == 0)) //Posi��es que vai quebrar a parede e pontuar
            {
                parede5 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

             if(((((y==28) && (x==35)) && (parede6 == 0)) || (((y==28) && (x==34)) && (parede6 == 0))) || (((y==28) && (x==33)) && (parede6 == 0))) //Posi��es que vai quebrar a parede e pontuar
            {
                parede6 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

                if (matriz_ptr[y-desl_y + 1][x-desl_x + d + 2] == 178)
              {
                break;
              }
           gotoxy(x+d+1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x+d+1, y);
           printf("%c", 255);
           d++;
            }
            if (seta == 2 )
            {
                if(((((y==17) && (x==7)) && (parede2 == 0))|| (((y==16) && (x==7)) && (parede2 == 0))) || (((y==15) && (x==7)) && (parede2 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 2 + d][x-desl_x + 1] == 178)
              {
                break;
              }
           gotoxy(x, y+d+1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y+d+1);
           printf("%c", 255);
           d++;
            }

            if (seta == 3 )
            {
               if(((((y==30) && (x==26)) && (parede4 == 0))|| (((y==30) && (x==27)) && (parede4 == 0))) || (((y==30) && (x==28)) && (parede4 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede4 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x - d ] == 178)
              {
                break;
              }
           gotoxy(x-d-1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x-d-1, y);
           printf("%c", 255);
           d++;
            }

            if (seta == 1 )
            {
                if (matriz_ptr[y-desl_y - d][x-desl_x +1 ] == 178)
              {
                break;
              }
           gotoxy(x, y-d-1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y - d - 1);
           printf("%c", 255);
           d++;
            }
        }
      d=0;
      }
      else if(KEY == 7)
        printf("Tab esquerdo");
      else if(KEY == 8)
        printf("Tab direito");
      else if(KEY == 6)
      {

      }
      else if (x == 42 && y ==7)
     {
         clrscr();
         break;
     }

     //********************************************
     //          Posi��o do personagem
     //********************************************
            gotoxy(x,y); // cursor
            printf("%c",207);
     //*******************************************

    }while(1);
    free(matriz_ptr);


    //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**********************************                                                TELA 4                                               ***********************************
   //**********************************                                                TELA 4                                               ***********************************
   //**********************************                                                TELA 4                                               ***********************************
   //**********************************                                                TELA 4                                               ***********************************
   //**********************************                                                TELA 4                                               ***********************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************

    parede  = 0;
    parede1 = 0;
    parede2 = 0;
    parede3 = 0;
    parede4 = 0;
    parede5 = 0;
    parede6 = 0;


    textcolor(12);
    gotoxy(60,15);
    printf("******************************************************");
    gotoxy(60,16);
    printf("     ENCONTRE A PASSAGEM PARA O FINAL DO LABIRINTO!");
    gotoxy(60,17);
    printf("    TENTE OBTER O MENOR NUMERO DE PONTOS POSSIVEIS!!");
    gotoxy(60,18);
    printf("******************************************************");;
    gotoxy(60, 20);
    printf("                      QUARTA FASE");
    gotoxy(90, 5);
    printf(" ");

   //*****************************  PLACAR  ***************************************
    //******************************************************************************

    //Leitura do Placar
    gotoxy(60, 20);
    placar = fopen("Estrutura.txt","r");

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);


    //L�gica do Placar
    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }
    //Printf do Placar
    printf("\t\t\t\t\t\t\t\t\t\t Placar Atual\n");
    printf("\t\t\t\t\t\t\t\t ------------------------------------------\n");

    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t\t\t\t   %s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    matriz(4);
    textcolor(15);

    //****************************************************
    //          posi��o inicial do personagem
    //****************************************************
    x = desl_x;
    y = desl_y;
    //****************************************************
    gotoxy(80,11);
    printf("\tX = %2d -- Y = %2d", x ,y);
    gotoxy(x,y); // cursor
    printf("%c",207);
    do
    {
      gotoxy(80,11);
      printf("\tX = %2d -- Y = %2d", x ,y);
      KEY = tecla();

      gotoxy(89,9); // posi��o do texto informativo de qual seta foi usada
      printf("                         ");
      gotoxy(89,9);
      if(KEY == 1)
      {
          seta =  1;
          printf("Seta para cima");
          y--;
          gotoxy(x, y+1);
          printf("%c",255);
          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((x!=43 || y!=8))  // Passagem secreta ocorre quando x == 43 e y ==8;
          {
             if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17); // texto informativo s� para saber se encntrou uma barreira
                y++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont); //Contador de Pontos
              }
             else //Contador de Pontos
                {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
                }
          }

          if((x==43 && y==8)) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y < lim_y_top)
            y = lim_y_top;
      }
      else if(KEY == 2)
      {
          printf("Seta para baixo");
          y++;
          gotoxy(x, y-1);
          printf("%c",255);
          seta = 2;
          //********************************************
          //   Restri��es de passagem
          //*******************************************

          if ((x!=43 || y!=8))   //Se n�o for parede secreta
          {
           if(((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)) || (matriz_ptr[y-desl_y +1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                y--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
            else
            {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
            }
          }
          if  (x==43 && y==8) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y > lim_y_down)
            y = lim_y_down;
      }

      else if(KEY == 3)
        {
          printf("Seta para esquerda");
          x--;
          gotoxy(x+1, y);
          printf("%c",255);
          seta = 3;

          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((((x != 14 || y != 7) || (parede1 == 0)) && ((((x != 14 || y != 31)) || (parede2 == 0))))  && ((((x != 47 || y != 7)) || (parede3 == 0))))
          {
          if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) ||  (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17);
                x++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
          else
              {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==14 && y==7))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede2 == 1) && (x==14 && y==31))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede3 == 1) && (x==47 && y==7))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x < lim_x_left)
            x = lim_x_left;
        }
      else if(KEY == 4)
        {
           printf("Seta para direita");
           x++;
           gotoxy(x-1, y);
           printf("%c",255);
           seta = 4;

           //********************************************
          //   Restri��es de passagem
          //********************************************

          if (((((x != 14 || y != 7)) || (parede1 == 0)) && ((((x != 14 || y != 31)) || (parede2 == 0)))) && ((((x != 47 || y != 7)) || (parede3 == 0))))     //   Restri��es de passagem ocorrem em todas as coordenadas menos na passagem secreta, al�m de quando quebrar o bloco a restri��o � desabilitada naquele ponto
          {
              if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                x--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
              else
              {
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==14 && y==7)) //Se estiver em cima da parede 1
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
           if ((parede2 == 1) && (x==14 && y==31)) //Se estiver em cima da parede 2
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede3 == 1) && (x==47 && y==7)) //Se estiver em cima da parede 3
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x > lim_x_right)
            x = lim_x_right;
        }

      else if(KEY == 5)
      {
      while (d<3)
        {
            if (seta == 4) //Direita

            {
                if(((((y==7) && (x==13)) && (parede1 == 0)) || (((y==7) && (x==12)) && (parede1 == 0))) || (((y==7) && (x==11)) && (parede1 == 0))) //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
            if((((((y==31) && (x==13)) && (parede2 == 0))|| ((y==31) && (x==12)) && (parede2 == 0)) || ((y==31) && (x==11)) && (parede2 == 0)) || ((y==31) && (x==16)) && (parede2 == 0))                  //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
             if(((y==7) && (x==46)) && (parede3 == 0)) //Posi��es que vai quebrar a parede e pontuar
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

                if (matriz_ptr[y-desl_y + 1][x-desl_x + d + 2] == 178)
              {
                break;
              }
           gotoxy(x+d+1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x+d+1, y);
           printf("%c", 255);
           d++;
            }
            if (seta == 2 ) //baixo
            {
                if (matriz_ptr[y-desl_y + 2 + d][x-desl_x + 1] == 178)
              {
                break;
              }
           gotoxy(x, y+d+1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y+d+1);
           printf("%c", 255);
           d++;
            }

            if (seta == 3 )//esquerda
            {
               if(((((y==7) && (x==15)) && (parede1 == 0))|| (((y==7) && (x==16)) && (parede1 == 0))) || (((y==7) && (x==17)) && (parede1 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede4 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x - d ] == 178)
              {
                break;
              }
           gotoxy(x-d-1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x-d-1, y);
           printf("%c", 255);
           d++;
            }

            if (seta == 1 )//Cima
            {
                if (matriz_ptr[y-desl_y - d][x-desl_x +1 ] == 178)
              {
                break;
              }
           gotoxy(x, y-d-1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y - d - 1);
           printf("%c", 255);
           d++;
            }
        }
      d=0;
      }
      else if(KEY == 7)
        printf("Tab esquerdo");
      else if(KEY == 8)
        printf("Tab direito");
      else if(KEY == 6)
      {

      }
      else if (x == 51 && y ==7)
     {
         clrscr();
         break;
     }

     //********************************************
     //          Posi��o do personagem
     //********************************************
            gotoxy(x,y); // cursor
            printf("%c",207);
     //*******************************************

    }while(1);

    free(matriz_ptr);
    //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**********************************                                                TELA 5                                               ***********************************
   //**********************************                                                TELA 5                                               ***********************************
   //**********************************                                                TELA 5                                               ***********************************
   //**********************************                                                TELA 5                                               ***********************************
   //**********************************                                                TELA 5                                               ***********************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************
   //**************************************************************************************************************************************************************************

    parede  = 0;
    parede1 = 0;
    parede2 = 0;
    parede3 = 0;
    parede4 = 0;
    parede5 = 0;
    parede6 = 0;

    #define lim_x_left  2
    #define lim_x_right 55
    #define lim_y_top   2
    #define lim_y_down  45

    #define desl_x      7
    #define desl_y      7

    #define posx_inicial 6
    #define posy_inicial 6

    textcolor(4);
    gotoxy(60,15);
    printf("******************************************************");
    gotoxy(60,16);
    printf("     ENCONTRE A PASSAGEM PARA O FINAL DO LABIRINTO!");
    gotoxy(60,17);
    printf("    TENTE OBTER O MENOR NUMERO DE PONTOS POSSIVEIS!!");
    gotoxy(60,18);
    printf("******************************************************");;
    gotoxy(60, 20);
    printf("                      QUINTA FASE");
    gotoxy(90, 5);
    printf(" ");

   //*****************************  PLACAR  ***************************************
    //******************************************************************************

    //Leitura do Placar
    gotoxy(60, 20);
    placar = fopen("Estrutura.txt","r");

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);


    //L�gica do Placar
    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }
    //Printf do Placar
    printf("\t\t\t\t\t\t\t\t\t\t Placar Atual\n");
    printf("\t\t\t\t\t\t\t\t ------------------------------------------\n");

    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t\t\t\t   %s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }

    //*****************************  PLACAR  ***************************************
    //******************************************************************************

    matriz(5);
    textcolor(15);

    //****************************************************
    //          posi��o inicial do personagem
    //****************************************************
    x = desl_x;
    y = desl_y;
    //****************************************************
    gotoxy(80,11);
    printf("\tX = %2d -- Y = %2d", x ,y);
    gotoxy(x,y); // cursor
    printf("%c",207);
    do
    {
      gotoxy(80,11);
      printf("\tX = %2d -- Y = %2d", x ,y);
      KEY = tecla();

      gotoxy(89,9); // posi��o do texto informativo de qual seta foi usada
      printf("                         ");
      gotoxy(89,9);
      if(KEY == 1)
      {
          seta =  1;
          printf("Seta para cima");
          y--;
          gotoxy(x, y+1);
          printf("%c",255);
          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((x!=9 || y!=9))  // Passagem secreta ocorre quando x == 34 e y ==9;
          {
             if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17); // texto informativo s� para saber se encntrou uma barreira
                y++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont); //Contador de Pontos
              }
             else //Contador de Pontos
                {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
                }
          }

          if((x==9 && y==9)) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y < lim_y_top)
            y = lim_y_top;
      }
      else if(KEY == 2)
      {
          printf("Seta para baixo");
          y++;
          gotoxy(x, y-1);
          printf("%c",255);
          seta = 2;
          //********************************************
          //   Restri��es de passagem
          //*******************************************

          if ((x!=9 || y!=9))   //Se n�o for parede secreta
          {
           if(((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178)) || (matriz_ptr[y-desl_y +1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                y--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
            else
            {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
            }
          }
          if  (x==9 && y==9) // Se for parede secreta
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
              if (parede == 0)
              {
                  gotoxy(90,7);
                  printf("Pontuacao = %d ", cont - 5);
                  cont -= 5;
                  parede++;
              }
          }
          //*********************************************
          if(y > lim_y_down)
            y = lim_y_down;
      }

      else if(KEY == 3)
        {
          printf("Seta para esquerda");
          x--;
          gotoxy(x+1, y);
          printf("%c",255);
          seta = 3;

          //********************************************
          //   Restri��es de passagem
          //********************************************
          if ((((x != 8 || y != 13) || (parede1 == 0)) && ((((x != 10 || y != 8)) || (parede2 == 0))))  && ((((x != 32 || y != 16)) || (parede3 == 0))))
          {
          if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) ||  (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {

                gotoxy(60,17);
                x++;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
          else
              {
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==8 && y==13))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede2 == 1) && (x==10 && y==8))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }

          if ((parede3 == 1) && (x==32 && y==16))
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if (x==6 && y ==32)
          {
              y = posy_inicial+1;
              x = posy_inicial+1;

          }
          //*********************************************
          if(x < lim_x_left)
            x = lim_x_left;
        }
      else if(KEY == 4)
        {
           printf("Seta para direita");
           x++;
           gotoxy(x-1, y);
           printf("%c",255);
           seta = 4;

           //********************************************
          //   Restri��es de passagem
          //********************************************

          if (((((x != 8 || y != 13)) || (parede1 == 0)) && ((((x != 10|| y != 8)) || (parede2 == 0)))) && ((((x != 32 || y != 16)) || (parede3 == 0))))     //   Restri��es de passagem ocorrem em todas as coordenadas menos na passagem secreta, al�m de quando quebrar o bloco a restri��o � desabilitada naquele ponto
          {
              if((matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 178) || (matriz_ptr[y-desl_y + 1][x-desl_x + 1] == 254))
              {
                gotoxy(60,17);
                x--;
                gotoxy(90,7);
                printf("Pontuacao = %d ", cont);
              }
              else
              {
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont+1);
                cont++;
              }
          }
          if ((parede1 == 1) && (x==8 && y==13)) //Se estiver em cima da parede 1
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
           if ((parede2 == 1) && (x==10 && y==8)) //Se estiver em cima da parede 2
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          if ((parede3 == 1) && (x==32 && y==16)) //Se estiver em cima da parede 3
          {
              gotoxy(90,7);
              printf("Pontuacao = %d ", cont+1);
              cont++;
          }
          //*********************************************
          if(x > lim_x_right)
            x = lim_x_right;
        }

      else if(KEY == 5)
      {
      while (d<3)
        {
            if (seta == 4) //Direita

            {
                if(((((y==13) && (x==7)) && (parede1 == 0)))) //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
            if(((y==8) && (x==9)) && (parede2 == 0))                 //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
             if(((((y==16) && (x==31)) && (parede3 == 0)) || ((y==16) && (x==30)) && (parede3 == 0)) || ((y==16) && (x==29)) && (parede3 == 0))//Posi��es que vai quebrar a parede e pontuar
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

                if (matriz_ptr[y-desl_y + 1][x-desl_x + d + 2] == 178)
              {
                break;
              }
           gotoxy(x+d+1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x+d+1, y);
           printf("%c", 255);
           d++;
            }
            if (seta == 2 ) //baixo
            {
                if (matriz_ptr[y-desl_y + 2 + d][x-desl_x + 1] == 178)
              {
                break;
              }
           gotoxy(x, y+d+1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y+d+1);
           printf("%c", 255);
           d++;
            }

            if (seta == 3 )//esquerda
            {
               if(((((y==7) && (x==15)) && (parede1 == 0))|| (((y==7) && (x==16)) && (parede1 == 0))) || (((y==7) && (x==17)) && (parede1 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede1 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

            if(((((y==8) && (x==12)) && (parede2 == 0))|| (((y==8) && (x==11)) && (parede2 == 0))))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede2 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }

            if(((((y==16) && (x==36)) && (parede3 == 0))|| (((y==16) && (x==34)) && (parede3 == 0))) || (((y==16) && (x==33)) && (parede3 == 0)))  //Posi��es que vai quebrar a parede e pontuar
            {
                parede3 = 1;
                gotoxy(90, 7);
                printf("Pontuacao = %d ", cont-5);
                cont-=5;
            }
                if (matriz_ptr[y-desl_y + 1][x-desl_x - d ] == 178)
              {
                break;
              }
           gotoxy(x-d-1, y);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x-d-1, y);
           printf("%c", 255);
           d++;
            }

            if (seta == 1 )//Cima
            {
                if (matriz_ptr[y-desl_y - d][x-desl_x +1 ] == 178)
              {
                break;
              }
           gotoxy(x, y-d-1);
           printf("%c", 250);
           Sleep(20);
           gotoxy(x, y - d - 1);
           printf("%c", 255);
           d++;
            }
        }
      d=0;
      }
      else if(KEY == 7)
        printf("Tab esquerdo");
      else if(KEY == 8)
        printf("Tab direito");
      else if(KEY == 6)
      {

      }
      else if (x == 55 && y ==8)
     {
         clrscr();
         break;
     }

     //********************************************
     //          Posi��o do personagem
     //********************************************
            gotoxy(x,y); // cursor
            printf("%c",207);
     //*******************************************

    }while(5);
    x = 0;
    y = 0;
    textcolor(2);
    gotoxy(50, 5);
    textcolor(2);
    printf("\n\n\n\n");
    printf("\n\t\t\t\t\t\t****************************");
    printf("\n\t\t\t\t\t\t                            ");
    printf("\n\t\t\t\t\t\t");
    printf("\n\t\t\t\t\t\t        FIM DE JOGO        ");
    printf("\n\t\t\t\t\t\t       PONTUACAO: %d      ", cont);
    printf("\n\t\t\t\t\t\t                      ");
    printf("\n\t\t\t\t\t\t                     ");
    printf("\n \t\t\t\t\t\t                    ");
    printf("\n\t\t\t\t\t\t****************************");
    printf("\n\n\n\n");
    gotoxy(50, 20);

    printf("Digite o nome: ");
    gets(lista[0].jogador);
    lista[0].pontuacao = cont;
    fflush(stdin);

    // Cola a estrutura no txt
    placar = fopen("Estrutura.txt","a");
    fprintf(placar,"%s -  Pontuacao: %d\n",lista[0].jogador, lista[0].pontuacao);
    fclose(placar);


    placar = fopen("Estrutura.txt","r");

    // Passa todo o txt para a estrutura

    for (k = 0; k < 100; k++)
    {
        fscanf(placar,"%[^\-] -  Pontuacao: %d\n",&lista[k].jogador,&lista[k].pontuacao);
    }
    printf("\n\n\n");
    fclose(placar);

    // L�gica da estrutura


    for (k = 0; k < 100; k++)
    {

        for (j = 0; j < 100; j++)
        {
            if ((lista[k].pontuacao < lista[j].pontuacao) && (lista[k].pontuacao != NULL))
            {
                maior = lista[k].pontuacao;
                aux = ptr[k];

                lista[k].pontuacao = lista[j].pontuacao;
                ptr[k] = ptr[j];

                lista[j].pontuacao = maior;
                ptr[j] = aux;
            }
        }
    }
    printf("\t\t\t\t\t\t\tPlacar\n");
    printf("\t\t------------------------------------------------------------------------------------------");
    printf("\n");


    // Printa os valores da estrutura
    for (k = 0; k < 6; k++)
    {
            if (lista[k].pontuacao != NULL)
            printf("\t\t\t\t\t\t%s -  Pontuacao: %d\n",lista[k].jogador, lista[k].pontuacao);
    }
    fclose(placar);

    return 0;
}

