//
// Created by evgenii on 19.11.17.
//

#ifndef MY_MC_CORE_H
#define MY_MC_CORE_H

#include "../graphic/graphic.h"
#include <zconf.h>
#include <sys/types.h>
#include <dirent.h>

#define SELECT_ACTIVE 2
#define RUN 1
#define STOP 0

#define LEFT 0
#define RIGHT 1

typedef struct content_dir content_dir_t;

int core_mc(int argc, char** argv);
int wait_resize();
int display_directory(WINDOW* win, content_dir_t* ContentDir);
content_dir_t* get_content_directory(char *path);
void free_content_dir(content_dir_t* ptr);

#endif //MY_MC_CORE_H
