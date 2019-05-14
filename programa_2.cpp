#include "antialiasing.h"
#include "forms.h"

int widthTela = 1000;
int heightTela = 600;

float w;
float h;

static void resize(int width, int height){
    const float ar = (float) width / (float) height; 

    w = ar;
    h = 1.0f;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(107,1.25,1,1000);
    glFrustum(-ar, ar, -1.0, 1.0, 1, 100); 
    //glFrustum(0, widthTela, 0, widthTela, 1, 1000.0); 
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    //gluLookAt(0,0,1,0,0,0,0,1,0);
} 

static void display(void){ 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cene_quads(w, h);
    cene_quads2(w, h);
    cena_sphere();
    cena_cube();
    cena_torus();
    cena_cone();
    cene_teapot();
    cene_doca();
    cene_octa();

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
    PIXEL * *result = new PIXEL*[t];

    for(int i = widthTela + 1; i < t - widthTela - 1; i++){
        result[i] = new PIXEL;

        result[i]->x = i % widthTela;
        result[i]->y = i / widthTela;
        result[i]->r = dataRed[i];
        result[i]->g = dataGreen[i];
        result[i]->b = dataBlue[i];
    }

    antiAliasing(
      widthTela,
      heightTela,
      10,
      8,
      dataRed,
      dataGreen,
      dataBlue,
      result,
      PASSA_BAIXA_MEDIA3X3
    );

    // for(int i = widthTela + 1; i < t - widthTela - 1; i++){
    //     glColor3ub(result[i]->r, result[i]->g,result[i]->b);

    //     glBegin(GL_POINTS);
    //       glVertex2i(result[i]->x, result[i]->y);
    //     glEnd();
    // }

    save(widthTela, heightTela, t, result);

    glutSwapBuffers();
} 

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; 

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f }; 

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(widthTela,heightTela);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 

    glutCreateWindow("Torus"); 

    glutReshapeFunc(resize);
    glutDisplayFunc(display); 

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); 

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 

    glutMainLoop(); 

    return EXIT_SUCCESS;
}