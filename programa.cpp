#include "antialiasing.h"
#include "forms.h"

using namespace std;

int widthTela = 1000, heightTela = 600;

void display(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, widthTela, 0, heightTela, 1, -1000);

    glClear(GL_COLOR_BUFFER_BIT);
    
    cena_quads(widthTela, heightTela);
    cena_1(widthTela, heightTela);
    //cena_triangulo_escada(widthTela, heightTela);
    //cena_solid_sphere(widthTela/2, heightTela/2);
    
    int t = widthTela * heightTela;

    unsigned char * dataRed;
    unsigned char * dataGreen;
    unsigned char * dataBlue;

    dataRed = new unsigned char[t];
    dataGreen = new unsigned char[t];
    dataBlue = new unsigned char[t];

    glReadPixels(0, 0, widthTela, heightTela, GL_BLUE, GL_UNSIGNED_BYTE, dataBlue);
    glReadPixels(0, 0, widthTela, heightTela, GL_RED, GL_UNSIGNED_BYTE, dataRed);
    glReadPixels(0, 0, widthTela, heightTela, GL_GREEN, GL_UNSIGNED_BYTE, dataGreen);
  
    char PASSA_BAIXA_MEDIA3X3[] = {1,1,1,1,1,1,1,1,1};
    //char PASSA_BAIXA_MEDIA3X32[] = {1,4,1,4,8,4,1,4,1};
    PIXEL * *result = new PIXEL*[t];

    for(int i = widthTela + 1; i < t - widthTela - 1; i++){
      result[i] = new PIXEL;

      result[i]->x = i % widthTela;
      result[i]->y = i / widthTela;
      result[i]->l = 0;
      result[i]->r = dataRed[i];
      result[i]->g = dataGreen[i];
      result[i]->b = dataBlue[i];
    }

    antiAliasing(
      widthTela,
      heightTela,
      180,
      10,
      dataRed,
      dataGreen,
      dataBlue,
      result,
      PASSA_BAIXA_MEDIA3X3
    );

    // antiAliasing_semrotacao(
    //   widthTela,
    //   heightTela,
    //   5,
    //   5,
    //   dataRed,
    //   dataGreen,
    //   dataBlue,
    //   result,
    //   matrizPassaBaixa
    // );

    // for(int i = widthTela + 1; i < t - widthTela - 1; i++){
    //     glColor3ub(result[i]->r, result[i]->g,result[i]->b);

    //     glBegin(GL_POINTS);
    //       glVertex2i(result[i]->x, result[i]->y);
    //     glEnd();
    // }

    save(widthTela, heightTela, t, result);

    glutSwapBuffers();
}

void init(){
  glClearColor(.0f, .0f, .0f, 0.0);
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(widthTela, heightTela); 
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Antialiasing");
  init();
  glutDisplayFunc(display); 
  glutMainLoop();
}