#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <string.h>

int width = 800;
int height = 600;
int option = 0;

float L1, L2, M1, M2;

float alpha1, alpha2;
float theta1, theta2;
float omega1 = 0.0f;
float omega2 = 0.0f;

const float dt = 0.01f;

void update(double time)
{
    float num1 = -9.81 * (2 * M1 + M2) * sin(theta1);
    float num2 = -M2 * 9.81 * sin(theta1 - 2 * theta2);
    float num3 = -2 * sin(theta1 - theta2) * M2;
    float num4 = omega2 * omega2 * L2 + omega1 * omega1 * L1 * cos(theta1 - theta2);
    float den = L1 * (2 * M1 + M2 - M2 * cos(2 * theta1 - 2 * theta2));
    float angular_acceleration1 = (num1 + num2 + num3 * num4) / den;


    num1 = 2 * sin(theta1 - theta2);
    num2 = (omega1 * omega1 * L1 * (M1 + M2));
    num3 = 9.81 * (M1 + M2) * cos(theta1);
    num4 = omega2 * omega2 * L2 * M2 * cos(theta1 - theta2);
    den = L2 * (2 * M1 + M2 - M2 * cos(2 * theta1 - 2 * theta2));
    float angular_acceleration2 = (num1 * (num2 + num3 + num4)) / den;

    omega1 += angular_acceleration1 * time;
    omega2 += angular_acceleration2 * time;
    theta1 += omega1 * time;
    theta2 += omega2 * time;
}

void drawPendulum_arms() {
    float x1, y1, x2, y2;

    x1 = L1 * sin(theta1);
    y1 = -L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 - L2 * cos(theta2);

    y1 += 100.0;
    y2 += 100.0;

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 100.0f);
    glVertex2f(x1, y1);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawPendulum_bobs() {
    float x1, y1, x2, y2;

    x1 = L1 * sin(theta1);
    y1 = -L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 - L2 * cos(theta2);

    y1 += 100.0;
    y2 += 100.0;

    glPushMatrix();
    glTranslatef(x1, y1, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(M1, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x2, y2, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidSphere(M2, 20, 200);
    glPopMatrix();

}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPendulum_arms();

    glColor3f(1, 1, 1);
    glRasterPos2f(-200, 250);
    int len2, i;
    char str[50];
    sprintf_s(str, "D O U B L E  P E N D U L U M  S I M U L A T I O N");
    len2 = (int)strlen(str);
    for (i = 0; i < len2; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
    }

    glColor3f(1, 1, 1);
    glRasterPos2f(-100, -240);
    int len;
    char string[50];
    sprintf_s(string, "Initial Angles : (%.2f,%.2f)", alpha1, alpha2);
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
    }

    glColor3f(1, 1, 1);
    glRasterPos2f(-100, -280);
    int len1;
    char string1[50];
    theta1 = theta1 * 180 / 3.14;
    theta2 = theta2 * 180 / 3.14;
    if (theta1 >= 360) theta1 -= 360;
    if (theta2 >= 360) theta2 -= 360;
    if (theta1 <= -360) theta1 += 360;
    if (theta2 <= -360) theta2 += 360;
    sprintf_s(string1, "Final Angles   : (%.2f,%.2f)", theta1, theta2);
    len1 = (int)strlen(string1);
    for (i = 0; i < len1; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string1[i]);
    }
    theta1 = theta1 * 3.14 / 180;
    theta2 = theta2 * 3.14 / 180;

    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPendulum_bobs();


    glFlush();
}

void reshape(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}
void idle()
{
    if (option == 1)
    {
        update(dt);
        glutPostRedisplay();
    }
}
void menu(int op)
{
    option = op;
}

int main(int argc, char** argv) {

    printf("****************DOUBLE PENDULUM SIMULATOR*******************\n\n");

    printf("Enter the length of rod 1 :");
    scanf("%f", &L1);
    printf("Enter the length of rod 2 :");
    scanf("%f", &L2);

    printf("Enter the mass of bob 1 :");
    scanf("%f", &M1);
    printf("Enter the mass of bob 2 :");
    scanf("%f", &M2);

    printf("Enter the initial inclination(angle [0,360]) of bob 1 :");
    scanf("%f", &theta1);
    printf("Enter the initial inclination(angle [0,360]) of bob 2 :");
    scanf("%f", &theta2);

    if (theta1 >= 360) theta1 -= 360;
    if (theta1 >= 360) theta2 -= 360;

    alpha1 = theta1;
    alpha2 = theta2;

    theta1 = theta1 * 3.14 / 180;
    theta2 = theta2 * 3.14 / 180;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Double Pendulum Simulation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glEnable(GL_DEPTH_TEST);
    glutCreateMenu(menu);
    glutAddMenuEntry("Start oscillation", 1);
    glutAddMenuEntry("Stop oscillation", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}

