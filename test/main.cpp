
#include <snake.hpp>

#include <cctype>

#include <GL/glut.h>

#define X_WINDOW (0)
#define Y_WINDOW (0)
#define N_WINDOW ("Snake")

Game::coordinate_t Game::Window::width = 1280.0f;
Game::coordinate_t Game::Window::height = 720.0f;

#define DELAY (200U)

void reshape(int width, int height);
void display(void);
void timer(int t);
void keyboard(unsigned char key, int, int);

static Game::Snake snake(0.0f, 0.0f, 35.0f, NORTH, 5UL);

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(X_WINDOW, Y_WINDOW);

    glutInitWindowSize(Game::Window::width, Game::Window::height);

    glutCreateWindow(N_WINDOW);

    glutReshapeFunc(reshape);

    glutDisplayFunc(display);
    
    glutKeyboardFunc(keyboard);

    glutTimerFunc(DELAY, timer, 0);

    glutMainLoop();
    
    return 0;
}

void reshape(int width, int height)
{
    if (height < 1)
        height = 1;

    if (width < 1)
        width = 1;

    glViewport
    (
        X_WINDOW, Y_WINDOW, static_cast<GLsizei>(width), static_cast<GLsizei>(height)
    );

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    Game::Window::width = static_cast<Game::coordinate_t>(width);
    Game::Window::height = static_cast<Game::coordinate_t>(height);

    gluOrtho2D(Game::Window::left(), Game::Window::right(), Game::Window::bottom(), Game::Window::top());

    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    snake.render();

    glutSwapBuffers();
}

void timer(int t)
{
    glutTimerFunc(DELAY, timer, t);

    snake.update();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
    snake.steer(static_cast<Game::direction_t>(std::tolower(static_cast<int>(key))));
}
