// Universidad Veracruzana - Ingeniería en Informática
// Policarpio Moran Michell Alexis - zS21002379
// Veracruz, Ver, MX. Octubre del 2024
// Sistema Solar 

/*Instrucciones para manipular el programa
-------------------------------------------
Controles del programa:
*Presiona 'q' o 'Q' para salir del programa.
*Presiona 'r' o 'R' para aumentar la rotación general en 5 grados.
*Presiona la barra espaciadora para activar o desactivar la animación.
*Utiliza las teclas 'W' o 'S' para mover la cámara hacia arriba o hacia abajo respectivamente.
*Utiliza las teclas 'A' o 'D' para mover la cámara hacia la izquierda o hacia la derecha respectivamente.
------------------------------------------- */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include <math.h>
#define NUM_ASTEROIDES_CINTURON 200 //cantidad de asteroides
#define NUM_ASTEROIDES_KUIPER 1200 //cantidad de asteoides de kuiper

// Variables globales para las posiciones y ángulos de los planetas
float mercurioAngOrb = 0.0, venusAngOrb = 0.0, tierraAngOrb = 0.0;
float marteAngOrb = 0.0, ceresAngOrb = 0.0, jupiterAngOrb = 0.0;
float saturnoAngOrb = 0.0, uranoAngOrb = 0.0, neptunoAngOrb = 0.0;
float plutonAngOrb = 0.0, lunaAngOrb = 0.0, europaAngOrb = 0.0;

float mercurioAngRot = 0.0, venusAngRot = 0.0, tierraAngRot = 0.0;
float marteAngRot = 0.0, ceresAngRot = 0.0, jupiterAngRot = 0.0;
float saturnoAngRot = 0.0, uranoAngRot = 0.0, neptunoAngRot = 0.0;
float plutonAngRot = 0.0, lunaAngRot = 0.0, europaAngRot = 0.0;
float haumeaAngOrb = 0.0;  
float haumeaAngRot = 0.0;  
float makemakeAngOrb = 0.0; 
float makemakeAngRot = 0.0; 

// variables para la posición de la cámara
float camX = 0.0;
float camY = 20.0;
float camZ = 50.0;
float velocidadCamara = 2.0; // Velocidad de movimiento de la cámara

float rotacionGeneral = 0.0;
int animacionActiva = 1;

// struct para asteroides
typedef struct{
    float distancia;
    float angulo;
    float tamano;
} Asteroide;

// Funciones prototipo
void inicializarAsteroides();
void dibujarAnillo(float radioInterno, float radioExterno);
void dibujarAsteroides();
void display(void);
void keyboard(unsigned char key, int x, int y);
void resize(int width, int height);

Asteroide cinturonAsteroides[NUM_ASTEROIDES_CINTURON];
Asteroide cinturonKuiper[NUM_ASTEROIDES_KUIPER];

// inicializa posiciones y caracteristicas de los asteroides
void inicializarAsteroides()
{
    // inicialización de asteroides del cinturon principal
    for(int i = 0; i < NUM_ASTEROIDES_CINTURON; i++) {
        cinturonAsteroides[i].distancia = 16.0 + (float)rand()/RAND_MAX * 2.0;
        cinturonAsteroides[i].angulo = (float)rand()/RAND_MAX * 360.0;
        cinturonAsteroides[i].tamano = 0.02 + (float)rand()/RAND_MAX * 0.05;
    }
    
    for(int i = 0; i < NUM_ASTEROIDES_KUIPER; i++) {
        cinturonKuiper[i].distancia = 38.0 + (float)rand()/RAND_MAX * 5;
        cinturonKuiper[i].angulo = (float)rand()/RAND_MAX * 360.0;
        cinturonKuiper[i].tamano = 0.02 + (float)rand()/RAND_MAX * 0.04;
    }
}

