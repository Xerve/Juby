#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude.h"

Object* juby(int argc, Object* argv[]) {
    return argv[argc - 1];
}

Object* print(int argc, Object* argv[]) {
    int i;
    for (i = 0; i < argc; ++i) {
        Object__print(argv[i]);
    }

    if (argc > 0) {
        return argv[0];
    }

    return undefined;
}

Object* let(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot let nothing!");
        return undefined;
    }

    if (argc == 1) {
        return argv[0];
    }

    Object__set(Object__getParent(argv[0]), Object__getName(argv[0]), argv[1]);
    return argv[0];
}

Object* name(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot get the name of nothing!");
        return undefined;
    } else {
        return Object__String(Object__getName(argv[0]));
    }
}

Object* quit(int argc, Object* argv[]) {
    exit(0);

    return undefined;
}

Scope* Prelude(void) {
    TYPE__INIT();
    Object* p = Object__Object(t_Any);
    Object__set(p, "Any", t_Any);
    Object__set(p, "String", t_String);
    Object__set(p, "Boolean", t_String);
    Object__set(p, "Number", t_String);
    Object__set(p, "Function", t_String);
    PreludeFunc(juby);
    PreludeFunc(print);
    PreludeFunc(let);
    PreludeFunc(name);
    PreludeFunc(quit);

    Scope* s = Scope__create(p);
    return s;
}
