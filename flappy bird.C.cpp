#include <stdio.h>
#include <stdlib.h>
#include <windows.h>                                                          

int col_bird_pipe();

#define SCREEN_WIDTH   40
#define SCREEN_HEIGHT  20
#define PIPE_GAP        6                                             
#define PIPE_SPEED      1                                             


float bird_y    = 10;                                               
float bird_speed = 0;                                               

int pipe_x      = 35;                                               
int pipe_hole   = 7;                                                

int score = 0;

int game_over = 0;

void reset_cursor()
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hide_cursor()
{
    CONSOLE_CURSOR_INFO info = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void draw()
{
    reset_cursor();                                            

    int row, col;

    for (row = 0; row < SCREEN_HEIGHT; row++)
    {
        for (col = 0; col < SCREEN_WIDTH; col++)
        {
            if (col == 5 && row == (int)bird_y)
            {
                printf("O");                      
            }

            else if (col == pipe_x)
            {
                int in_hole = (row >= pipe_hole && row < pipe_hole + PIPE_GAP);

                if (in_hole)
                    printf(" ");                               
                else
                    printf("|");                               
            }

            else if (col == SCREEN_WIDTH - 1)
            {
                printf("|");
            }

            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }

    for (col = 0; col < SCREEN_WIDTH; col++)
        printf("-");
    printf("\n");

    printf("  Score: %d     (SPACE=flap, Q=quit)\n", score);
}

void update()
{
    bird_speed = bird_speed + 0.4f;                                  
    bird_y     = bird_y + bird_speed;                                

    pipe_x = pipe_x - PIPE_SPEED;

    if (pipe_x < 0)
    {
        pipe_x    = SCREEN_WIDTH - 2;
        pipe_hole = 3 + rand() % (SCREEN_HEIGHT - PIPE_GAP - 5);
        score     = score + 1;
    }

    if ((int)bird_y >= SCREEN_HEIGHT || bird_y < 0)
    {
        game_over = 1;
    }

    if (col_bird_pipe())
    {
        game_over = 1;
    }
}

int col_bird_pipe()
{
    int bird_row = (int)bird_y;
    int bird_col = 5;

    if (bird_col == pipe_x)
    {
        int in_hole = (bird_row >= pipe_hole && bird_row < pipe_hole + PIPE_GAP);

        if (!in_hole)
            return 1;                   
    }

    return 0;                     
}

int main()
{
    hide_cursor();
    srand(42);                            

    printf("=== FLAPPY BIRD ===\n");
    printf("Press SPACE to start!\n");

    while (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
        Sleep(10);

    while (!game_over)
    {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            bird_speed = -2.0f;                                    
        }

        if (GetAsyncKeyState('Q') & 0x8000)
        {
            break;
        }

        update();                        
        draw();                          

        Sleep(80);                                              
    }

    printf("\n  GAME OVER! Final score: %d\n", score);
    Sleep(2000);

    return 0;
}
