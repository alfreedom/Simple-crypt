
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>

//PROTOTIPOS DE FUNCIONES DEL RATON
int mtest(void);
void mver(void);
void mocultar(void);
int mposx(int modo);
int mposy(int modo);
void msituar(int modo, int x, int y);
int mclick(void);
void mlimitar(int modo, int x1,int y1,int x2, int y2);

// VARIABLE DE LOS REGISTROS DEL RATON
union REGS reg;


//VERIFICAR PRESENCIA DEL RATON
int mtest(void)
{
 reg.x.ax=0x0;
 int86(0x33,&reg,&reg);
 if(reg.x.ax>0)
       return reg.x.bx;
  else
       return 0;
}

//MOSTRAR PUNTERO DEL RATON
void mver(void)
{
  reg.x.ax=0x1;
  int86(0x33,&reg,&reg);
}

//OCULTAR PUNTERO DEL RATON
void mocultar(void)
{
 reg.x.ax=0x2;
 int86(0x33,&reg,&reg);
}

//COORDENADA 'X' DEL PUNTERO
int mposx(int modo)
{
  reg.x.ax=0x3;
  int86(0x33,&reg,&reg);
  return reg.x.cx/modo;
}


//COORDENADA 'Y' DEL PUNTERO
int mposy(int modo)
{
  reg.x.ax=0x3;
  int86(0x33,&reg,&reg);
  return reg.x.dx/modo;
}

//POSICIONAR EL PUNTERO
void msituar(int modo, int x, int y)
{
 reg.x.ax=0x4;
 reg.x.cx=x*modo;
 reg.x.dx=y*modo;
 int86(0x33,&reg,&reg);
}

//VERIFICAR SI EXISTE BOTON PRESIONADO
int mclick(void)
{
  int r=0;
  reg.x.ax=0x5;
  reg.x.bx=0;
  int86(0x33,&reg,&reg);
  if((reg.x.ax)&1)
       r=1;
  else
    if((reg.x.ax>>1)&1)
        r=2;
  return r;
}

//LIMITAR AREA DE DESPLAZAMIENTO DEL RATON
void mlimitar(int modo,int x1,int y1, int x2, int y2)
{
 reg.x.ax=0x7;
 reg.x.cx=x1*modo;
 reg.x.dx=x2*modo;
 int86(0x33,&reg,&reg);
 reg.x.ax=0x8;
 reg.x.cx=y1*modo;
 reg.x.dx=y2*modo;
 int86(0x33,&reg,&reg);
}
