#define PROGRAM_TITLE "Chris Toth"
#define DISPLAY_INFO "CPSC3710 Assignment Chris Toth"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>
#include <string.h>  // For spring operations.
#include <math.h> // for sin()

#include <gl.h>   // OpenGL itself.
#include <glu.h>  // GLU support library.
#include <glut.h> // GLUT support library.

// Some global variables.
// Window IDs, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

double eyeX = 1;
double eyeY = 1;
double eyeZ = 1;

// moving UFO init coords
float UFO1_x = 3.5;
float UFO1_y = 0.0;
float UFO1_z = 0.0;

float UFO2_x = -3.5;
float UFO2_y = 0.0;
float UFO2_z = 0.0;

float UFO3_x = 0.0;
float UFO3_y = -2.0;
float UFO3_z = 3.0;

// variables for controlling 5th moving ufo
enum direction{none, Y, Z} dir;
float yMod = 0;
float zMod = 0;

// spin variable for all top pieces of the ufos
float ufoSpin = 3.0f;

void drawAxisLines(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
    // draw Z axis
    glPushMatrix();
    glBegin(GL_LINES);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // GREEN
    glVertex3f(0.0f, 0.0f, zMin);
    glVertex3f(0.0f, 0.0f, zMax);
    glEnd();
    glPopMatrix();

    // Draw X axis
    glPushMatrix();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // RED
    glVertex3f(xMin, 0.0f, 0.0f);
    glVertex3f(xMax, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Draw Y axis
    glPushMatrix();
    glBegin(GL_LINES);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // BLUE
    glVertex3f(0.0f, yMin, 0.0f);
    glVertex3f(0.0f, yMax, 0.0f);
    glEnd();
    glPopMatrix();
}

/**
* Creates UFOs based on input size s
*/
void ufo(float s)
{
    //bottom
    glColor4f(1.f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f * s, 0.0f * s, 0.0f * s);
    glVertex3f(1.0f * s, 1.0f * s, 0.0f * s);
    glVertex3f(0.5f * s, 1.0f * s, 1.0f * s);
    glVertex3f(-0.5f * s, 1.0f * s, 1.0f * s);
    glVertex3f(-1.0f * s, 1.0f * s, 0.0f * s);
    glVertex3f(-0.5f * s, 1.0f * s, -1.0f * s);
    glVertex3f(0.5f * s, 1.0f * s, -1.0f * s);
    glVertex3f(1.0f * s, 1.0f * s, 0.0f * s);
    glEnd();

    //top
    glRotatef(ufoSpin, 0, 1, 0); //spinning
    glColor4f(0.0f, 1.f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f * s, 2.0f * s, 0.0f * s);
    glVertex3f(1.0f * s, 1.0f * s, 0.0f * s);
    glVertex3f(0.5f * s, 1.0f * s, 1.0f * s);
    glVertex3f(-0.5f * s, 1.0f * s, 1.0f * s);
    glVertex3f(-1.0f * s, 1.0f * s, 0.0f * s);
    glVertex3f(-0.5f * s, 1.0f * s, -1.0f * s);
    glVertex3f(0.5f * s,1.0f * s, -1.0f * s);
    glVertex3f(1.0f * s, 1.0f * s, 0.0f * s);
    glEnd();
    glPopMatrix();
}

// draws a 6 pointed star in 3D
void drawNonConvex1()
{
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(3.5f, 0.0f, 0.0f);
    glScalef(1.0f, 1.5f, 1.0f);
    glutSolidTetrahedron();
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glutSolidTetrahedron();
    glPopMatrix();
}

// draws a 3D letter T
void drawNonConvex2()
{
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-3.5f, 0.0f, 0.0f);
    glScalef(1.0f, 1.0f, 10.0f);
    glutSolidCube(0.25);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3.5, 0.0f, 0.0f);
    glScalef(1.0, 10.0f, 1.0f);
    glutSolidCube(0.25);
    glPopMatrix();
}

// draw a snowflake like object of Rectangles
void drawNonConvex3()
{
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -3.f);
    glutSolidCube(1);
    glRotatef(45, 1, 1, 0);
    glutSolidCube(1);
    glPopMatrix();
}


