/* game.c --- 
 * 
 * Filename: game.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Sep  6 11:08:59 2016
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
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>
#include "highscore.h"
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

highscore_t *game(highscore_t *highscores) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  //tetromino_t *dispNext = NULL;
  int nextX;
  int nextY;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = 500;
  int status;
  int counter = 0;
  int lines_cleared = 0;
  int score = 0;
  char str[80];  
  
  
  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
	start_color();
	refresh();
	init_pair(11, COLOR_WHITE, COLOR_RED);
        init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(2, COLOR_RED, COLOR_RED);
        init_pair(3, COLOR_GREEN, COLOR_GREEN);
        init_pair(4, COLOR_BLUE, COLOR_BLUE);
        init_pair(5, COLOR_WHITE, COLOR_WHITE);
      //start_color();
      //init_pair(0, COLOR_RED, COLOR_BLACK);
      //Challenge 2: Splash
      nodelay(stdscr,FALSE);
      refresh();
      int i = 0;
      int j = 0;
      getmaxyx(stdscr,y,x);
      attron(COLOR_PAIR(2));
      for(i = 0;i< x;i++){
	for(j = 0; j < y; j++){
	    mvprintw(j,i,"-");
	}
      }
      attroff(COLOR_PAIR(2));
      attron(COLOR_PAIR(11));
      mvprintw(y/2-1,x/2 - 3,"Tetris");
      mvprintw(y -y/4-1,x/2 - 13,"Press any Key to Continue");
      mvprintw(y-1,0,"Michael McCann");
      mvprintw(0,0,"  Highscores  ");
      for(i = 1; i < 11; i++){
	   mvprintw(i,0,"%d",i);
        }
      print_score_list(highscores, 3, 1, 10);
      attroff(COLOR_PAIR(11));
      refresh();
      getch();

      for(i = 0;i< x;i++){
	for(j = 0; j < y; j++){
	    mvprintw(j,i," ");
	}
      }
      refresh();
      //End Challenge 2
   
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      //getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),3,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      display_score(score, w->upper_left_x-15,w->upper_left_y);  
      state = ADD_PIECE;
      //mvprintw(1,0,"Highscores");
      //print_score_list (highscores, 0, 2, 10);
      break;
    case ADD_PIECE:          // Add a new piece to the game
      if (next) {
        //undisplay_tetromino(next);
	current = next;
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      if( move_tet(current,current->upper_left_x,current->upper_left_y) == MOVE_FAILED){
	state = GAME_OVER;
      }else {
	display_tetromino(current);
	state = MOVE_PIECE;
      }
      //Challenge 1
/*
      nextX = next->upper_left_x;
      nextY = next->upper_left_y;
      move_tet(next,0,1);
      display_tetromino(next);
      next->upper_left_x = nextX;
      next->upper_left_y = nextY;

      mvprintw(6,2,"Next Piece");
      if(dispNext){
	undisplay_tetromino(dispNext);
       }
      dispNext = next;
      move_tet(dispNext,0,1);
      display_tetromino(dispNext);
      destroy_tetromino(dispNext);
*/
      break;
    case MOVE_PIECE:         // Move the current piece 
      if ((arrow = read_escape(&c)) != NOCHAR) {
	if (arrow == UP) {
	  undisplay_tetromino(current);
	  rotate_ccw(current);
	  display_tetromino(current);
	}
	else if (arrow == DOWN) {
	  undisplay_tetromino(current);
	  rotate_cw(current);
	  display_tetromino(current);
	}
	else if (arrow == LEFT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x-1,current->upper_left_y);
	  display_tetromino(current);
	}
	else if (arrow == RIGHT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x+1,current->upper_left_y);
	  display_tetromino(current);
	}
      	else if (arrow == REGCHAR) {
	  if (c == ' ') {
	    move_timeout = DROP_RATE;
 	  }
	  if (c == 'q') {
	    state = GAME_OVER;
 	  }
	}
      } 
      if (move_counter++ >= move_timeout) {
	counter++;
	undisplay_tetromino(current);
	status = move_tet(current,current->upper_left_x,current->upper_left_y+1);
	display_tetromino(current);
	if (status == MOVE_FAILED) {
	  state = ADD_PIECE;
	  move_timeout = BASE_FALL_RATE;
	}
	move_counter = 0;
      }
      break;
    case GAME_OVER:
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);
      mvprintw(1,x/2-5,"  GAME_OVER  ");
      mvprintw(2,x/2-5,"#############");
      mvprintw(3,x/2-5," Please type ");
      mvprintw(4,x/2-5,"Three Letters");
      char initials[] = "   ";
      initials[0] = getch();
      mvprintw(5,x/2-5,"     %s       ",initials);
      initials[1] = getch();
      mvprintw(5,x/2-5,"     %s     ",initials);
      initials[2] = getch();
      mvprintw(5,x/2-5,"     %s   ",initials);

      //Highscores
      if( compare_highscore(highscores, score, 10) == 1){
          highscores = insert_score(highscores, &initials[0], score);
        }
      
      mvprintw(1,0,"Highscores");
      print_score_list (highscores, 0, 2, 10);

      mvprintw(8,x/2-5," Your Score: ");
      mvprintw(9,x/2-5,"      %d     ", score);
      mvprintw(16,x/2-5,"Hit q to exit");
      getch(); // Wait for a key to be pressed. 
      state = EXIT;
      break;
    case EXIT:
      return(highscores);  // Return the highscore structure back to main to be stored on disk. 
      break;
    }
    score = compute_score(score ,prune_well(w));
    display_score(score, w->upper_left_x-15,w->upper_left_y);
    refresh();
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
