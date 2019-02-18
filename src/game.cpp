
#include <game.hpp>
#include <types.hpp>
#include <window.hpp>
#include <snake.hpp>

#include <cctype>

#include <GL/glut.h>

Game::coordinate_t Game::Window::width = 1280.0f;
Game::coordinate_t Game::Window::height = 720.0f;

#define SNAKE_STROKE Game::Color3f(0.0f, 0.5f, 0.0f)
#define SNAKE_FILL   Game::Color3f(0.4f, 1.0f, 0.4f)

#define FOOD_STROKE  Game::Color3f(0.7f, 0.0f, 0.1f)
#define FOOD_FILL    Game::Color3f(1.0f, 0.0f, 0.1f)

static Game::Snake snake(0.0f, 0.0f, 35.0f, Game::Keys::Up, 5UL, SNAKE_STROKE, SNAKE_FILL);

static Game::Food food(0.0f, 0.0f, 17.5f, FOOD_STROKE, FOOD_FILL);

void Game::reshape(int width, int height)
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

    Game::Window::width  = static_cast<Game::coordinate_t>(width);
    Game::Window::height = static_cast<Game::coordinate_t>(height);

    gluOrtho2D(Game::Window::left(), Game::Window::right(), Game::Window::bottom(), Game::Window::top());

    glMatrixMode(GL_MODELVIEW);
}

void Game::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    food.render();

    snake.render();

    glutSwapBuffers();
}

void Game::timer(int t)
{
    glutTimerFunc(DELAY, timer, t);

    snake.update();

    glutPostRedisplay();
}

void Game::keyboard(unsigned char key, int, int)
{
    snake.steer(static_cast<Game::direction_t>(std::tolower(static_cast<int>(key))));
}
