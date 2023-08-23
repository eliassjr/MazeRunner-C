#ifndef LE_TECLAS_H_INCLUDED
#define LE_TECLAS_H_INCLUDED
//**************************************************
// Esta biblioteca é para uso em sala de aula e em
// projetos. Qualquer alteração poderá ser feita.
// O codigo foi desenvolvido neste formato e não
// há garantias sobre o seu uso.
//
// Prof. Nivaldo T. Schiefler Jr.  Dr.sc
// IFSC - Instituto Federal de Santa Catarina
//*******************************************************************


//*******************************************************************
char tecla(void)
{
  char key;

  key = getch();
  //************************************************************
  if(key == 72)        // seta para cima // arrow up
     return 1;
  else if(key == 80)   // seta para baixo // arrow down
     return 2;
  else if(key == 75)   // seta para esquerda // arrow left
     return 3;
  else if(key == 77)   // seta para direita // arrow right
     return 4;
  else if(key == 32)   // barra de espaço // space bar
     return 5;
  else if(key == 27)   // ESC
     return 6;
  else if(key == 9)    // TAB ->
     return 7;
  else if(key == 8)    // TAB <-
     return 8;
  else                 // Opção não existente
     return 0;
  //**************************************************************
}


#endif // LE_TECLAS_H_INCLUDED
