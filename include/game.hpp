
#pragma once

#define X_WINDOW (0)
#define Y_WINDOW (0)
#define N_WINDOW ("Snake")
#define DELAY (100U)

namespace Game
{
    void reshape(int width, int height);
    void display(void);
    void timer(int t);
    void keyboard(unsigned char key, int, int);
}
