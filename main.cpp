#include <raylib.h>
const Color apple = {255, 0, 0, 255};
const Color back = {0, 0, 255, 255};
const Color body = {0, 255, 0, 255};
int board[15][15], score, headx, heady, direction, applex, appley;
bool active;
void initializeScreen() {
    score = 0; headx = 4; heady = 5; direction = 2; applex = 9; appley = 9; board[3][5] = 1;
    active = true;
    for(int i = 0; i < 225; i++){
        board[i%15][i/15] = 0;
    }
}
int main() {
    initializeScreen();
    int firstTime = true;
    InitWindow(600, 600, "Basic Snake in C++");
    SetTargetFPS(8);
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(back);
        if(active){
            board[headx][heady] = score + 1;
            if(direction % 2 == 0) {
                headx += (direction-1);
            } else {
                heady += (direction-2);
            }
            if(headx==applex && heady==appley) {
                score++;
                do{
                    applex = GetRandomValue(0,14);
                    appley = GetRandomValue(0,14);
                }while(board[applex][appley] > 0);
            }
            if(headx > 14 || headx < 0 || heady > 14 || heady < 0 || board[headx][heady] > 0){
                active = false;
            }
            for(int i=0; i<15; i++){
                for(int j=0; j<15; j++){
                    if(headx == j && heady == i){
                        DrawRectangle(j*40, i*40, 40, 40, body);
                    } else if(applex == j && appley == i){
                        DrawRectangle(j*40, i*40, 40, 40, apple);
                    }
                    if(board[j][i] > 0){
                        board[j][i]--;
                        DrawRectangle(j*40, i*40, 40, 40, body);
                    }
                }
            }
            if(IsKeyPressed(KEY_D)&& direction!=0)
                direction = 2;
            if(IsKeyPressed(KEY_A)&& direction!=2)
                direction = 0;
            if(IsKeyPressed(KEY_W)&& direction!=3)
                direction = 1;
            if(IsKeyPressed(KEY_S)&& direction!=1)
                direction = 3;
        } else {
            if(firstTime){
                DrawText("Welcome to Snake!", 15, 250, 15, apple);
            }
            DrawText("Press SPACE to begin, use WASD to move.", 15, 300, 15, apple);
        }
        EndDrawing();
        if(IsKeyDown(KEY_SPACE) && !active) {
            firstTime = false;
            initializeScreen();
        }
    }
    CloseWindow();
}