/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
    glEnable(GL_AUTO_NORMAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);

    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    drawAxisLines(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    drawNonConvex1();
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    drawNonConvex2();
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    drawNonConvex3();

    // two UFOs are just spinning
    glPushMatrix();
    glTranslatef(-2.0f, -4.0f, 0.0f);
    ufo(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0f, 0, -4.0f);
    ufo(1);
    glPopMatrix();

    // two UFOs are orbiting a polyhedra
    glPushMatrix();
    glTranslatef(UFO1_x, UFO1_y, UFO1_z);
    glRotatef(ufoSpin - 3, 0, 1, 0);
    glTranslatef(UFO1_x - 2, UFO1_y - 0.5, UFO1_z);
    ufo(.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(UFO2_x, UFO2_y, UFO2_z);
    glRotatef(ufoSpin - 3, 1, 0, 0);
    glTranslatef(0, 2, 0);
    ufo(.5);
    glPopMatrix();

    // fifth UFO is flying up/down (toggle 'u' 117) back/forth (toggle 'f' 102)
    glPushMatrix();
    if (dir == Y)
    {
        if (UFO3_y >= 3)
        {
            yMod = -0.1;
        }
        else if (UFO3_y <= -2)
        {
            yMod = 0.1;
        }
        UFO3_y += yMod;
    }
    if (dir == Z)
    {
        if (UFO3_z >= 3)
        {
            zMod = -0.1;
        }
        else if (UFO3_z <= -2)
        {
            zMod = 0.1;
        }
        UFO3_z += zMod;
    }
    glTranslatef(UFO3_x, UFO3_y, UFO3_z);
    ufo(.5);
    glPopMatrix();

    ufoSpin += 3;
    glutSwapBuffers();
}
//////////////////////////////////////////////////////////////
//// Callback function called when a normal key is pressed. //
//////////////////////////////////////////////////////////////
void myCBKey(unsigned char key, int x, int y)
{
    switch (key) {
        case 117: // u
            if (dir == Y)
                dir = none;
            else
                dir = Y;
            break;
        case 102: // f
            if (dir == Z)
                dir = none;
            else
                dir = Z;
            break;
        default:
            printf ("KP: No action for %d.\n", key);
            break;
    }
}

void rotateCmd(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                eyeX = -1;
                eyeY = 0.01;
                //eyeZ = 5;
                printf("Right Mouse Button pressed. Changing LookAt.\n");
            }
                else {
                    eyeX = 1;
                    eyeY = 1;
                    printf("Right Mouse Button released. Defaulting LookAt.\n");
                }
            break;
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                eyeX = 0.01;
                eyeY = 2;
                eyeZ = 0.01;
                printf("Left Mouse Button pressed. Changing LookAt.\n");
            }
                else {
                    eyeX = 1;
                    eyeY = 1;
                    eyeZ = 1;
                    printf("Left Mouse Button released. Defaulting LookAt.\n");
                }
            break;
        default:
            printf("No action for %d.\n", button);
            break;
    }
}

///////////////////////////////////////////////////////////////
// Callback routine executed whenever the window is resized. //
//////////////////////////////////////////////////////////////
void CallBackResizeScene(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();


   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
void MyInit(int Width, int Height)
{
   // Color to clear color buffer to.
   glClearColor(0.3f, 0.1f, 0.5f, 0.5f);

   //GLfloat arrays to be passed into lighting setup functions
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 20.0 };
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lessWhite[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat pos[] = {10.0f, 10.0f, 10.0f, 0.0};
    GLfloat pos2[] = {0.0f, -5.0f, 0.0f, 0.0};

    // set the material settings of the polygons
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // setup light 0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // setup light 1
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lessWhite);
    glLightfv(GL_LIGHT1, GL_POSITION, pos2);

    // enable colors, lighting, and the lights
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    //enable depth and culling
   glEnable(GL_DEPTH_TEST);
   glClearDepth(1.0);
   glDepthFunc(GL_LESS);

   // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
   glShadeModel(GL_SMOOTH);

   // Load up the correct perspective matrix; using a callback directly.
   CallBackResizeScene(Width,Height);
}

///////////////////////////////////////////////////
// main() function.                              //
//   There are general steps in making           //
//   an OpenGL application.                      //
//   Inits OpenGL.                               //
//   Calls our own init function                 //
//   then passes control onto OpenGL.            //
///////////////////////////////////////////////////
int main(int argc, char **argv)
{
   glutInit(&argc, argv);

   // To see OpenGL drawing, take out the GLUT_DOUBLE request.
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // The following is for window creation.
   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);
   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   // Register and install the callback function to do the drawing.
   glutDisplayFunc(&CallBackRenderScene);

   // If there's nothing to do, draw.
   glutIdleFunc(&CallBackRenderScene);

   // It's a good idea to know when our window's resized.
   glutReshapeFunc(&CallBackResizeScene);

   // Register and install the callback function for
   // Some keys
   glutKeyboardFunc(&myCBKey);
   /** Callback function for mouse button **/
   glutMouseFunc(&rotateCmd);

   // OK, OpenGL's ready to go.  Let's call our own init function.
   MyInit(Window_Width, Window_Height);

   // Print out a bit of help dialog.
   printf("\n%s\n\n", PROGRAM_TITLE);
   printf("Print out some helpful information here.\n");
   printf("When you program, you can also use\n");
   printf("printf to do debugging.\n\n");

   // Above functions represents those you will do to set up your
   // application program.
   // Now pass off control to OpenGL.
   glutMainLoop();
   // Never returns.
   return 1;
}
