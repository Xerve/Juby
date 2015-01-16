#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Array.h"

void Prelude__Array__init(void) {
    Object__set(t_Array, "Array", Object__nFunction(Prelude__Array__Array));
    Object__set(t_Array, "get", Object__nFunction(Prelude__Array__get));
    Object__set(t_Array, "push", Object__nFunction(Prelude__Array__push));
    // Object__set(t_Array, "pop", Object__nFunction(Array__pop));
}

Object* Prelude__Array__Array(int argc, Object* argv[]) {
    Object* ret = Object__Object(t_Array);
    Object__set(ret, "length", Object__Number(argc));

    int i;
    char buffer[20];
    for (i = 0; i < argc; ++i) {
        sprintf(buffer, "%d", i);
        Object__set(ret, buffer, Object__copy(argv[i]));
    }

    return ret;
}

Object* Prelude__Array__get(int argc, Object* argv[]) {
    if (argc < 2) { return undefined; }

    if (!Object__is(argv[0], t_Array)) {
        puts("Cannot Array#get from non-Array!");
        exit(1);
    }

    if (!Object__is(argv[1], t_Number)) {
        puts("Cannot get non-Number from Array!");
        exit(1);
    }

    char buffer[20];
    sprintf(buffer, "%.0f", Object__getNumber(argv[1]));
    return Object__get(argv[0], buffer);
}

Object* Prelude__Array__push(int argc, Object* argv[]) {
    if (argc < 2) { return undefined; }

    if (!Object__is(argv[0], t_Array)) {
        puts("Cannot Array#push to non-Array!");
        exit(1);
    }

    char buffer[20];
    double length = Object__getNumber(Object__get(argv[0], "length"));
    sprintf(buffer, "%.0f", length);
    Object__unset(argv[0], "length");
    Object__set(argv[0], "length", Object__Number(length + 1));
    Object__set(argv[0], buffer, Object__copy(argv[1]));

    return argv[0];
}

// Object* Array__pop(int argc, Object* argv[]);
