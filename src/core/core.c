//
// Created by evgenii on 19.11.17.
//
#include "core.h"

struct content_dir {
    struct dirent** content;
    int size;
};

int core_mc(int argc, char** argv) {
    char dir_path[2][FILENAME_MAX];
    getcwd(dir_path[LEFT], FILENAME_MAX);
    getcwd(dir_path[RIGHT], FILENAME_MAX);
    WINDOW* Main = InitGraphic();
    WINDOW* Left;
    WINDOW* Right;
    WINDOW* Bottom;
    WINDOW* active[2];
    PANEL* PanelRow[2];
    content_dir_t* ContentDir[2] = {NULL, NULL};
    int maxx;
    int maxy;
    int flg = RUN;
    int i = 0;
    int row[2] = {0, 0};
    do {
        maxx = getmaxx(stdscr);
        maxy = getmaxy(stdscr);
        if ((maxx < 50) || (maxy < 8)) {
            clear();
            refresh();
            printw("Error: Can't create window!");
            wait_resize();
        }
        clear();
        Main = GetMainWindow(Main);
        Left = GetLeftWindow(Main, dir_path[LEFT]);
        Right = GetRightWindow(Main, dir_path[RIGHT]);
        Bottom = GetBottomWindow(Main);
        active[LEFT] = GetActiveArea(Left);
        active[RIGHT] = GetActiveArea(Right);
        free_content_dir(ContentDir[LEFT]);
        free_content_dir(ContentDir[RIGHT]);
        ContentDir[LEFT] = get_content_directory(dir_path[LEFT]);
        ContentDir[RIGHT] = get_content_directory(dir_path[RIGHT]);
        PanelRow[LEFT] = GetPanelRow(active[LEFT], row[LEFT], ContentDir[LEFT]->content[row[LEFT]]);
        PanelRow[RIGHT] = GetPanelRow(active[RIGHT], row[RIGHT], ContentDir[RIGHT]->content[row[RIGHT]]);
        display_directory(active[LEFT], ContentDir[LEFT]);
        display_directory(active[RIGHT], ContentDir[RIGHT]);
        if (flg == SELECT_ACTIVE) {
            i ^= 1;
        }
        SelectActive(PanelRow, i);
        refresh();
        keypad(stdscr, TRUE);
        switch (getch()) {
            case KEY_F(10):
                flg = STOP;
                break;
            case 9:
                flg = SELECT_ACTIVE;
                break;
            case KEY_UP:
                if (row[i] != 0)
                   row[i]--;
                break;
            case KEY_DOWN:
                if (ContentDir[i] != NULL) {
                    if (row[i] != ContentDir[i]->size - 1)
                        row[i]++;
                }
                break;
            case 10:
                /*strcpy(ContentDir[i]->content[row[i]]->d_name, dir_path[i]);
                move(20, 20);
                printw(ContentDir[i]->content[row[i]]->d_name);
                getch();*/
                break;
            default:
                flg = RUN;
                break;
        }
        keypad(stdscr, FALSE);
    } while(flg);
    free_content_dir(ContentDir[LEFT]);
    free_content_dir(ContentDir[RIGHT]);
    FinalizeGraphic();
    return 0;
}

int wait_resize() {
    int maxx;
    int maxy;
    do {
        refresh();
        maxx = getmaxx(stdscr);
        maxy = getmaxy(stdscr);
        sleep(100);
    } while ((maxx < 50) || (maxy < 8));
    return 0;
}

int display_directory(WINDOW* win, content_dir_t* ContentDir) {
    for (int i = 0; i < ContentDir->size; i++) {
        if (ContentDir->content[i]->d_type == DT_DIR)
            wprintw(win, "/%s\n", ContentDir->content[i]->d_name);
        else
            wprintw(win, " %s\n", ContentDir->content[i]->d_name);
    };
    wrefresh(win);
    return 0;
}

content_dir_t* get_content_directory(char* path) {
    struct content_dir* result = malloc(sizeof(struct content_dir));
    struct dirent** content;
    int n = scandir(path, &content, 0, alphasort);
    result->size = n;
    result->content = content;
    return result;
}

void free_content_dir(content_dir_t* ptr) {
    if (ptr) {
        if (ptr->content) {
            for (int i = 0; i < ptr->size; i++)
                free(ptr->content[i]);
        }
        free(ptr->content);
        free(ptr);
    }
}
