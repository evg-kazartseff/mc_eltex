//
// Created by evgenii on 01.11.17.
//

#include "graphic.h"

WINDOW* init_graphic() {
    WINDOW* main = initscr();
    start_color();
    init_pair(1,COLOR_BLACK, COLOR_CYAN);
    wbkgd(main, COLOR_PAIR(1));
    return main;
}

int finalize_graphic() {
    return endwin();
}

WINDOW *bottom_window() {
    short height = 3;
    WINDOW* panel = subwin(stdscr, height, stdscr->_maxx, stdscr->_maxy - height +1, 0);
    box(panel, ACS_VLINE, ACS_HLINE);
    move(panel->_begy + 1, stdscr->_begx + stdscr->_maxx / 4 - 8);
    printw("[f1 - open file]");
    move(panel->_begy + 1, stdscr->_begx + stdscr->_maxx / 4 * 2 - 8);
    printw("[f2 - save file]");
    move(panel->_begy + 1, stdscr->_begx + stdscr->_maxx / 4 * 3 - 11/2);
    printw("[f3 - exit]");
    wrefresh(panel);
    return panel;
}

void print_name_file(WINDOW* win, const char *name) {
    size_t lenght = strlen(name);
    if(lenght < win->_maxx - 4) {
        move(0, win->_maxx / 2 - (int) lenght / 2);
        printw(" ");
        printw(name);
        printw(" ");
    }
}

WINDOW *text_window(WINDOW* BottomP) {
    WINDOW* text = subwin(stdscr, stdscr->_maxy - BottomP->_maxy, stdscr->_maxx, 0, 0);
    box(text, ACS_VLINE, ACS_HLINE);
    wrefresh(text);
    return text;
}

WINDOW* edit_window(WINDOW* TextWindow) {
    WINDOW* win = subwin(TextWindow, TextWindow->_maxy - 1, TextWindow->_maxx - 1,
                  TextWindow->_begy + 1, TextWindow->_begx + 1);
    wrefresh(win);
    return win;
}

WINDOW* open_file_window(WINDOW* TextWindow) {
    int k = 4;
    int j = 2;
    WINDOW* win = newwin(TextWindow->_maxy / k >= 7 ? TextWindow->_maxy / k : 7,
                         TextWindow->_maxx / j,
                         TextWindow->_maxy / 2 - TextWindow->_maxy / (2 * k),
                         TextWindow->_maxx / 2 - TextWindow->_maxx / (2 * j));
    box(win, ACS_VLINE, ACS_HLINE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    wbkgd(win, COLOR_PAIR(2));
    mvwhline(win, 2, 1, ACS_HLINE, win->_maxx - 1);
    mvwprintw(win,1, win->_maxx / 2 - 8, "Enter file name!");
    WINDOW* sub = subwin(win, 3, win->_maxx - 5, win->_begy + 3, win->_begx + 3);
    box(sub, ACS_VLINE, ACS_HLINE);
    wmove(win, 4, 4);
    refresh();
    return win;
}

PANEL* open_file_panel(WINDOW* OpenFileWindow) {
    return new_panel(OpenFileWindow);
}
