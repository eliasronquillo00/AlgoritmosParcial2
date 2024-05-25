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

void inicializar_usosmultiples(void) {
    glClearColor(0.63, 0.65, 0.61, 1.0); // gray color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 700, 0, 700); // 700x700
}

// Tamaño de la ventana
#define WIDTH 640
#define HEIGHT 480

// Estructura para almacenar puntos
typedef struct {
    int x, y;
} Point;

// Número de vértices del polígono
int numVertices = 4;

// Vértices del polígono
                     //h           //i        //f           //g
Point vertices[] = {{188, 428}, {160, 300}, {620, 300}, {587, 432}};
Point vertices2[] = {{300, 440}, {457,442}, {468, 300}, {290, 300}};

// Función para dibujar un píxel
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Función para dibujar el polígono
void drawPolygon(Point *vertices, int numVertices) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glFlush();
}

// Función para rellenar el polígono utilizando Scan-Line Fill
void scanLineFill(Point *vertices, int numVertices) {
    int i, j, k;
    int x, y, temp;
    int minY = vertices[0].y, maxY = vertices[0].y;

    // Encontrar las coordenadas y mínima y máxima
    for (i = 1; i < numVertices; i++) {
        if (vertices[i].y < minY)
            minY = vertices[i].y;
        if (vertices[i].y > maxY)
            maxY = vertices[i].y;
    }

    // Scan-Line Fill
    for (y = minY; y <= maxY; y++) {
        int intersections[numVertices];
        int numIntersections = 0;

        // Encontrar las intersecciones con las aristas del polígono
        for (i = 0; i < numVertices; i++) {
            int next = (i + 1) % numVertices;
            if ((vertices[i].y <= y && vertices[next].y > y) ||
                (vertices[i].y > y && vertices[next].y <= y)) {
                int intersectX = vertices[i].x + (y - vertices[i].y) * (vertices[next].x - vertices[i].x) / (vertices[next].y - vertices[i].y);
                intersections[numIntersections++] = intersectX;
            }
        }

        // Ordenar las intersecciones
        for (j = 0; j < numIntersections - 1; j++) {
            for (k = j + 1; k < numIntersections; k++) {
                if (intersections[j] > intersections[k]) {
                    temp = intersections[j];
                    intersections[j] = intersections[k];
                    intersections[k] = temp;
                }
            }
        }

        // Dibujar píxeles entre pares de intersecciones
        for (i = 0; i < numIntersections; i += 2) {
            for (x = intersections[i]; x <= intersections[i + 1]; x++) {
                setPixel(x, y);
            }
        }
    }
}

// Función de visualización
/*
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Negro para el contorno del polígono
    drawPolygon(vertices, numVertices);

    glColor3f(1.0, 0.0, 0.0); // Rojo para el relleno del polígono
    scanLineFill(vertices, numVertices);
}
*/

// Función de inicialización
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fondo blanco
    glColor3f(0.0, 0.0, 0.0); // Color inicial de los puntos (negro)
    glPointSize(3.0); // Tamaño de los puntos
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

void EcuacionG(int size, float x1, float y1, float x2, float y2) {

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
   
    glColor3f(0.0, 0.0, 0.0); // Negro para el contorno del polígono
    drawPolygon(vertices, numVertices);

    glColor3f( 0.81, 0.81, 0.81); // Rojo para el relleno del polígono
    scanLineFill(vertices, numVertices);
    
    glColor3f(0.0, 0.0, 0.0); // Negro para el contorno del polígono
    drawPolygon(vertices2, numVertices);

    glColor3f(0.77, 0.34, 0.26); // Azul para el relleno del polígono
    scanLineFill(vertices2, numVertices);
    
//    glColor3f( 0, 1, 0);
//    EcuacionG(10,463,335,659,344);
//    glColor3f( 1, 0, 0);
//    EcuacionG(10,450,320,574,320);
//    glColor3f( 1, 0, 0);
//    EcuacionG(9,574,267,450,267);
/*
    Point vertices[] = {{25, 25}, {150, 25}, {150, 150}, {25, 150}};
    glColor3f(0.0, 0.0, 0.0); // Rojo para el relleno del polígono
    scanLineFill(vertices, numVertices);
*/
    glFlush();
       
}



const char* get_carnet(void){
    return "PG19065 y RL18003";
}