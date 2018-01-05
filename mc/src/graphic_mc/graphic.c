//
// Created by evgenii on 19.11.17.
//
#include <dirent.h>
#include "graphic.h"

WINDOW* InitGraphic() {
    WINDOW* main = initscr();
    return main;
}

int FinalizeGraphic() {
    clear();
    return endwin();
}

WINDOW* GetMainWindow(WINDOW* Main) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    wbkgd(Main, COLOR_PAIR(1));
    wrefresh(Main);
    return Main;
}

WINDOW* GetLeftWindow(WINDOW* Main, char* path) {
    WINDOW* win = subwin(Main, Main->_maxy  - 4, Main->_maxx / 2, 0 ,0);
    wbkgd(win, COLOR_PAIR(1));
    box(win, ACS_VLINE, ACS_HLINE);
    mvwprintw(win, 0, win->_maxx / 2 - (int) strlen(path) / 2, path);
    wrefresh(win);
    return win;
}

WINDOW* GetRightWindow(WINDOW* Main, char* path) {
    WINDOW* win = subwin(Main, Main->_maxy - 4, Main->_maxx / 2, 0, Main->_maxx / 2);
    wbkgd(win, COLOR_PAIR(1));
    box(win, ACS_VLINE, ACS_HLINE);
    mvwprintw(win, 0, win->_maxx / 2 - (int) strlen(path) / 2, path);
    wrefresh(win);
    return win;
}

WINDOW* GetBottomWindow(WINDOW* Main) {
    WINDOW* win = subwin(Main, 5, Main->_maxx, Main->_maxy - 4, 0);
    wbkgd(win, COLOR_PAIR(1));
    box(win, ACS_VLINE, ACS_HLINE);
    WINDOW* button1 = subwin(win, 3, 15, win->_begy + 1, 2);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);
    wbkgd(button1, COLOR_PAIR(2));
    box(button1, ACS_VLINE, ACS_HLINE);
    mvwprintw(button1, 1, button1->_maxx / 2 - 3, "1 open");
    wrefresh(win);
    return win;
}

WINDOW* GetActiveArea(WINDOW* Win) {
    WINDOW* win = subwin(Win, Win->_maxy - 1, Win->_maxx - 1, Win->_begy + 1, Win->_begx + 1);
    wrefresh(win);
    return win;
}

void SelectActive(PANEL** PanelRow, int i) {
    if (i == 0) {
        show_panel(PanelRow[0]);
        hide_panel(PanelRow[1]);
    }
    else {
        show_panel(PanelRow[1]);
        hide_panel(PanelRow[0]);
    }
    update_panels();
    doupdate();
}

PANEL* GetPanelRow(WINDOW* Win, int row, struct dirent* name) {
    WINDOW* RowWindow = newwin(1, Win->_maxx, Win->_begy + row, Win->_begx);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    wbkgd(RowWindow, COLOR_PAIR(3));
    if (name->d_type == DT_DIR)
        wprintw(RowWindow, "/%s\n", name->d_name);
    else
        wprintw(RowWindow, " %s\n", name->d_name);
    wrefresh(RowWindow);
    PANEL* panel = new_panel(RowWindow);
    hide_panel(panel);
    update_panels();
    doupdate();
    return panel;
}

