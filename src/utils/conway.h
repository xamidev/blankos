// Conway's Game of Life program header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef CONWAY_H
#define CONWAY_H

#define X 66
#define Y 240

#define GENERATIONS 100
#define DEAD 0
#define LIVE 1
#define SOUP_PROB 0.7
#define DELAY 10

void print_grid(const unsigned char grid[X][Y]);
int count_live_neighbors(const unsigned char grid[X][Y], int i, int j);
void grid_new_generation(unsigned char grid[X][Y], unsigned char temp[X][Y]);
void soup(unsigned char grid[X][Y]);

#endif
