//
// Created by evgenii on 19.11.17.
//

#ifndef MY_MC_GRAPHIC_H
#define MY_MC_GRAPHIC_H

#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>

WINDOW* InitGraphic();
int FinalizeGraphic();
WINDOW* GetMainWindow(WINDOW* Main);
WINDOW* GetLeftWindow(WINDOW* Main, char* path);
WINDOW* GetRightWindow(WINDOW* Main, char* path);
WINDOW* GetBottomWindow(WINDOW* Main);
WINDOW* GetActiveArea(WINDOW *Win);
void SelectActive(PANEL** PanelRow, int i);
PANEL* GetPanelRow(WINDOW* Win, int row, struct dirent* name);


#endif //MY_MC_GRAPHIC_H
