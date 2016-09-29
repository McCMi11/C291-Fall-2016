/* tetromino.c --- 
 * 
 * Filename: tetromino.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Fri Sep  2 09:38:49 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tetromino.h"

const tetromino_t tetromino_types[7] = {
  {"block",
   {{0,0,0,0}, 
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"tee",
   {{0,0,0,0}, 
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"zigzag_l",
   {{0,0,1,0}, 
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"zigzag_r",
   {{0,1,0,0}, 
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"lform_l",
   {{0,0,1,0}, 
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"lform_r",
   {{0,1,0,0}, 
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}},
  {"pipe",
   {{0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}}, 
   0,
   0,
   '%',
   {0,0,0}}
};

int rotate_cw(tetromino_t *tet) {
  char temp[4][4];
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<4;y++) {
      temp[x][y] = tet->piece[y][3-x]; 
    }
  }
  memcpy(tet->piece,&temp,sizeof(tet->piece));
}

int rotate_ccw(tetromino_t *tet) {
  char temp[4][4];
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<4;y++) {
      temp[x][y] = tet->piece[3-y][x]; 
    }
  }
  memcpy(tet->piece,&temp,sizeof(tet->piece));
}

tetromino_t *create_tetromino (int initial_x, int initial_y) {
  int type;
  tetromino_t *tet = malloc(sizeof(tetromino_t));
  srand(time(NULL));
  type = rand()%7;
  memcpy(tet, &tetromino_types[type], sizeof(tetromino_t));
  tet->upper_left_x = initial_x;
  tet->upper_left_y = initial_y;
  return(tet);
}

void display_tetromino(tetromino_t *tet) {
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<+4;y++) {
      if (tet->piece[x][y]) {
	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x,"%c",tet->draw_char);
      }
    }
  }
}

void undisplay_tetromino(tetromino_t *tet) {
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<+4;y++) {
      if (tet->piece[x][y]) {
	mvprintw(tet->upper_left_y+y,tet->upper_left_x+x," ",tet->draw_char);
      }
    }
  }
}

int destroy_tetromino(tetromino_t *tet) {
  free(tet);
}

/* tetromino.c ends here */
