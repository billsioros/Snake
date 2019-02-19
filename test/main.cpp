
#include <window.hpp>
#include <game.hpp>

#if defined (__RANDOM__)
    #include <ctime>
    #include <cstdlib>
#endif

#include <GL/glut.h>

int main(int argc, char * argv[])
{
    #if defined (__RANDOM__)
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    #endif

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(X_WINDOW, Y_WINDOW);

    glutInitWindowSize(Game::Window::width, Game::Window::height);

    glutCreateWindow(N_WINDOW);

    glutReshapeFunc(Game::reshape);

    glutDisplayFunc(Game::display);
    
    glutKeyboardFunc(Game::keyboard);

    glutTimerFunc(TIMESPAN, Game::timer, 0);

    glutMainLoop();
    
    return 0;
}
