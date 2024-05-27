/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include "./usosmultiples.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14156

void inicializar_usosmultiples(void) {
    glClearColor(0.0, 0.44, 0.73, 1.0); 
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 700, 0, 700); // 700x700
}

#define WIDTH 640
#define HEIGHT 480

typedef struct {
    int x, y;
} Point;

int numeroVertices = 4;
int numeroVertices2 = 6;

//LA SUMATORIA DEBE SER 660 PARA QUE SEA SIMETRICO
Point verticesVentana1[] = {{454, 450}, {590, 450}, {590, 415}, {454, 415}};
Point verticesVentana2[] = {{454, 388}, {590, 388}, {590, 360}, {454, 360}};
Point verticesVentana3[] = {{454, 330}, {590, 330}, {590, 300}, {454, 300}};

Point verticesVentanaReflejada1[] = {{206, 450}, {70, 450}, {70, 415}, {206, 415}};
Point verticesVentanaReflejada2[] = {{206, 388}, {70, 388}, {70, 360}, {206, 360}};
Point verticesVentanaReflejada3[] = {{206, 330}, {70, 330}, {70, 300}, {206, 300}};

Point verticesPared[] = {{454, 468}, {600, 470}, {600, 280}, {454, 280}};
Point verticesParedReflejada[] = {{206, 468}, {60, 470}, {60, 280}, {206, 280}};

Point verticesCentro[] = {{330, 440}, {330,480}, {454, 480}, {454, 280}, {380, 280}, {380, 440}};
Point verticesCentroReflejado[] = {{330, 440}, {330,480}, {206, 480}, {206, 280}, {280, 280}, {280, 440}};

Point verticesEntrada[] = {{280, 440}, {380, 440}, {380, 280}, {280, 280}};

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void DibujarPoligono(Point *vertices, int numVertices) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glFlush();
}

void LlenadoInundacion(Point *vertices, int numeroVertices) {
    int i, j, k;
    int x, y, temp;
    int minimoY = vertices[0].y, maximoY = vertices[0].y;

    for (i = 1; i < numeroVertices; i++) {
        if (vertices[i].y < minimoY)
            minimoY = vertices[i].y;
        if (vertices[i].y > maximoY)
            maximoY = vertices[i].y;
    }

    for (y = minimoY; y <= maximoY; y++) {
        int intersections[numeroVertices];
        int numIntersections = 0;

        for (i = 0; i < numeroVertices; i++) {
            int next = (i + 1) % numeroVertices;
            if ((vertices[i].y <= y && vertices[next].y > y) ||
                (vertices[i].y > y && vertices[next].y <= y)) {
                int intersectX = vertices[i].x + (y - vertices[i].y) * (vertices[next].x - vertices[i].x) / (vertices[next].y - vertices[i].y);
                intersections[numIntersections++] = intersectX;
            }
        }

        for (j = 0; j < numIntersections - 1; j++) {
            for (k = j + 1; k < numIntersections; k++) {
                if (intersections[j] > intersections[k]) {
                    temp = intersections[j];
                    intersections[j] = intersections[k];
                    intersections[k] = temp;
                }
            }
        }

        for (i = 0; i < numIntersections; i += 2) {
            for (x = intersections[i]; x <= intersections[i + 1]; x++) {
                setPixel(x, y);
            }
        }
    }
}

void Elipse(float radioX, float radioY, float centroX, float centroY, float limiteAngulo) {
    if (radioX > 0 && radioY > 0) {
        if (limiteAngulo > 360) {
            exit(EXIT_FAILURE);
        }

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, .50, 0.0); 
        glVertex2f(centroX, centroY);

        for (float angle = 0; angle <= limiteAngulo; angle++) {
            float radian = angle * (PI / 180); 
            
            float x = centroX + radioX * cos(radian); 
            float y = centroY + radioY * sin(radian); 

            glVertex2f(x, y);
        }
        
        glVertex2f(centroX + radioX * cos(0), centroY + radioY * sin(0)); 
        glEnd();
    } else {
        exit(EXIT_FAILURE);
    }
}

