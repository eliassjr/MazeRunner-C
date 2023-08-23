#ifndef MY_LIB_H_INCLUDED
#define MY_LIB_H_INCLUDED

#include <time.h>
#include <windows.h>

//*****************************************************************************
//          Rotina de tempo em milisegundos
//  ex: para dar um tempo de 1s colocar o valor 1000
//      delay(1000)
//*****************************************************************************
void delay(unsigned int mili_secs)
{
  clock_t tempo;
  tempo = mili_secs + clock();
  while (tempo > clock());
}
//*****************************************************************************
//                       Definição de cores
//*****************************************************************************
enum DOS_COLORS {
        BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
        LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
        LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };
//*****************************************************************************
//                       Posição do texto na tela
//*****************************************************************************
void gotoxy(int x, int y)
{
  HANDLE hOut;
  COORD Position;
  hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  Position.X = x;
  Position.Y = y;
  SetConsoleCursorPosition(hOut,Position);
}
//*****************************************************************************
//                       Cor do texto
//*****************************************************************************
void textcolor(int cor)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, cor);
}
//*****************************************************************************
//                       Cor do fundo de tela
//*****************************************************************************
void textbackground (int iColor)
{
  HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(hl, &bufferInfo);
  bufferInfo.wAttributes &= 0x000F;
  SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}
//*****************************************************************************
//                       Limpar a tela
//*****************************************************************************
void clrscr(void)
{
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '),
			       dwConSize, coordScreen, &cCharsWritten);

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                               dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}
//*****************************************************************************
//                      Desliga cursor
//*****************************************************************************
void cursor_off(void)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
//*****************************************************************************
//                      Liga cursor
//*****************************************************************************
void cursor_on(void)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
//*****************************************************************************
//
//*****************************************************************************




#endif // MY_LIB_H_INCLUDED
