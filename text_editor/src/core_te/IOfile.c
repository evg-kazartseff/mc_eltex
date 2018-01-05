//
// Created by evgenii on 10.11.17.
//

#include "IOfile.h"

FILE* open_file(const char *filename) {
    return fopen(filename, "w+t");
}

char *read_file(FILE *file) {
    if (!file)
        return NULL;
    size_t buf = 64;
    size_t readed = 0;
    char *output = calloc(buf, sizeof(char));
    while (!feof(file)) {
        if (readed == buf) {
            buf += 64;
            output = realloc(output, buf);
        }
        output[readed] = (char) fgetc(file);
        readed++;
    }
    output[readed - 1] = '\000';
    return output;
}
