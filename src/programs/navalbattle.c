// Simplified naval battle game
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "navalbattle.h"
#include "../libc/stdio.h"
#include "../kernel/system.h"
#include "../kernel/kheap.h"
#include "../libc/string.h"
#include "../libc/crypto.h"
#include "../drivers/serial.h"

// Porting problems:
// - Color printf? (Need to implement ANSI escape sequences).
// - Scanf?
// - Malloc? (proof of concept)

void program_navalbattle()
{
	clear();

	grid_t* grid[SIZE][SIZE];
	grid_t* enemyGrid[SIZE][SIZE];

	init_battlefield(grid);
	init_battlefield(enemyGrid);

	placing_ally_ships(grid);
	puts("Now, time for the enemies to prepare...\n");
	placing_enemy_ships(enemyGrid);

	delay((rand()%MAX_WAIT_TIME)+10);

	puts("Here we go!\n");
	show_game_stats(grid, enemyGrid);

	do
	{
		ally_do_attack(enemyGrid);
		enemy_do_attack(grid);
		show_game_stats(grid, enemyGrid);
	} while (check_victory(grid, enemyGrid) == 0);

	free_grid(grid);
	free_grid(enemyGrid);

	return;	
}

void init_battlefield(grid_t* grid[SIZE][SIZE])
{
	for (size_t i=0; i<SIZE; i++)
	{
		for (size_t j=0; j<SIZE; j++)
		{
			grid[i][j] = (grid_t*)malloc(sizeof(grid_t));
			grid[i][j]->x = i;
			grid[i][j]->y = j;
			grid[i][j]->role = 0;
			grid[i][j]->state = -2;
		}
	}
}

// To avoid memory leaks..
void free_grid(grid_t* grid[SIZE][SIZE])
{
	for (size_t i=0; i<SIZE; i++)
	{
		for (size_t j=0; j<SIZE; j++)
		{
			free(grid[i][j]);
		}
	}
}

void show_ally_battlefield(grid_t* grid[SIZE][SIZE])
{	
	puts("\n*** Ally grid ***\n");
	puts("   0 1 2 3 4 5\n");

	for (size_t i=0; i<SIZE; i++)
	{
		printf("%d ", i);
		for (size_t j=0; j<SIZE; j++)
		{
			char roleChar = 0;
			switch(grid[i][j]->state)
			{
				case -2:
					roleChar = 32; // space
					break;
				case -1:
					roleChar = 120;
					break;
				case 0:
					roleChar = 79;
					break;
				case 1:
					roleChar = 88;
					break;
				default:
					printf("Error: bad value in grid at x=%d y=%d\n", grid[i][j]->x, grid[i][j]->y);
					shell_install();
					break;
			}

			if (j == SIZE-1)
			{
				printf("%c]", roleChar);
			} else if (j == 0) {
				printf("[%c|", roleChar);
			} else {
				printf("%c|", roleChar);
			}
		}
		puts("\n");
	}
}

void placing_ally_ships(grid_t* grid[SIZE][SIZE])
{
	puts("==== Allied preparation phase =====\nPlease enter the positions for your ships, sir.\n");

	for (size_t i=0; i<BOATS; i++)
	{
		int posX = 0, posY = 0;

		do
		{
			printf("Ship %d\n------\n", (int)i);
			puts("X coord: ");
			char input_buffer[BUFFER_SIZE];
			get_input(input_buffer, BUFFER_SIZE);
			posY = atoi(input_buffer);
			
			puts("\nY coord: ");
			char input_buffer2[BUFFER_SIZE];
			get_input(input_buffer2, BUFFER_SIZE);
			posX = atoi(input_buffer2);
			
			puts("\n");
			if (posX < 0 || posX >= SIZE || posY < 0 || posY >= SIZE)
			{
				printf("Invalid position x=%d y=%d, please retry.\n", posX, posY);
			}
			if (grid[posX][posY]->role == 1)
			{
				printf("A ship is already in x=%d y=%d, please retry.\n", posX, posY);
			}
		} while (posX < 0 || posX >= SIZE || posY < 0 || posY >= SIZE || grid[posX][posY]->role == 1);

		grid[posX][posY]->role = 1;
		grid[posX][posY]->state = 0;
	}
}

void placing_enemy_ships(grid_t* grid[SIZE][SIZE])
{
	for (size_t i=0; i<BOATS; i++)
	{
		int posX = 0, posY = 0;
		do
		{
			posX = rand() % SIZE;
			posY = rand() % SIZE;
		} while (grid[posX][posY]->role != 0);

		grid[posX][posY]->role = 1;
		grid[posX][posY]->state = 0;
	}
}

