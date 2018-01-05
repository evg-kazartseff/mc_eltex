//
// Created by evgenii on 10.11.17.
//

#include "core.h"

typedef struct _PANEL_DATA {
    int hide;
} PANEL_DATA;

int core_te(int argc, char **argv) {
    init_graphic();
    cbreak();
    int maxx = getmaxx(stdscr);
    int maxy = getmaxy(stdscr);
    if ((maxx < 50) || (maxy < 6)) {
        dprintf(STDERR_FILENO, "Error: Can't create window!");
        return 1;
    }
    WINDOW* BottomPanel = bottom_window();
    WINDOW* TextWindow = text_window(BottomPanel);
    WINDOW* EditWindow = edit_window(TextWindow);
    FILE* file;
    char* text = NULL;
    char *name = NULL;
    if (argc == 2) {
        file = fopen(argv[1], "r");
        print_name_file(TextWindow, argv[1]);
        name = argv[1];
        text = read_file(file);
        fclose(file);
        move(1, 1);
        wprintw(EditWindow, text);
    }
    refresh();

    int key;
    volatile int x, y;
    noecho();
    keypad(stdscr, TRUE);
    wmove(EditWindow, 0, 0);
    WINDOW* OpenFW;
    PANEL* OpenFP;
    OpenFW = open_file_window(EditWindow);
    OpenFP = open_file_panel(OpenFW);
    hide_panel(OpenFP);
    update_panels();
    doupdate();
    PANEL_DATA panel_data;
    PANEL_DATA *temp;
    panel_data.hide = TRUE;
    set_panel_userptr(OpenFP, &panel_data);
    do {
        x = getcurx(EditWindow);
        y = getcury(EditWindow);
        key = getch();
        switch (key) {
            case KEY_F(1):
                temp = (PANEL_DATA *)panel_userptr(OpenFP);
                if(temp->hide == FALSE) {
                    hide_panel(OpenFP);
                    temp->hide = TRUE;
                }
                else {
                    show_panel(OpenFP);
                    temp->hide = FALSE;
                }
                break;
            case KEY_UP:
                move_up(EditWindow, &x, &y);
                break;
            case KEY_DOWN:
                move_down(EditWindow, &x, &y);
                break;
            case KEY_LEFT:
                move_left(EditWindow, &x, &y);
                break;
            case KEY_RIGHT:
                move_rigt(EditWindow, &x, &y);
                break;
            case KEY_F(2):
                if (text != NULL)
                    free(text);
                if (name != NULL) {
                    unsigned int xmax = (unsigned int) getmaxx(EditWindow);
                    unsigned int ymax = (unsigned int) getmaxy(EditWindow);
                    text = calloc((xmax * ymax), sizeof(char));
                    mvwinstr(EditWindow, 0, 0, text);
                    FILE* wr = fopen(name, "w");
                    fprintf(wr, "%s", text);
                    fflush(wr);
                    fclose(wr);
                }
                break;
            case KEY_F(3):
                if (text != NULL)
                    free(text);
                break;
            case KEY_BACKSPACE:
                if (x != 0) {
                    move_left(EditWindow, &x, &y);
                    wdelch(EditWindow);
                }
                break;
            case KEY_DC:
                wdelch(EditWindow);
                break;
            case 10:
                move_new_line(EditWindow, &x, &y);
                break;
            default:
                if(print_symbol(key)) {
                    wprintw(EditWindow, "%c", key);
                    move_rigt(EditWindow, &x, &y);
                }
                break;
        }
        wmove(EditWindow, y, x);
        wrefresh(EditWindow);
        if (key == KEY_F(1)) {
            update_panels();
            doupdate();
            if (panel_data.hide == FALSE) {
                name = get_name_file(OpenFW);
                hide_panel(OpenFP);
                panel_data.hide = TRUE;
                file = fopen(name, "r");
                if (file != NULL) {
                    print_name_file(TextWindow, name);
                    text = read_file(file);
                    fclose(file);
                    mvwprintw(EditWindow, 0, 0, text);
                    wrefresh(EditWindow);
                }
                else {
                    move(EditWindow->_maxy, EditWindow->_maxx / 2 - 8);
                    print_name_file(TextWindow, "Can't open file");
                }
            }
        }
    } while (key != KEY_F(3));
    finalize_graphic();
}

void move_up(WINDOW* Win, const volatile int* x, volatile int* y) {
    wmove(Win, (*y) -= 1, *x);
}

void move_down(WINDOW* Win, const volatile int* x, volatile int* y) {
    wmove(Win, (*y) += 1, *x);
}

void move_left(WINDOW* Win, volatile int* x, volatile const int* y) {
    *x = *x - 1;
    wmove(Win, *y, *x);
}

void move_rigt(WINDOW* Win, volatile int* x, volatile const int* y) {
    wmove(Win, *y, (*x) += 1);
}

void move_new_line(WINDOW* Win, volatile int* x, volatile int* y) {
    *x = 0;
    wmove(Win, (*y) += 1, *x);
}

bool print_symbol(int key) {
    if (key >= 32 && key <= 126)
        return true;
    return false;
}

char* get_name_file(WINDOW* win) {
    char *name = calloc(256, sizeof(char));
    echo();
    mvwgetstr(win, 4, 4, name);
    noecho();
    return name;
}
