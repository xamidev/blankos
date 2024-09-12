// Snake game
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../kernel/system.h"
#include "../libc/stdio.h"
#include "../drivers/framebuffer.h"
#include "../drivers/kb.h"
#include "../libc/string.h"
#include "../libc/crypto.h"

#define WIDTH        25
#define HEIGHT 	     25
#define PIXEL_SIZE   20

// to add:
// score
// sound

typedef struct
{
	int x;
	int y;
} SnakeSegment;

typedef struct
{
	SnakeSegment segments[100];
	int length;
	int dx;
	int dy;
} Snake;

typedef struct
{
	int x;
	int y;
} Food;

Snake snake;
Food food;

int is_snake(int x, int y);

void init_game()
{
	snake.length = 1;
	snake.segments[0].x = WIDTH/2;
	snake.segments[0].y = HEIGHT/2;
	snake.dx = 1;
	snake.dy = 0;

	food.x = rand() % (WIDTH-1);
	food.y = rand() % (HEIGHT-1);
}

void draw_board()
{
	erase_cursor();
	for (int y=0; y<=HEIGHT; y++)
	{
		for (int x=0; x<=WIDTH; x++)
		{
			if (x == 0 || x == WIDTH || y == 0 || y == HEIGHT)
			{
				draw_square(x, y, white, PIXEL_SIZE);
			}
			else if (is_snake(x, y)) {
				draw_square(x, y, green, PIXEL_SIZE);
			} else if(x == food.x && y == food.y) {
				draw_square(x, y, red, PIXEL_SIZE);
			} else {
				draw_square(x, y, black, PIXEL_SIZE);
			}
		}
	}
}

int is_snake(int x, int y)
{
	for (int i=0; i<snake.length; i++)
	{
		if (snake.segments[i].x == x && snake.segments[i].y == y)
		{
			return 1;
		}
	}
	return 0;
}

void move_snake()
{
	for (int i=snake.length-1; i>0; i--)
	{
		snake.segments[i] = snake.segments[i-1];
	}

	snake.segments[0].x += snake.dx;
	snake.segments[0].y += snake.dy;

	if (snake.segments[0].x < 0) snake.segments[0].x = WIDTH-1;
	if (snake.segments[0].x >= WIDTH) snake.segments[0].x = 0;
	if (snake.segments[0].y < 0) snake.segments[0].y = HEIGHT-1;
	if (snake.segments[0].y >= HEIGHT) snake.segments[0].y = 0;

	if (snake.segments[0].x == food.x && snake.segments[0].y == food.y)
	{
		snake.length++;
		food.x = rand() % (WIDTH-1);
		food.y = rand() % (HEIGHT-1);
	}
}

void handle_input(char key)
{	
	if (key == 'w' && snake.dy == 0) {
		snake.dx = 0;
		snake.dy = -1;
	} else if (key == 's' && snake.dy == 0) {
		snake.dx = 0;
		snake.dy = 1;
	} else if (key == 'a' && snake.dx == 0) {
		snake.dx = -1;
		snake.dy = 0;
	} else if (key == 'd' && snake.dx == 0) {
		snake.dx = 1;
		snake.dy = 0;
	} else if (key =='q') {
		clear();
		shell_install();
	} 
}

void program_snake(int argc, char* argv[])
{
	int game_speed;
	if (argc < 2)
	{
		game_speed = 4;
	} else {
		game_speed = atoi(argv[1]);
	}

	clear();
	init_game();

	for(;;)
	{
		char key = keyboard_getchar_non_blocking();

		if (key)
		{
			handle_input(key);
		}

		move_snake();
		draw_board();
		delay(game_speed);
	}
}