// funcion que dibuja un anillo planetario dado un radio interno y externo
void dibujarAnillo(float radioInterno, float radioExterno) 
{
    glBegin(GL_QUADS);
    for(int i = 0; i < 360; i += 5) {
        float angle1 = i * M_PI / 180.0;
        float angle2 = (i + 5) * M_PI / 180.0;
        
        glVertex3f(radioInterno * cos(angle1), 0.0, radioInterno * sin(angle1));
        glVertex3f(radioExterno * cos(angle1), 0.0, radioExterno * sin(angle1));
        glVertex3f(radioExterno * cos(angle2), 0.0, radioExterno * sin(angle2));
        glVertex3f(radioInterno * cos(angle2), 0.0, radioInterno * sin(angle2));
    }
    glEnd();
}

// funcion que dibuja todos los asteroides en el sistema
void dibujarAsteroides()
{
    glColor3f(0.5, 0.5, 0.5);
    
    // se inserta cada asteroide en el cinturon de asteroides
    for(int i = 0; i < NUM_ASTEROIDES_CINTURON; i++)
    {
        glPushMatrix(); // Guarda la posición actual de la matriz
        glRotatef(cinturonAsteroides[i].angulo, 0.0, 1.0, 0.0); // Rota al ángulo de cada asteroide
        glTranslatef(cinturonAsteroides[i].distancia, // Traslada el asteroide a su distancia en el cinturón
                     (float)rand() / RAND_MAX * 0.5 - 0.25, 0.0); // Pequeño desplazamiento en altura
        glutSolidSphere(cinturonAsteroides[i].tamano, 8, 8); // Dibuja el asteroide como esfera sólida
        glPopMatrix(); // Restaura la posición guardada
    }
    
    glColor3f(0.4, 0.4, 0.4); // color ligeramente mas oscuro para el cinturon de Kuiper

    // se hace cada asteroide en el cinturon de Kuiper
    for(int i = 0; i < NUM_ASTEROIDES_KUIPER; i++)
    {
        glPushMatrix();
        glRotatef(cinturonKuiper[i].angulo, 0.0, 1.0, 0.0);
        glTranslatef(cinturonKuiper[i].distancia, 
                    (float)rand()/RAND_MAX * 0.3 - 0.15,
                    0.0);
        glutSolidSphere(cinturonKuiper[i].tamano, 8, 8);
        glPopMatrix();
    }
}

