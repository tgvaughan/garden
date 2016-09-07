#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "garden.h"

WINDOW *top_view, *side_view;

char *top_view_title = "Top View";
char *side_view_title = "Side View";


void init() {
  initscr();

  if (has_colors() == FALSE) {
    shutdown();
    printf("Terminal lacks colour support.");
    exit(1);
  }

  start_color();
  
  curs_set(0);

  // Set up windows

  top_view = newwin(0,COLS/2,0,0);
  side_view = newwin(0,COLS/2,0,COLS/2);
}

void refresh_all() {
  wborder(top_view, 0, 0, 0, 0, 0, 0, 0, 0);
  wborder(side_view, 0, 0, 0, 0, 0, 0, 0, 0);

  int x_max, y_max;

  getmaxyx(top_view, y_max, x_max);
  mvwprintw(top_view, 0, (x_max-strlen(top_view_title))/2, top_view_title);

  getmaxyx(side_view, y_max, x_max);
  mvwprintw(side_view, 0, (x_max-strlen(side_view_title))/2, side_view_title);

  wrefresh(top_view);
  wrefresh(side_view);
}

void shutdown() {
  endwin();
}

int main(int argc, char **argv) {

  init();

  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  wattron(top_view, COLOR_PAIR(1));
  mvwprintw(top_view, 10, 10, "Hello, world!");
  wattroff(top_view, COLOR_PAIR(1));

  refresh_all();
  
  wgetch(top_view);

  shutdown();

  return 0;
}
