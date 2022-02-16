#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define FIELD_WIDTH  (14)
#define FIELD_HEIGHT (FIELD_WIDTH * 2)

#define FPS   (10)
#define INTERVAL (1000 / FPS)

#define PADDLE_WIDTH (4)

int ballX;
int ballY;
int ballVelocityX = 1;
int ballVelocityY = 1;

int paddleX;
int paddleY;

int field[FIELD_HEIGHT][FIELD_WIDTH];

void DrawScreen() {
 system("cls");
 for (int x = 0; x < FIELD_WIDTH + 2; x++)
  printf("■");
 printf("\n");

 for (int y = 0; y < FIELD_HEIGHT; y++) {
  printf("■");
  for (int x = 0; x < FIELD_WIDTH; x++) {
   if ((x == ballX) && (y == ballY))
    printf("●");
   else if ((y == paddleY) && (x >= paddleX) && (x < paddleX + PADDLE_WIDTH))
    printf("回");
   else if(field[y][x])
    printf("□");
   else
    printf("　");
  }
  printf("■");
  printf("\n");
 }

 for (int x = 0; x < FIELD_WIDTH + 2; x++)
  printf("■");
}

void Reset() {
 ballX = rand() % FIELD_WIDTH;
 ballY = FIELD_HEIGHT / 3;
 ballVelocityX = (rand() % 2) ? 1 : -1;
 ballVelocityY = 1;

 paddleX = (FIELD_WIDTH - PADDLE_WIDTH) / 2;
 paddleY = FIELD_HEIGHT - 3;

 for (int y = 0; y < FIELD_HEIGHT / 4; y++)
  for (int x = 0; x < FIELD_WIDTH; x++)
   field[y][x] = 1;

 DrawScreen();
}

int main() {
 srand((unsigned int)time(NULL));

 Reset();

 clock_t lastClock = clock();
 while (1) {
  clock_t nowClock = clock();
  if (nowClock >= lastClock + INTERVAL) {
   ballX += ballVelocityX;
   ballY += ballVelocityY;

   if (ballX <= 0)
    ballVelocityX = 1;

   if (ballX >= FIELD_WIDTH - 1)
    ballVelocityX = -1;

   if (ballY <= 0)
    ballVelocityY = 1;

   if (ballY >= FIELD_HEIGHT - 1)
    ballVelocityY = -1;

   if (
    (ballY == paddleY - 1)
    && (ballX >= paddleX - 1)
    && (ballX < paddleX + PADDLE_WIDTH + 1)
    ) {
    if (ballX < paddleX + PADDLE_WIDTH / 2)
     ballVelocityX = -1;
    else
     ballVelocityX = 1;

    ballVelocityY = -1;
   }

   for (int x = ballX - 1; x <= ballX + 1; x++) {
    int y = ballY - 1;
    if ((y < 0) || (x < 0) || (x >= FIELD_WIDTH))
     continue;

    if (field[y][x]) {
     field[y][x] = 0;
     ballVelocityY = 1;
    }
   }


   DrawScreen();

   lastClock = nowClock;

   if (ballY >= FIELD_HEIGHT-1)
    Reset();
  }

  if (_kbhit()) {
   switch (_getch()) {
   case 'a': paddleX--; break;
   case 'd': paddleX++; break;
   }

   if (paddleX < 0)
    paddleX = 0;

   if (paddleX > FIELD_WIDTH - PADDLE_WIDTH)
    paddleX = FIELD_WIDTH - PADDLE_WIDTH;

   DrawScreen();
  }
 }
 _getch();
}