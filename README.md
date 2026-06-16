| `flappy_bird_documentation.docx` | Line-by-line explanation of every line of code |
---
## Settings
You can change these values at the top of `flappy_bird.c` to adjust difficulty:

```c
#define SCREEN_WIDTH   40   // width of the game screen
#define SCREEN_HEIGHT  20   // height of the game screen
#define PIPE_GAP        6   // size of the hole in the pipe (bigger = easier)
#define PIPE_SPEED      1   // how fast the pipe moves (higher = harder)
```

---

## How It Works

The game runs a loop that repeats ~12 times per second:

1. Read keyboard input
2. Apply gravity to the bird
3. Move the pipe left
4. Check for collisions
5. Draw the frame to the terminal

The "animation" works by moving the cursor back to the top of the screen each frame and overwriting the previous frame instead of scrolling.

First semester C programming course. No structs, no pointers, no external libraries — just variables, loops, functions, and if statements.
