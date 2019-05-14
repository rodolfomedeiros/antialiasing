#include <GL/gl.h>
#include <GL/glut.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

#define PI 3.14159265

struct PIXEL{
  int x;
  int y;
  unsigned char value;
  unsigned char l;
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

void antiAliasing(
  int width,
  int height,
  int anguloRotacao,
  int limiar,
  unsigned char * dataRed,
  unsigned char * dataGreen,
  unsigned char * dataBlue,
  PIXEL * dataResult[],
  char * passaBaixa
);

int buscarPosicao(int i, int width, int height, int x, int y);

int obterIntensidade(
  unsigned char * dataRed,
  unsigned char * dataGreen,
  unsigned char * dataBlue,
  int pos
);

unsigned char somarMatriz(char * matriz, unsigned char tam);

void save(int x, int y, int t, PIXEL * r[]);

void fourier();