void Circulo(float radio, float centroX, float centroY, float limiteAngulo) {
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    
    if (radio > 0) {
        if (limiteAngulo  > 360) {
            exit(EXIT_FAILURE);
        }

        for (float angulo = 0; angulo <= limiteAngulo ; angulo++) {
            float radian = angulo * (PI / 180);
            
            float x = radio * cos(radian);
            float y = radio * sin(radian);
            
            
            
            glVertex2f(centroX + x, centroY + y);
            glVertex2f(centroX + x, centroY - y);
            glVertex2f(centroX - x, centroY + y);
            glVertex2f(centroX - x, centroY - y);
            glVertex2f(centroX + y, centroY + x);
            glVertex2f(centroX + y, centroY - x);
            glVertex2f(centroX - y, centroY + x);
            glVertex2f(centroX - y, centroY - x);

        }
    }else{
        exit(EXIT_FAILURE);
    }
    
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0); 
    glPointSize(3.0); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

void PuntoPDT(int size, float x1, float y1, float x2, float y2) {

    if (x1 == x2) {
        int startY = (y1 < y2) ? y1 : y2;
        int endY = (y1 > y2) ? y1 : y2;
        for (int j = startY; j <= endY; j++) {
            glPointSize(size);
            glBegin(GL_POINTS);
            glVertex2f(x1, j);
            glEnd();
        }
    }

    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - (m * x1);

    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    glPointSize(size);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        float x = x1 + i * xIncrement;
        float y = m * x + b;
        glVertex2f(x, y);
    }
    glEnd();
}


void dibujar_usosmultiples(){
   glClear(GL_COLOR_BUFFER_BIT);
   
    //PAREDES
    glColor3f(0.0, 0.0, 0.0); // Se dibuja el poligono
    DibujarPoligono(verticesPared, numeroVertices);

    glColor3f( 0.81, 0.81, 0.81); // Se rellena el poligono
    LlenadoInundacion(verticesPared, numeroVertices);
    
    glColor3f(0.0, 0.0, 0.0); 
    DibujarPoligono(verticesParedReflejada, numeroVertices);

    glColor3f( 0.81, 0.81, 0.81); 
    LlenadoInundacion(verticesParedReflejada, numeroVertices);
    
    //CENTRO
    glColor3f(0.77, 0.34, 0.26); 
    DibujarPoligono(verticesCentroReflejado, numeroVertices2);

    glColor3f(0.77, 0.34, 0.26); 
    LlenadoInundacion(verticesCentroReflejado, numeroVertices2);
    
    glColor3f(0.77, 0.34, 0.26); 
    DibujarPoligono(verticesCentro, numeroVertices2);

    glColor3f(0.77, 0.34, 0.26); 
    LlenadoInundacion(verticesCentro, numeroVertices2);
    
    glColor3f(0.77, 0.34, 0.26); 
    DibujarPoligono(verticesEntrada, numeroVertices);

    glColor3f(0.74, 0.65, 0.52); 
    LlenadoInundacion(verticesEntrada, numeroVertices);
    
    //VENTANAL 1
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentana1, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentana1, numeroVertices);
    
    //VENTANA 2
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentana2, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentana2, numeroVertices);
    
    //VENTANA 3
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentana3, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentana3, numeroVertices);
    
    //VENTANA REFLEJADA 1
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentanaReflejada1, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentanaReflejada1, numeroVertices);
    
    //VENTANA REFLEJADA 2
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentanaReflejada2, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentanaReflejada2, numeroVertices);
    
    //VENTANA REFLEJADA 3
    glColor3f(0.31, 0.20, 0.16); 
    DibujarPoligono(verticesVentanaReflejada3, numeroVertices);

    glColor3f(0.31, 0.20, 0.16); 
    LlenadoInundacion(verticesVentanaReflejada3, numeroVertices);
    
//  PILAR 
    glColor3f(0.77, 0.34, 0.26);    
    PuntoPDT(10, 545, 448, 545, 280);
    
//  ESTRUCTURA HORIZONTAL DE LA VENTANA
    glColor3f(0.77, 0.34, 0.26);
    PuntoPDT(10, 450, 394, 588, 394);
    
    glColor3f(0.77, 0.34, 0.26);
    PuntoPDT(10, 450, 336, 588, 336);
    
//  PILAR REFLEJADO
    glColor3f(0.77, 0.34, 0.26);    
    PuntoPDT(10, 115, 448, 115, 280);
    
