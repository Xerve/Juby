#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Boolean.h"

void Prelude__Boolean__init(void) {
    Object__set(t_Boolean, "and", Object__nFunction(Prelude__Boolean__and));
    Object__set(t_Boolean, "or", Object__nFunction(Prelude__Boolean__or));
    Object__set(t_Boolean, "xor", Object__nFunction(Prelude__Boolean__xor));
    Object__set(t_Boolean, "not", Object__nFunction(Prelude__Boolean__not));
}

Object* Prelude__Boolean__and(int argc, Object* argv[]) {
    int i;
    for (i = 0; i < argc; ++i) {
        if (!Object__is(argv[i], t_Boolean)) {
            puts("Cannot 'and' non-Boolean value!");
            return undefined;
        }

        if (!Object__getBoolean(argv[i])) {
            return Object__Boolean(false);
        }
    }

    return Object__Boolean(true);
}

Object* Prelude__Boolean__or(int argc, Object* argv[]) {
    int i;
    for (i = 0; i < argc; ++i) {
        if (!Object__is(argv[i], t_Boolean)) {
            puts("Cannot 'and' non-Boolean value!");
            return undefined;
        }

        if (Object__getBoolean(argv[i])) {
            return Object__Boolean(true);
        }
    }

    return Object__Boolean(false);
}
Object* Prelude__Boolean__xor(int argc, Object* argv[]) {
    if (argc != 2) {
        puts("Can only 'xor' two values!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Boolean) || !Object__is(argv[1], t_Boolean)) {
        puts("Can only 'xor' boolean values!");
        return undefined;
    }

    bool a = Object__getBoolean(argv[0]);
    bool b = Object__getBoolean(argv[1]);

    return Object__Boolean((a || b) && !(a &&b));
}
Object* Prelude__Boolean__not(int argc, Object* argv[]) {
    if (argv == 0) {
        puts("Cannot 'not' nothing!");
        return undefined;
    }

    if (!Object__is(argv[0], t_Boolean)) {
        puts("Can only 'not' boolean values!");
        return undefined;
    }

    return Object__Boolean(!Object__getBoolean(argv[0]));
}
