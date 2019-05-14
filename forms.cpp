#include "antialiasing.h"
#include "forms.h"

void cena_quads(int width, int height){
    glPushMatrix();
        glTranslated(0,0,4);
        glBegin(GL_QUADS);
            glColor3ub(255, 255, 0);
            glVertex2i(0, height);
            glColor3ub(255, 0, 255);
            glVertex2i(width, height);
            glColor3ub(0, 255, 255);
            glVertex2i(width, 0);
            glColor3ub(255, 255, 255);
            glVertex2i(0, 0);
        glEnd();
    glPopMatrix();
}

void cena_1(int width, int height){
    glColor3ub(255, 0, 0);

    glBegin(GL_LINE_LOOP);
      glVertex2i(0, 0.5*height);
      glVertex2i(0.5*width, height);
      glColor3ub(100, 0, 0);
      glVertex2i(width, 0.5*height);
      glVertex2i(0.5*width, 0);
    glEnd();

    glColor3ub(0, 255, 0);

    glBegin(GL_POLYGON);
      glVertex2i(width/4, height/2);
      glVertex2i(width/2-width/8, height-height/4);
      glVertex2i(width/2+width/8, height-height/4);
      glColor3ub(0, 150, 0);
      glVertex2i(width/2+width/4, height/2);
      glVertex2i(width/2+width/8, height/4);
      glVertex2i(width/2-width/8, height/4);
    glEnd();

    glColor3f(0.0, 0.0, 1.0f);

    glBegin(GL_TRIANGLES);
      glVertex2i(width/4, height-1);
      glVertex2i(width/10, height/2+height/6);
      glColor3ub(0, 0, 100);
      glVertex2i(width/2, height/2+height/6);
      // //drawing a new triangle
      glVertex2i(width/2+width/4, 1);
      glVertex2i(width/2+width/10, height/2-height/6);
      glColor3ub(0, 140, 100);
      glVertex2i(width/2+width/2, height/2-height/6);
    glEnd();
}

void cena_triangulo_escada(int width, int height){

    glBegin(GL_TRIANGLES);
      //1
      glColor3ub(255, 0, 0);
      glVertex2i(750, 598);
      glColor3ub(0, 255, 0);
      glVertex2i(250, 510);
      glColor3ub(0, 0, 255);
      glVertex2i(750, 510);
      //2
      glColor3ub(255, 0, 0);
      glVertex2i(750, 509);
      glColor3ub(0, 255, 0);
      glVertex2i(250, 327);
      glColor3ub(0, 0, 255);
      glVertex2i(750, 327);
      //3
      glColor3ub(255, 0, 0);
      glVertex2i(750, 326);
      glColor3ub(0, 255, 0);
      glVertex2i(250, 37);
      glColor3ub(0, 0, 255);
      glVertex2i(750, 37);
      
    glEnd();
}

void cena_solid_sphere(int centerX, int centerY){
    
    glPushMatrix();
        glColor3ub(0, 0, 255);
        glTranslated(centerX, centerY, -240);
        glutSolidSphere(350, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0, 255, 0);
        glTranslated(centerX, centerY, -120);
        glutSolidSphere(200, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 0, 0);
        glTranslated(centerX, centerY, -30);
        glutSolidSphere(50, 30, 30);
    glPopMatrix();

}

void cene_quads(float w, float h){
    w *= 100;
    h *= 100;
    glPushMatrix();
        glTranslated(0,0,-100);
        glBegin(GL_QUADS);
            glColor3ub(255, 0, 0);
            glVertex2f(-w, -h);
            glColor3ub(0, 0, 255);
            glVertex2f(w, h);
            glColor3ub(0, 255, 0);
            glVertex2f(-w, h);
            glColor3ub(255, 255, 255);
            glVertex2f(w, -h);
        glEnd();
    glPopMatrix();
}

void cene_quads2(float w, float h){
    w *= 100;
    h *= 100;
    glPushMatrix();
        glTranslated(0,0,-100);
        glBegin(GL_QUADS);
            glColor3ub(255, 255, 0);
            glVertex2f(w, -h);
            glColor3ub(0, 255, 255);
            glVertex2f(w, h);
            glColor3ub(255, 0, 255);
            glVertex2f(-w, -h);
            glColor3ub(255, 255, 255);
            glVertex2f(w, h);
        glEnd();
    glPopMatrix();
}

void cena_sphere(){
    // glPushMatrix();
    //     glColor3d(0, 0, 1);
    //     glTranslated(0,0,-20);
    //     glutSolidSphere(14, 50, 30);
    // glPopMatrix();

    glPushMatrix();
        glColor3d(0, 0.5, 0.9);
        glTranslated(-1.6,-0.7,-6);
        glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // glPushMatrix();
    //     glColor3d(1, 0, 0);
    //     glTranslated(0, 0, -6);
    //     glutSolidSphere(2, 50, 30);
    // glPopMatrix();
}

void cena_cube(){
    glPushMatrix();
        glColor3d(0.5,1,0.3);
        glTranslated(-2.5,-5,-13);
        glRotated(30, 5.0, 2, 1.0);
        glutSolidCube(6);
    glPopMatrix();
    // glPushMatrix();
    //     glColor3d(0.5,1,0.3);
    //     glTranslated(-3,1.5,-6);
    //     glRotated(30, 5.0, 2, 1.0);
    //     glutWireCube(2);
    // glPopMatrix(); 
}

void cena_torus(){
    glColor3d(1,0,0);
    glPushMatrix();
        glTranslated(-6,2,-6);
        glRotated(-10, 1.0, 0.0, 0.0);
        glutSolidTorus(0.6, 1.2, 20, 50);
    glPopMatrix(); 

    // glPushMatrix();
    //     glTranslated(0.0,-1.2,-6);
    //     glutWireTorus(0.4, 0.8, 10, 20);
    // glPopMatrix();
}

void cena_cone(){
    
    glPushMatrix();
        glColor3d(1,0.5,0.9);
        glTranslated(-1.6,0.4,-5);
        glRotated(-45, 20, 3, 0);
        glutSolidCone(1, 2, 50, 20);
    glPopMatrix(); 

    // glPushMatrix();
    //     glTranslated(0.0,-1.2,-6);
    //     glutWireTorus(0.4, 0.8, 10, 20);
    // glPopMatrix();
}

void cene_teapot(){
    glPushMatrix();
        glColor3d(1,0,1);
        glTranslated(3,-1,-4);
        glRotated(-20, 0, 5, 0);
        glutSolidTeapot(1);
    glPopMatrix();
}

void cene_doca(){
    glPushMatrix();
        glColor3d(0.5,1,0.9);
        glTranslated(2,2,-6);
        glRotated(-20, 0, 5, 0);
        glutSolidDodecahedron();
    glPopMatrix();
}

void cene_octa(){
    glPushMatrix();
        glColor3d(1,1,0.5);
        glTranslated(-4,-2,-4);
        glRotated(-20, 0, 5, 0);
        glutSolidOctahedron();
    glPopMatrix();
}

