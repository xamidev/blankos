// Simplified naval battle game header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef NAVALBATTLE_H
#define NAVALBATTLE_H

#include "../drivers/framebuffer.h"

typedef struct
{
	int x;
	int y;
	int role;
	int state;	
} grid_t;

#define SIZE	      6
#define BOATS	      5
#define MAX_WAIT_TIME 20
#define BUFFER_SIZE   16

void init_battlefield(grid_t* grid[SIZE][SIZE]);
void show_ally_battlefield(grid_t* grid[SIZE][SIZE]);
void placing_ally_ships(grid_t* grid[SIZE][SIZE]);
void placing_enemy_ships(grid_t* grid[SIZE][SIZE]);
void show_enemy_battlefield(grid_t* grid[SIZE][SIZE]);
void show_remaining_boats(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE]);
void show_game_stats(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE]);
void do_attack(grid_t* grid[SIZE][SIZE], int x, int y);
void ally_do_attack(grid_t* enemyGrid[SIZE][SIZE]);
void enemy_do_attack(grid_t* allyGrid[SIZE][SIZE]);
int check_victory(grid_t* allyGrid[SIZE][SIZE], grid_t* enemyGrid[SIZE][SIZE]);

#endif
