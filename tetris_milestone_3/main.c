/*main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Aug 18 16:32:20 2016
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

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stdio.h>
#include <ncurses.h>
#include "tetromino.h"
#include "highscore.h"
#include "game.h"

int main(int argc, char *argv[]) {
  int status = 1;
  highscore_t * highscores;
  char *hsFile;
  if (argc!=2) { 
    char defName[11] = "scores.dat";
    hsFile = &defName[0];
    printf("Using default high score file\nscores.dat");
    FILE *fp = fopen(defName, "w");
    fprintf(fp,"NUL-----,0\n");
    fclose(fp);
    highscores = load_scores(hsFile);
    sleep(1);
  } else{
    hsFile = argv[1]; 
    highscores = load_scores(argv[1]);
  }
  mvprintw(1,0,"Highscores");
  highscores = game(highscores);
  //store_scores(hsFile, highscores);
  endwin();
  return (0);
}
/* main.c ends here */
