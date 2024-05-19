#include "CHIP-8.h"
#include "raylib.h"
#include <stdio.h>
#include <time.h>

int main(void)
{
    /*if (argc != 2)
    {
        printf("Usage: CHIP-8 <(path to)rom name>\n");
      
        return 1;
    }*/
    SetRandomSeed((unsigned int)time(0));

    InitWindow(SCREEN_WIDTH * 10, SCREEN_HEIGHT * 10, "CHIPX");

    SetTargetFPS(60);

    //Get rom file from cmd line argument
    char* romName = "C:/Users/_ars_/source/repos/CHIP-8-Interpreter/4-flags.ch8";


    // CHIP-8 system declaration
    Chip8 system = *sysInit(romName);

    while (!WindowShouldClose())
    {
        for (int i = 0; i < 11; i++) {
            cycle(&system);
        }
        /*cycle(&system);*/
        BeginDrawing();

        ClearBackground(BLACK);

        if (system.drawScreen) {
            for (int i = 0; i < SCREEN_HEIGHT; i++) {
                for (int j = 0; j < SCREEN_WIDTH ; j++) {
                    if (system.screen[i][j]) {
                        DrawRectangle(j * 10, i * 10, 10, 10, RAYWHITE);
                    }
                }
            }
        }
        EndDrawing();

        /*system.drawScreen = false;*/

        if (system.delayTimer > 0) {
            system.delayTimer -= 1;
        }
        if (system.soundTimer > 0) {
            system.soundTimer -= 1;
        }
    }
    CloseWindow();
    return 0;
}