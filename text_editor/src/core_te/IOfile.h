//
// Created by evgenii on 10.11.17.
//

#ifndef TEXT_EDITOR_FILE_IO_H
#define TEXT_EDITOR_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

FILE* open_file(const char* filename);
char* read_file(FILE* file);


#endif //TEXT_EDITOR_FILE_IO_H
