// Conway's Game of Life program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#include "conway.h"
#include "../libc/stdio.h"
#include "../kernel/system.h"
#include "../libc/crypto.h"
#include <stdint.h>
#include "../drivers/serial.h"
#include "../libc/string.h"

void print_grid(const unsigned char grid[X][Y])
{
	for (int i=0; i<X; i++)
	{
		for (int j=0; j<Y; j++)
		{
			//(grid[i][j] == LIVE) ? putc(42) : putc(32);
			if (grid[i][j] == LIVE) {
				serial_printf(3, "alive");
			       //colorputc(32, 120);
			} else {
	       		       putc(32);
			}		       
		}
	}
}

int count_live_neighbors(const unsigned char grid[X][Y], int i, int j)
{
	int live_neighbors = 0;

	for (int x=-1; x<=1; x++)
	{
		for (int y=-1; y<=1; y++)
		{
			if (x==0 && y==0) continue;

			int ni = i+x;
			int nj = j+y;

			if (ni >= 0 && ni < X && nj >= 0)
			{
				if (grid[ni][nj] == LIVE) live_neighbors++;
			}
		}
	}
	return live_neighbors;
}

void grid_new_generation(unsigned char grid[X][Y], unsigned char temp[X][Y])
{
	for (int i=0; i<X; i++)
	{
		for (int j=0; j<Y; j++)
		{
			int cell = grid[i][j];
			int live_neighbors = count_live_neighbors(grid, i, j);

			if (cell == LIVE)
			{
				switch(live_neighbors)
				{
					case 2:
					case 3:
						temp[i][j] = LIVE;
						break;
					default:
						temp[i][j] = DEAD;
						break;
				}
			}
			else if (cell == DEAD && live_neighbors == 3)
			{
				temp[i][j] = LIVE;
			}
		}
	}

	for (int i=0; i<X; i++)
	{
		for (int j=0; j<Y; j++)
		{
			grid[i][j] = temp[i][j];
			temp[i][j] = DEAD;
		}
	}
}

void soup(unsigned char grid[X][Y])
{
	srand(global_ticks);
	for (int i=0; i<X; i++)
	{
		for (int j=0; j<Y; j++)
		{
			grid[i][j] = rand_float() > SOUP_PROB ? LIVE : DEAD; 
		}
	}
}

void program_conway(int argc, char* argv[])
{
	clear();
	unsigned char grid[X][Y] = {0};
	unsigned char temp[X][Y] = {0};

	if (argc == 1)
	{
		soup(grid);
	} else if (argc == 2 && strcmp(argv[1], "-g") == 0) {
		grid[1][2] = LIVE;
		grid[2][3] = LIVE;
		grid[3][1] = LIVE;
		grid[3][2] = LIVE;
		grid[3][3] = LIVE;	
	} else if (argc == 2 && strcmp(argv[1], "-l") == 0) {
		grid[10][3] = LIVE; grid[10][4] = LIVE; grid[10][5] = LIVE; grid[10][6] = LIVE;
		grid[11][2] = LIVE; grid[11][6] = LIVE;
		grid[12][6] = LIVE;
		grid[13][2] = LIVE; grid[13][5] = LIVE;
	}

	print_grid(grid);
	puts("generation 0");
	for (int i=1; i<GENERATIONS; i++)
	{
		grid_new_generation(grid, temp);
		delay(DELAY);
		clear();
		print_grid(grid);
		printf("generation %d", i);
	}
	
}
