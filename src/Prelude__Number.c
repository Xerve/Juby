#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Number.h"

void Prelude__Number__init(void) {
    Object__set(t_Number, "+", Object__nFunction(Number__add));
    Object__set(t_Number, "-", Object__nFunction(Number__sub));
    Object__set(t_Number, "*", Object__nFunction(Number__mul));
    Object__set(t_Number, "/", Object__nFunction(Number__div));
}

Object* Number__add(int argc, Object* argv[]) {
    if (argc < 2) {
        puts("Cannot add less than two numbers!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Number)) {
        puts("Cannot add non-Number at position 0");
        return undefined;
    }

    double ret = Object__getNumber(argv[0]);

    int i;
    for(i = 1; i < argc; ++i) {
        if (Object__is(argv[i], t_Number)) {
            ret += Object__getNumber(argv[i]);
        } else {
            printf("Cannot add non-Number at position %d\n", i);
            return undefined;
        }
    }

    return Object__Number(ret);
}
Object* Number__sub(int argc, Object* argv[]) {
    if (argc < 2) {
        puts("Cannot subtract less than two numbers!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Number)) {
        puts("Cannot subtract non-Number at position 0");
        return undefined;
    }

    double ret = Object__getNumber(argv[0]);

    int i;
    for(i = 1; i < argc; ++i) {
        if (Object__is(argv[i], t_Number)) {
            ret -= Object__getNumber(argv[i]);
        } else {
            printf("Cannot subtract non-Number at position %d\n", i);
            return undefined;
        }
    }

    return Object__Number(ret);
}

Object* Number__mul(int argc, Object* argv[]) {
    if (argc < 2) {
        puts("Cannot multiply less than two numbers!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Number)) {
        puts("Cannot multiply non-Number at position 0");
        return undefined;
    }

    double ret = Object__getNumber(argv[0]);

    int i;
    for(i = 1; i < argc; ++i) {
        if (Object__is(argv[i], t_Number)) {
            ret *= Object__getNumber(argv[i]);
        } else {
            printf("Cannot multiply non-Number at position %d\n", i);
            return undefined;
        }
    }

    return Object__Number(ret);
}

Object* Number__div(int argc, Object* argv[]) {
    if (argc < 2) {
        puts("Cannot divide less than two numbers!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Number)) {
        puts("Cannot add non-Number at position 0");
        return undefined;
    }

    double ret = Object__getNumber(argv[0]);

    int i;
    for(i = 1; i < argc; ++i) {
        if (Object__is(argv[i], t_Number)) {
            ret /= Object__getNumber(argv[i]);
        } else {
            printf("Cannot divide non-Number at position %d\n", i);
            return undefined;
        }
    }

    return Object__Number(ret);
}
