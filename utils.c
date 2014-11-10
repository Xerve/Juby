#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

bool _panic = false;
static char* _panic_message = "Please";
static char* _panic_arg = "ignore";

inline void panic(char* message, char* arg) {
    _panic = true;
    _panic_message = message;
    _panic_arg = arg;
}

inline void recover(bool verbose) {
    if (_panic) {
        _panic = false;
        if (verbose) {
            puts(_panic_message);
            puts(_panic_arg);
        }
    }
}
