#include <iostream>
#include <raylib.h>

class Ball {

    public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x,y,radius,WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight()||y - radius <= 0) {

            speed_y *= -1;

        }

        if(x + radius >= GetScreenWidth()||x - radius <= 0) {

            speed_x *= -1;

        }
    }

};

class Paddle {

    public:
    float x,y;
    float width,height;
    int speed;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

};

class CPUPaddle: public Paddle{
    public:

    void Update(int ball_y) {
        if (y + height/2 > ball_y) {
            y = y - speed;
        }
        if (y + height/2 <= ball_y) {
            y = y + speed;
        }
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
};

Ball ball;
Paddle player;
CPUPaddle cpu;

int main() {

    const int width = 1280;
    const int height = 800;
    int fps = 60;

    ball.radius = 20;
    ball.x = width/2;
    ball.y = height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = 0;
    player.y = height / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = width - cpu.width - 10;
    cpu.y = height / 2 - player.height / 2;
    cpu.speed = 6;

    InitWindow(width,height,"game");
    SetTargetFPS(fps);

    while(WindowShouldClose() == !true)
    {
        BeginDrawing();
        //updating the ball
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{player.x,player.y,player.width,player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{cpu.x,cpu.y,cpu.width,cpu.height})) {
            ball.speed_x *= -1;
        }

        //drawing
        ClearBackground(BLACK);
        DrawLine(width/2,0,width/2,height,WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();

        EndDrawing();
    }

    CloseWindow();

  return 0;
}