void show_enemy_battlefield(grid_t* grid[SIZE][SIZE])
{
	puts("\n*** Enemy grid ***\n");
	puts("   0 1 2 3 4 5\n");

	for (size_t i=0; i<SIZE; i++)
	{
		printf("%d ", (int)i);
		for (size_t j=0; j<SIZE; j++)
		{
			char roleChar = 0;
			switch(grid[i][j]->state)
			{
				case -2:
				case 0:
					roleChar = 32;
					break;
				case -1:
					roleChar = 120;
					break;
				case 1:
					roleChar = 88;
					break;
				default:
					printf("Error: bad value in battlefield at x=%d y=%d\n", grid[i][j]->x, grid[i][j]->y);
					shell_install();
					break;
			}
			if (j == SIZE-1)
			{
				printf("%c]", roleChar);
			} else if (j == 0) {
				printf("[%c|", roleChar);
			} else {
				printf("%c|", roleChar);
			}
		}
		puts("\n");
	}
	puts("\n");
}

void show_remaining_boats(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE])
{
	int allyShips = 0;
	int enemyShips = 0;

	for (size_t i=0; i<SIZE; i++)
	{
		for (size_t j=0; j<SIZE; j++)
		{
			if (allyGrid[i][j]->state == 0)
			{
				allyShips++;
			}

			if (enemyGrid[i][j]->state == 0)
			{
				enemyShips++;
			}
		}
	}

	printf("%d ally ships and %d enemy ships remaining.\n", allyShips, enemyShips);
	allyShips >= enemyShips ? colorputs("The allies are in a good posture.\n", yellow, black) : colorputs("The allies are losing terrain...\n", salmon, black);
}

void show_game_stats(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE])
{
	clear();
	colorputs("\n\n\nShowing known information:\n\n", cyan, black);
	show_ally_battlefield(allyGrid);
	show_enemy_battlefield(enemyGrid);
	show_remaining_boats(allyGrid, enemyGrid);
}

void do_attack(grid_t* grid[SIZE][SIZE], int x, int y)
{
	switch(grid[x][y]->state)
	{
		case -2: // Untouched ocean
			colorputs("The torpedo explodes in water. Missed.\n", orange, black);
			grid[x][y]->state = -1;
			delay(30);
			break;
		case -1: // Already hit ocean
			colorputs("We already striked here, sir... Too late.\n", orange, black);
			break;
		case 0: // Ship
			colorputs("Hit! Well done!\n", green, black);
			grid[x][y]->state = 1;
			delay(30);
			break;
		case 1: // Already hit ship
			colorputs("Sir, we already sunk that ship... (looser)\n", orange, black);
			break;
	}
}

void ally_do_attack(grid_t* enemyGrid[SIZE][SIZE])
{
	int x = 0, y = 0;
	colorputs("\n* Ally attack preparation *\n", blue, black);
	do
	{	
		// yes, x and y are inverted.
		puts("X coord: ");
		char input_buffer[BUFFER_SIZE];
		get_input(input_buffer, BUFFER_SIZE);
		y = atoi(input_buffer);
			
		puts("\nY coord: ");
		char input_buffer2[BUFFER_SIZE];
		get_input(input_buffer2, BUFFER_SIZE);
		x = atoi(input_buffer2);
		
		puts("\n");

		if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
		{
			puts("Sir, this zone is not in our operation area! Please retry.\n");
		}
	} while (x < 0 || x >= SIZE || y < 0 || y >= SIZE);

	do_attack(enemyGrid, x, y);
}

void enemy_do_attack(grid_t* allyGrid[SIZE][SIZE])
{
	int x = 0, y = 0;
	colorputs("\n* Enemies are preparing for attack, everyone take shelter! *\n", blue, black);

	do
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
	} while (allyGrid[x][y]->state == -1 || allyGrid[x][y]->state == 1);

	delay((rand()%MAX_WAIT_TIME)+10);
	do_attack(allyGrid, x, y);
}

int check_victory(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE])
{
	int allyShips = 0;
	int enemyShips = 0;

	for (size_t i=0; i<SIZE; i++)
	{
		for (size_t j=0; j<SIZE; j++)
		{
			if (allyGrid[i][j]->state == 0)
			{
				allyShips++;
			}

			if (enemyGrid[i][j]->state == 0)
			{
				enemyShips++;
			}
		}
	}

	if (allyShips > 0 && enemyShips == 0)
	{
		colorputs("The allies have won! Congratulations, chief!\n", green, black);
		return 1;
	} else if (enemyShips > 0 && allyShips == 0)
	{
		colorputs("The ennemies have won.. We must retreat.\n", red, black);
		return 1;
	}
	return 0;
}