// pantalla
void display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // definicion de la posicion y orientacion de la camara
    gluLookAt(camX, camY, camZ,  // posicion de la cámara
              0.0, 0.0, 0.0,     // punto al que mira la cámara
              0.0, 1.0, 0.0);    // dirección "up" para la cámara
    
    glRotatef(rotacionGeneral, 0.0, 1.0, 0.0); // Rota toda la escena
    
    // Dibujar asteroides
    dibujarAsteroides();
    
    // Sol
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
        glutSolidSphere(4.0, 50, 50);
    glPopMatrix();
    
    // Mercurio
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
        glRotatef(mercurioAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(6.0, 0.0, 0.0);
        glRotatef(mercurioAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.383, 50, 50);
    glPopMatrix();
    
    // Venus
    glColor3f(0.9, 0.7, 0.5);
    glPushMatrix();
        glRotatef(venusAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(9.0, 0.0, 0.0);
        glRotatef(venusAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.949, 50, 50);
    glPopMatrix();

    // Tierra y Luna
    glPushMatrix();
        glRotatef(tierraAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(12.0, 0.0, 0.0);
        
        glColor3f(0.2, 0.5, 1.0);
        glPushMatrix();
            glRotatef(tierraAngRot, 0.0, 1.0, 0.0);
            glutSolidSphere(1.0, 50, 50);
        glPopMatrix();
        
        // Luna
        glColor3f(0.7, 0.7, 0.7);
            glRotatef(lunaAngOrb, 0.0, 1.0, 0.0);
            glTranslatef(1.5, 0.0, 0.0);
            glRotatef(lunaAngRot, 0.0, 1.0, 0.0);
            glutSolidSphere(0.27, 50, 50);
    glPopMatrix();

    // Marte
    glColor3f(1.0, 0.3, 0.0);
    glPushMatrix();
        glRotatef(marteAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(15.0, 0.0, 0.0);
        glRotatef(marteAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.532, 50, 50);
    glPopMatrix();

    // Ceres
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
        glRotatef(ceresAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(18.0, 0.0, 0.0);
        glRotatef(ceresAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.3, 50, 50);
    glPopMatrix();

    // Júpiter y Europa
    glPushMatrix();
        glRotatef(jupiterAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(22.0, 0.0, 0.0);
        
        // Anillo de Júpiter
        glColor4f(0.64, 0.48, 0.32, 0.7);
        dibujarAnillo(1.95, 2.5);
        
        glColor3f(0.8, 0.6, 0.4);
        glPushMatrix();
        glRotatef(jupiterAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(1.6, 50, 50);
    glPopMatrix();
        
        // Europa
        glColor3f(0.7, 0.7, 0.7);
            glRotatef(europaAngOrb, 0.0, 1.0, 0.0);
            glTranslatef(2.0, 0.0, 0.0);
            glRotatef(europaAngRot, 0.0, 1.0, 0.0);
            glutSolidSphere(0.27, 50, 50);
    glPopMatrix();

    // Saturno
    glPushMatrix();
        glRotatef(saturnoAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(27.0, 0.0, 0.0);
        
        // Anillo de Saturno
        glColor4f(0.72, 0.64, 0.4, 0.7);
        dibujarAnillo(1.46, 2.5);
        glColor3f(0.9, 0.8, 0.5);
        glRotatef(saturnoAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(1.1, 50, 50);
    glPopMatrix();

    // Urano
    glColor3f(0.5, 0.8, 0.9);
    glPushMatrix();
        glRotatef(uranoAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(32.0, 0.0, 0.0);
        glRotatef(uranoAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(1.0, 50, 50);
    glPopMatrix();

    // Neptuno
    glColor3f(0.2, 0.2, 0.8);
    glPushMatrix();
        glRotatef(neptunoAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(36.0, 0.0, 0.0);
        glRotatef(neptunoAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(1.0, 50, 50);
    glPopMatrix();

    // Plutón
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
        glRotatef(plutonAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(40.0, 0.0, 0.0);
        glRotatef(plutonAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.3, 50, 50);
    glPopMatrix();

    // Haumea
    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
        glRotatef(haumeaAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(42.0, 0.0, 0.0);
        glRotatef(haumeaAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.5, 50, 50); 
    glPopMatrix();

    // Makemake
    glColor3f(0.8, 0.6, 0.4);
    glPushMatrix();
        glRotatef(makemakeAngOrb, 0.0, 1.0, 0.0);
        glTranslatef(45.0, 0.0, 0.0);
        glRotatef(makemakeAngRot, 0.0, 1.0, 0.0);
        glutSolidSphere(0.5, 50, 50); 
    glPopMatrix();
    
    glutSwapBuffers();
}

// funcion que actualiza la rotación y posición de los planetas
void actualizar()
{
    if (animacionActiva){
        // actualizar angulos de orbita
        mercurioAngOrb += 2.49;
        venusAngOrb += 0.97;
        tierraAngOrb += 0.60; //10 segundos de orbitas
        marteAngOrb += 0.32;
        ceresAngOrb += 0.17;
        jupiterAngOrb += 0.05;
        saturnoAngOrb += 0.02;
        uranoAngOrb += 0.007;
        neptunoAngOrb += 0.0036;
        plutonAngOrb += 0.0024;
        lunaAngOrb += 2.0;
        europaAngOrb += 2.0;
        
        // actualizar angulos de rotacion
        mercurioAngRot += 2.0;
        venusAngRot += 1.5;
        tierraAngRot += 1.0;
        marteAngRot += 1.2;
        ceresAngRot += 0.5;
        jupiterAngRot += 0.8;
        saturnoAngRot += 0.7;
        uranoAngRot += 0.6;
        neptunoAngRot += 0.5;
        plutonAngRot += 0.4;
        lunaAngRot += 0.5;
        europaAngRot += 0.5;
        
        // actualizar asteroides
        for(int i = 0; i < NUM_ASTEROIDES_CINTURON; i++) 
        {
            cinturonAsteroides[i].angulo += 0.1;
            if(cinturonAsteroides[i].angulo >= 360.0)
                cinturonAsteroides[i].angulo -= 360.0;
        }
        
        for(int i = 0; i < NUM_ASTEROIDES_KUIPER; i++) 
        {
            cinturonKuiper[i].angulo += 0.05;
            if(cinturonKuiper[i].angulo >= 360.0)
                cinturonKuiper[i].angulo -= 360.0;
        }
        
        glutPostRedisplay();
    }
    glutTimerFunc(16, actualizar, 0);
}

// control con teclado del programa
void keyboard(unsigned char key, int x, int y) 
{
    switch(key) 
    {
        case 'q': // si se presiona la tecla 'q'
        case 'Q': // o 'Q'
            exit(0); 
            break; 
        
        case 'r': // si se presiona la tecla 'r'
        case 'R': // o 'R'
            rotacionGeneral += 5.0; // aumenta la rotación general en 5 grados
            break; 

        case ' ': // si se presiona la barra espaciadora
            animacionActiva = !animacionActiva; // cambia el estado de la animación (activa/desactiva)
            break; 
        
        // controles para la camara
        case 'w': // si se presiona la tecla 'w'
        case 'W': // o 'W'
            camY += velocidadCamara; // mueve la cámara hacia arriba
            break; 
        
        case 's': // si se presiona la tecla 's'
        case 'S': // o 'S'
            camY -= velocidadCamara; // mueve la camara hacia abajo
            break; 
        
        case 'a': // si se presiona la tecla 'a'
        case 'A': // o 'A'
            camX -= velocidadCamara; // mueve la camara hacia la izquierda
            break; 
        
        case 'd': // si se presiona la tecla 'd'
        case 'D': // o 'D'
            camX += velocidadCamara; // mueve la camara hacia la derecha
            break; 
    }
    glutPostRedisplay(); // solicita que se vuelva a dibujar la ventana para reflejar los cambios
}

// funcion resize para ajustar la ventana al redimensionarla
void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Establece el modo de visualización a RGB, doble buffer y profundidad
    glutInitWindowSize(1200, 800); // establece el tamaño de la ventana 
    glutInitWindowPosition(10, 10); // establece la posición inicial de la ventana en la pantalla
    glutCreateWindow("Sistema Solar"); // Crea la ventana con el título "Sistema Solar"

    inicializarAsteroides(); // inicializa los asteroides en la escena
    
    glutReshapeFunc(resize); // llama al cambiar el tamaño de la ventana
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard); // función que maneja eventos del teclado
    glutTimerFunc(0, actualizar, 0); // inicia temporizador que llama a la función de actualización periódicamente
    
    glClearColor(0.0, 0.0, 0.1, 1.0); // establece el color de fondo de la ventana a un azul oscuro
    
    glEnable(GL_DEPTH_TEST); // habilita el test de profundidad para gestionar el orden de los objetos
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0); 
    glEnable(GL_COLOR_MATERIAL); // habilita el material de color para aplicar colores a los objetos
    
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // define la posición de la luz en el espacio (en el origen)
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // definicion del color difuso de la luz (blanco)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // establece la posición de la luz en la escena
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); // para el color difuso de la luz
    
    glutMainLoop(); 
    
    return 0; 
}