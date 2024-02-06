/*********
   CTIS164 - Template Source Program
----------
STUDENT : Ozge Tontu
SECTION : 1
HOMEWORK: 1
----------
PROBLEMS:-
----------
ADDITIONAL FEATURES:
1.The car moves to right side of the window.
2.The clouds move to left side of the window.
3.When you press SPACE button it stops and when you press again it continues.
4.Car and clouds start their movements again when their last coordinates reach to the borders of the window
5.You can change the color of the car body when you press c button.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  15 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

bool activetimer = true;

int x = -450;//car initial position
int xc1 = 0;//the left cloud initial position
int xc2 = 1;//the right cloud initial position
int baslangýc = -526;//for the restart movements of the clouds and car
int red = 180, green = 172, blue = 50;//for the changes the color of the car body

// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void wall()
{
    //wall ornament
    glColor3f(0.55, 0, 1);
    glRectf(-485, -400, -500, 400);
    glRectf(-385, -400, -400, 400);
    glRectf(-285, -400, -300, 400);
    glRectf(-185, -400, -200, 400);
    glRectf(-85, -400, -100, 400);
    glRectf(15, -400, 0, 400);
    glRectf(115, -400, 100, 400);
    glRectf(215, -400, 200, 400);
    glRectf(315, -400, 300, 400);
    glRectf(415, -400, 400, 400);
    glRectf(515, -400, 500, 400);
}
void label()
{
    //name, id label
    glColor3f(1, 1, 1);
    glRectf(224, 261, -209, 389);
    glColor3f(0.31, 0, 1);
    glRectf(220, 265, -205, 385);
    glColor3f(1, 1, 1);
    vprint(-40, 340, GLUT_BITMAP_8_BY_13, "--Ozge Tontu--");
    vprint(-72, 300, GLUT_BITMAP_8_BY_13, "--22002199 HOMEWORK 1--");
    glColor3f(1, 1, 1);
    glRectf(565, 261, 250, 389);
    glColor3f(0.31, 0, 1);
    glRectf(560, 266, 255, 384);
    glColor3f(1, 1, 1);
    vprint(260, 360, GLUT_BITMAP_8_BY_13, "   1.When you press 'c', the color of");
    vprint(260, 340, GLUT_BITMAP_8_BY_13, "the car body change.");
    vprint(260, 320, GLUT_BITMAP_8_BY_13, "   2.When you press 'Space'button,");
    vprint(260, 300, GLUT_BITMAP_8_BY_13, "the movements of car and clouds stop.");
}
void window()
{
    //white
    glColor3f(1, 1, 1);
    glRectf(-581, -369, 585, -365);
    glRectf(581, 250, -585, 254);
    glRectf(554, 220, -555, 224);
    glRectf(554, -339, -555, -335);
    //open brown
    glColor3ub(186, 74, 0);
    glRectf(581, -365, -585, -339);
    glRectf(581, 224, -585, 250);
    //dark brown
    glColor3ub(102, 38, 2);
    glRectf(-555, 195, 551, 220);
    glRectf(-555, -335, 551, -310);
}
void inside()
{
    //sky
    glColor3ub(41, 194, 250);
    glRectf(-30,-310,-551,195);
    glRectf(30, -310, 551, 195);
    //road
    glColor3f(0.8, 0.8, 0.8);
    glRectf(551, -310, -551, -200);
    //roadway
    glColor3f(1, 1, 1);
    glRectf(-351, -280, -551, -250);
    glRectf(151, -280, -151, -250);
    glRectf(551, -280, 351, -250);
    //sun
    glColor3ub(255, 204, 58);
    circle(-350, 140, 37);
    //pink apartment
    glColor3ub(226, 0, 253);
    glRectf(-400, -200, -500, -50);
    //green apartment
    glColor3ub(9, 196, 3);
    glRectf(-100, -200, -200, 0);
    //yellow apartment
    glColor3ub(196, 208, 95);
    glRectf(300, -200, 100, -100);
    //apartment windows
    glColor3ub(4, 70, 176);
    //for pink
    glRectf(-480, -72, -460, -94);
    glRectf(-420, -72, -440, -94);
    glRectf(-480, -134, -460, -114);
    glRectf(-420, -134, -440, -114);
    //for green
    glRectf(-180, -40, -160, -20);
    glRectf(-180, -80, -160, -60);
    glRectf(-180, -120, -160, -100);
    glRectf(-140, -40, -120, -20);
    glRectf(-140, -80, -120, -60);
    glRectf(-140, -120, -120, -100);
    //for yellow
    glRectf(157, -130, 127, -110);
    glRectf(215, -130, 185, -110);
    glRectf(273, -130, 243, -110);
    glRectf(157, -160, 127, -140);
    glRectf(215, -160, 185, -140);
    glRectf(273, -160, 243, -140);
    //apartment doors
    glColor3ub(117, 75, 5);
    glRectf(-435, -200, -465, -150); //for pink
    glRectf(-135, -200, -165, -150); //for green
    glRectf(229, -200, 171, -170);  //for yellow
    //roofs
    glColor3ub(96, 59, 0);
    glBegin(GL_TRIANGLES);
    //pink
    glVertex2f(-500, -50);
    glVertex2f(-400, -50);
    glVertex2f(-450, -10);
    //green
    glVertex2f(-200, 0);
    glVertex2f(-100, 0);
    glVertex2f(-150, 40);
    //yellow
    glVertex2f(100, -100);
    glVertex2f(300, -100);
    glVertex2f(200, -60);
    glEnd();
    //traffic light
    glColor3f(0, 0, 0);
    circle(405, -100, 15);
    glColor3ub(75, 76, 76);
    glRectf(410, -220, 400, -180);
    glRectf(390, -180, 420, -100);
    glColor3ub(231, 2, 2);//red light
    circle(405, -120, 8);
    glColor3ub(252, 253, 0);//yellow light
    circle(405, -140, 8);
    glColor3ub(64, 253, 0);//green light
    circle(405, -160, 8);
}
void car()
{
    //car tires
    glColor3f(0, 0, 0);
    circle(x - 36, -280, 20);
    circle(x + 27, -280, 20);
    //car body
    glColor3ub(red, green, blue);
    glRectf(x + 50, -270, x - 60, -220);
    glColor3f(0, 0, 0);
    glRectf(x +2, -270, x - 2, -220);

    glRectf(x-10, -245, x-25, -235);
    glRectf(x+40, -245, x+25, -235);
    glRectf(x+60, -263, x+50, -250);
    glRectf(x+60, -240, x+50, -227);
    glRectf(x+15, -220, x-25, -190);

    glBegin(GL_TRIANGLES);
    glVertex2f(x - 60, -220);
    glVertex2f(x - 25, -220);
    glVertex2f(x - 25, -190);

    glVertex2f(x + 50, -220);
    glVertex2f(x + 15, -220);
    glVertex2f(x + 15, -190);

    glEnd();
}
void clouds()
{
    glColor3f(1, 1, 1);
    circle(xc1 - 300, 80, 33);
    circle(xc1 - 255, 80, 37);
    circle(xc1 - 210, 80, 28);
    circle(xc2 + 472, 45, 31);
    circle(xc2 + 369, 47, 34);
    circle(xc2 + 430, 70, 34);
    circle(xc2 + 422, 20, 34);
}
void front_shapes()
{
    //wall ornament
    glColor3f(0.55, 0, 1);
    glRectf(-685, -400, -700, 400);
    glRectf(-585, -400, -600, 400);
    glRectf(685, -400, 700, 400);
    glRectf(585, -400, 600, 400);
    //wall
    glColor3f(0.75, 0.75, 1);
    glRectf(-600, -400, -685, 400);
    glRectf(600, -400, 685, 400);
    //open brown
    glColor3ub(186, 74, 0);
    glRectf(-555, -365, -581, 250);
    glRectf(555, -365, 581, 250);
    //dark brown
    glColor3ub(102, 38, 2);
    glRectf(-526, -335, -551, 220);
    glRectf(526, -335, 551, 220);
    glRectf(30, -310, -30, 195);
    //white
    glColor3f(1, 1, 1);
    glRectf(-581, -369, -585, 254);
    glRectf(581, -369, 585, 254);
    glRectf(-551, -335, -555, 220);
    glRectf(551, -335, 555, 220);
    glRectf(-4, -335, 4, 220);
    //window handle
    circle(-17, -37, 5);
    circle(-17, -72, 5);
    circle(17, -72, 5);
    circle(17, -37, 5);
    glRectf(-16, -75, -18, -40);
    glRectf(18, -75, 16, -40);
}
void display() 
{
    // clear window to black
    //
    glClearColor(0.75, 0.75, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    wall();
    window();
    inside();
    car();
    clouds();
    front_shapes();
    label();
    if (x == 586)
    {
        x = baslangýc;
    }
    if (xc1 == -334)
    {
        xc1 = 900;
    }
    if (xc2+430 == -585)
    {
        xc2 = 500;
    }

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    //exit when ESC is pressed
    if (key == 27)
        exit(0);

    // PAUSE and CONTINUE when spacebar is pressed.
    if (key == ' ')
        activetimer = !activetimer;
    
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    //change the car body when c is pressed.
    if (key == 'c')
    {
        red = rand() % 256;
        green = rand() % 256;
        blue = rand() % 256;
    }
    
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (activetimer)
    {
        x += 4;
        xc1 -= 1;
        xc2 -= 1;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()
}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CTIS 164 HOMEWORK");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}
