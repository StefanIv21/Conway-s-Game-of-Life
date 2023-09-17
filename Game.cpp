#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <thread>
#include <chrono>

using namespace std;

const int winWidth = 840;
const int winHeight = 480;
const int matrixRows = 40;
const int matrixCols = 20;

enum GameState {
    STARTING,
    GAME_CHOOSE,
    PROPAGATING,
    LAST
};

GameState gameState;
int i,j;
bool gameMatrix[matrixRows][matrixCols];
bool tempMatrix[matrixRows][matrixCols];
bool hasLife;

void header() {
    const unsigned char name[] = "GAME OF LIFE";

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(377, 450);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, name);

    glutSwapBuffers();
}

void printGrid() {
    glColor3f(0.44f, 0.44f, 0.66f);
    glBegin(GL_LINES);

    for (int i = 20; i <= 820; i += 20) {
        glVertex2f(i, 440);
        glVertex2f(i, 40);
    }

    for (int i = 40; i <= 440; i += 20) {
        glVertex2f(20, i);
        glVertex2f(820, i);
    }

    glEnd();

    glutSwapBuffers();
}

void updateDisplay() {
    header();

    glColor3f(0.0f, 0.4f, 0.0f);
    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixCols; j++) {
            if (gameMatrix[i][j] == true) {
                glBegin(GL_POLYGON);
                glVertex2f(i * 20 + 20, j * 20 + 40);
                glVertex2f(i * 20 + 40, j * 20 + 40);
                glVertex2f(i * 20 + 40, j * 20 + 60);
                glVertex2f(i * 20 + 20, j * 20 + 60);
                glEnd();
            }
        }
    }

    const unsigned char name1[] = "Press 'i' to cycle 10 times";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(600, 350);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, name1);

    const unsigned char name2[] = "Press Enter to cycle 1 time";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(600, 250);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, name2);

    const unsigned char name3[] = "Press Esc to exit";
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(600, 150);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, name3);

    glutSwapBuffers();
}

void last() {
    gameState = LAST;

    const unsigned char msg[] = "YOU DIDN'T SURVIVE THE LIFE";
    const unsigned char restart[] = " RESTART ";

    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2f(280, 360);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, msg);

    glColor3f(0.44, 0.44, 0.44); // Restart button
    glBegin(GL_POLYGON);
    glVertex2f(winWidth / 2 - 50, winHeight / 2 - 20);
    glVertex2f(winWidth / 2 + 65, winHeight / 2 - 20);
    glVertex2f(winWidth / 2 + 65, winHeight / 2 + 20);
    glVertex2f(winWidth / 2 - 50, winHeight / 2 + 20);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Restart text
    glRasterPos2f(winWidth / 2 - 50, winHeight / 2 - 7);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, restart);

    glutSwapBuffers();
}

void propagateOnce() {
    gameState = PROPAGATING;

    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixCols; j++) {
            tempMatrix[i][j] = gameMatrix[i][j];
            gameMatrix[i][j] = false;
        }
    }

    hasLife = false;

    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixCols; ++j) {
            int neighbourCount = 0;

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < matrixRows && y >= 0 && y < matrixCols) {
                        neighbourCount += tempMatrix[x][y];
                    }
                }
            }

            if (tempMatrix[i][j]) {
                gameMatrix[i][j] = (neighbourCount == 2 || neighbourCount == 3);
            } else {
                gameMatrix[i][j] = (neighbourCount == 3);
            }

            hasLife |= gameMatrix[i][j];
        }
    }

    updateDisplay();

    if (!hasLife) {
        last();
    }
}

void propagateMultipleTimes(int n) {
    for (int i = 0; i < n; i++) {
        propagateOnce();
        if (!hasLife) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void startMenu() {
    gameState = STARTING;

    const unsigned char start[] = "START";
    const unsigned char quit[] = "QUIT";

    header();

    glColor3f(0.78, 0.16, 0.83);
    glBegin(GL_LINES);
    glVertex2f(0, 430);
    glVertex2f(860, 430);
    glEnd();

    glColor3f(0.78, 0.16, 0.83); // Restart button
    glBegin(GL_POLYGON);
    glVertex2f(winWidth / 2 - 50, winHeight / 2 - 20);
    glVertex2f(winWidth / 2 + 65, winHeight / 2 - 20);
    glVertex2f(winWidth / 2 + 65, winHeight / 2 + 20);
    glVertex2f(winWidth / 2 - 50, winHeight / 2 + 20);
    glEnd();

    glColor3f(1.0, 1.0, 0.0); // Restart text
    glRasterPos2f(winWidth / 2 - 35, winHeight / 2 - 7);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, start);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            propagateMultipleTimes(10);
            break;
        case 27: // '27' corresponds to the 'Esc' key
            exit(0);
            break;
        case 13: // '13' corresponds to the 'Enter' key
            if (gameState == PROPAGATING) {
                propagateOnce();
            }
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) return;

    switch (gameState) {
        case STARTING: {
            if (y < 220 || y > 270) return;

            if (x > 370 && x < 490) {
                gameState = GAME_CHOOSE;
                const unsigned char name[] = "START";
				glClear(GL_COLOR_BUFFER_BIT);
				glColor3f(1.0f, 1.0f, 1.0f);
				glRasterPos2f(377, 450);
				glutBitmapString(GLUT_BITMAP_HELVETICA_18, name);
				glutSwapBuffers();
                glColor3f(0.11, 0.89, 0.34);
                printGrid();
            }
        }
        break;

        case GAME_CHOOSE: {
            if (x < 505 && x > 380 && y <= 30 && y >= 15) {
                propagateOnce();
                return;
            }

            if (y < 40 || y > 440 || x > 820 || x < 20) return;
            int i = (x - 20) / 20;
            int j = (winHeight - y - 40) / 20;

            glBegin(GL_POLYGON);
            glVertex2f(i * 20 + 20, j * 20 + 40);
            glVertex2f(i * 20 + 40, j * 20 + 40);
            glVertex2f(i * 20 + 40, j * 20 + 60);
            glVertex2f(i * 20 + 20, j * 20 + 60);
            glEnd();

            gameMatrix[i][j] = true;
            glutSwapBuffers();
        }
        break;

        case LAST: {
            if (y < 200 || y > 270) return;
            if (x > 360 && x < 490) {
                for (int i = 0; i < matrixRows; i++) {
                    for (int j = 0; j < matrixCols; j++) {
                        gameMatrix[i][j] = false;
                    }
                }
                startMenu();
            }
        }
        break;
    }
}




int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Game_of_life");

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, winWidth, 0, winHeight);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    startMenu();
    glutMainLoop();

    return 0;
}

