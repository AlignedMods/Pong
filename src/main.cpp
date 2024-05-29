#include <iostream>
#include <raylib.h>

int main() {

    const int width = 1200;
    const int height = 900;
    int fps = 60;

    InitWindow(width,height,"game");
    SetTargetFPS(fps);

    while(WindowShouldClose() == !true)
    {
        BeginDrawing();

        DrawLine(width/2,0,width/2,height,WHITE);
        DrawCircle(width/2,height/2,20,WHITE);
        DrawRectangle(0,height/2-60,25,120,WHITE);
        DrawRectangle(width-25,height/2-60,25,120,WHITE);

        EndDrawing();
    }

    CloseWindow();

  return 0;
}