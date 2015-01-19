#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude__Object.h"

void Prelude__Object__init(void) {
    Object__set(t_Object, "Object", Object__nFunction(Prelude__Object__Object));
}


Object* Prelude__Object__Object(int argc, Object* argv[]) {
    if (argc == 0) { return Object__Object(t_Object); }
    if (argc == 1) { return Object__Object(argv[0]); }

    if (argc % 2 == 0) {
        Object* ret = Object__Object(t_Object);
        int i;
        for (i = 0; i < argc; i += 2) {
            if (!Object__is(argv[i], t_String)) {
                puts("Cannot set non-string value on object!");
                exit(1);
            }

            Object__set(ret, Object__getString(argv[i]), Object__copy(argv[i + 1]));
        }

        return ret;
    } else {
        if (Object__is(argv[0], t_String) ||
            Object__is(argv[0], t_Boolean) ||
            Object__is(argv[0], t_Number) ||
            Object__is(argv[0], t_Undefined) ||
            Object__is(argv[0], t_Function)) {
                puts("Cannot inherit from native type!");
                exit(1);
        }

        Object* ret = Object__Object(argv[0]);
        int i;
        for (i = 1; i < argc; i += 2) {
            if (!Object__is(argv[i], t_String)) {
                puts("Cannot set non-string value on object!");
                exit(1);
            }

            Object__set(ret, Object__getString(argv[i]), Object__copy(argv[i + 1]));
        }

        return ret;
    }
}
