#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Any.h"

void Prelude__Any__init(void) {
    Object__set(t_Any, "name", Object__nFunction(Prelude__Any__name));
    Object__set(t_Any, "type", Object__nFunction(Prelude__Any__type));
    Object__set(t_Any, "parent", Object__nFunction(Prelude__Any__parent));
    Object__set(t_Any, "is", Object__nFunction(Prelude__Any__is));
    Object__set(t_Any, "has", Object__nFunction(Prelude__Any__has));
    Object__set(t_Any, "==", Object__nFunction(Prelude__Any__equals));
}

Object* Prelude__Any__name(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get the name of nothing!");
        return undefined;
    } else {
        return Object__String(Object__getName(argv[0]));
    }
}

Object* Prelude__Any__type(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get type of nothing!");
        return undefined;
    } else {
        return Object__getType(argv[0]);
    }
}

Object* Prelude__Any__parent(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get parent of nothing!");
        return undefined;
    } else {
        return Object__getParent(argv[0]);
    }
}

Object* Prelude__Any__is(int argc, Object* argv[]) {
    if (argc != 2) {
        puts("Cannot compare type of nothing!");
        return undefined;
    } else {
        return Object__Boolean(Object__is(argv[0], argv[1]));
    }
}

Object* Prelude__Any__has(int argc, Object* argv[]) {
    if (argc != 2) {
        puts("Cannot 'has' less than two args!");
        return undefined;
    } else {
        if (!Object__is(argv[1], t_String)) {
            puts("Can only 'has' on Strings!");
            return undefined;
        } else {
            return Object__Boolean(Object__hasWithType(argv[0], Object__getString(argv[1])));
        }
    }
}

Object* Prelude__Any__equals(int argc, Object* argv[]) {
    if (argc != 2) {
        puts("Cannot compare not two values!");
        return undefined;
    } else {
        return Object__Boolean(Object__equals(argv[0], argv[1]));
    }
}