//  ESTRUCTURA HORIZONTAL DE LA VENTANA REFLEJADA  
    glColor3f(0.77, 0.34, 0.26);
    PuntoPDT(10, 210, 394, 72, 394);
    
    glColor3f(0.77, 0.34, 0.26);
    PuntoPDT(10, 210, 336, 72, 336);
    
//  BARROTES DE LAS VENTANAS 1
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 464, 446, 464, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 479, 446, 479, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 493, 446, 493, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 507, 446, 507, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 521, 446, 521, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 536, 446, 536, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 559, 446, 559, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 573, 446, 573, 420);
    
//  BARROTES DE LAS VENTANAS 2
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 464, 386, 464, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 479, 386, 479, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 493, 386, 493, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 507, 386, 507, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 521, 386, 521, 362);
    
     glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 536, 386, 536, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 559, 386, 559, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 573, 386, 573, 362);
    
//  BARROTES DE LAS VENTANAS 3
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 464, 328, 464, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 479, 328, 479, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 493, 328, 493, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 507, 328, 507, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 521, 328, 521, 304);
    
     glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 536, 328, 536, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 559, 328, 559, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 573, 328, 573, 304);
    
//  BARROTES DE LAS VENTANAS REFLEJADAS 1
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 196, 446, 196, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 181, 446, 181, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 167, 446, 167, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 153, 446, 153, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 139, 446, 139, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 124, 446, 124, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 101, 446, 101, 420);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 87, 446, 87, 420);
    
//  BARROTES DE LAS VENTANAS REFLEJADAS 2
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 196, 386, 196, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 181, 386, 181, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 167, 386, 167, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 153, 386, 153, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 139, 386, 139, 362);
    
     glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 124, 386, 124, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 101, 386, 101, 362);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 87, 386, 87, 362);
    
//  BARROTES DE LAS VENTANAS REFLEJADAS 3
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 196, 328, 196, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 181, 328, 181, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 167, 328, 167, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 153, 328, 153, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 139, 328, 139, 304);
    
     glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 124, 328, 124, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 101, 328, 101, 304);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(5, 87, 328, 87, 304);
    
//  VENTANALES DE LA PARED ROJA
//  PRIMERA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 397, 435, 397, 400);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 418, 435, 418, 400);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 439, 435, 439, 400);
    
//  SEGUNDA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 397, 350, 397, 385);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 418, 350, 418, 385);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 439, 350, 439, 385);
    
//  TERCERA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 397, 300, 397, 335);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 418, 300, 418, 335);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 439, 300, 439, 335);
    
//  VENTANALES DE LA PARED ROJA REFLEJADA
//  PRIMERA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 263, 435, 263, 400);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 242, 435, 242, 400);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 221, 435, 221, 400);
    
//  SEGUNDA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 263, 350, 263, 385);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 242, 350, 242, 385);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 221, 350, 221, 385);
    
//  TERCERA FILA  
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 263, 300, 263, 335);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 242, 300, 242, 335);
    
    glColor3f(0.31, 0.20, 0.16);
    PuntoPDT(12, 221, 300, 221, 335);
    
//  VENTANAS CENTRO 1
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 435, 375, 435);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 435, 375, 390);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 390, 285, 390);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 390, 285, 435);
    
//  BARROTES  
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 300, 435, 300, 390);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 320, 435, 320, 390);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 340, 435, 340, 390);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 360, 435, 360, 390);
    
//  VENTANAS CENTRO 2
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 385, 375, 385);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 385, 375, 330);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 330, 285, 330);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 330, 285, 385);
    
//  BARROTES  
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 300, 385, 300, 330);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 320, 385, 320, 330);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 340, 385, 340, 330);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 360, 385, 360, 330);
    
//  MARCO
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 325, 375, 325);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 325, 375, 280);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 375, 280, 285, 280);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 285, 280, 285, 325);
    
//  PUERTA  
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 320, 310, 340, 310);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 340, 310, 340, 280);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 340, 280, 320, 280);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 320, 280, 320, 310);
    
    glColor3f(0.0, 0.0, 0.0);
    PuntoPDT(3, 330, 310, 330, 280);
    
    Elipse(150, 50, 300, 230, 360);
   
    Circulo(10, 552, 366, 360);
    Circulo(10, 108, 366, 360);
    
    
    glFlush();
       
}



const char* get_carnet(void){
    return "PG19065 y RL18003";
}