//
// Created by evgenii on 01.11.17.
//

#ifndef GRAPHIC_MAIN_H
#define GRAPHIC_MAIN_H

#include <ncurses.h>
#include <panel.h>
#include <string.h>


WINDOW* bottom_window();
WINDOW* text_window(WINDOW* BottomP);
WINDOW* edit_window(WINDOW* TextWindow);
WINDOW* open_file_window(WINDOW* TextWindow);
PANEL* open_file_panel(WINDOW* OpenFileWindow);
void print_name_file(WINDOW *win, const char *name);
WINDOW* init_graphic();
int finalize_graphic();


#endif //GRAPHIC_MAIN_H
