
#include <window.hpp>
#include <game.hpp>

#include <GL/glut.h>

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(X_WINDOW, Y_WINDOW);

    glutInitWindowSize(Game::Window::width, Game::Window::height);

    glutCreateWindow(N_WINDOW);

    glutReshapeFunc(Game::reshape);

    glutDisplayFunc(Game::display);
    
    glutKeyboardFunc(Game::keyboard);

    glutTimerFunc(DELAY, Game::timer, 0);

    glutMainLoop();
    
    return 0;
}
