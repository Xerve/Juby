#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Any.h"

void Prelude__Any__init(void) {
    Object__set(t_Any, "name", Object__nFunction(Any__name));
    Object__set(t_Any, "type", Object__nFunction(Any__type));
    Object__set(t_Any, "parent", Object__nFunction(Any__parent));
}

Object* Any__name(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get the name of nothing!");
        return undefined;
    } else {
        return Object__String(Object__getName(argv[0]));
    }
}

Object* Any__type(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get type of nothing!");
        return undefined;
    } else {
        return Object__getType(argv[0]);
    }
}

Object* Any__parent(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get parent of nothing!");
        return undefined;
    } else {
        return Object__getParent(argv[0]);
    }
}

