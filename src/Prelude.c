#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Prelude.h"

Scope* Prelude(void) {
    TYPE__INIT();
    Prelude__init();
    Prelude__Any__init();
    Prelude__Number__init();
    Prelude__Object__init();
    Prelude__Array__init();
    Object* p = Object__Object(t_Prelude);
    Object__set(p, "Any", t_Any);
    Object__set(p, "Undefined", t_Undefined);
    Object__set(p, "String", t_String);
    Object__set(p, "Boolean", t_Boolean);
    Object__set(p, "Number", t_Number);
    Object__set(p, "Function", t_Function);
    Object__set(p, "Prelude", t_Prelude);
    Object__set(p, "Object", t_Object);
    Object__set(p, "Array", t_Array);

    Scope* s = Scope__create(p);
    return s;
}

void Prelude__init(void) {
    Object__set(t_Prelude, "juby", Object__nFunction(Prelude__juby));
    Object__set(t_Prelude, "print", Object__nFunction(Prelude__print));
    Object__set(t_Prelude, "let", Object__nFunction(Prelude__let));
    Object__set(t_Prelude, "exit", Object__nFunction(Prelude__exit));
    Object__set(t_Prelude, "panic", Object__nFunction(Prelude__panic));
    Object__set(t_Prelude, "recover", Object__nFunction(Prelude__recover));
}

Object* Prelude__juby(int argc, Object* argv[]) {
    return argv[argc - 1];
}

Object* Prelude__print(int argc, Object* argv[]) {
    int i;
    for (i = 0; i < argc; ++i) {
        Object__print(argv[i]);
    }

    if (argc > 0) {
        return argv[0];
    }

    return undefined;
}

Object* Prelude__let(int argc, Object* argv[]) {
    if (argc == 0) {
        puts("Cannot let nothing!");
        return undefined;
    }

    if (argc == 1) { return argv[0]; }
    if (argv[0] == undefined) {
        puts("Cannot let on undefined!");
        exit(1);
    }

    Object__set(Object__getParent(argv[0]), Object__getName(argv[0]), Object__copy(argv[1]));
    return argv[1];
}

Object* Prelude__exit(int argc, Object* argv[]) {
    if (argc > 0) {
        if (Object__is(argv[0], t_Number)) { exit(Object__getNumber(argv[0])); }
        else { exit(1); }
    } else {
        exit(1);
    }

    return undefined;
}

bool panic_state = false;
char* panic_message = "Please ignore";

Object* Prelude__panic(int argc, Object* argv[]) {
    panic_state = true;
    if (argc > 0) {
        if (Object__is(argv[0], t_String)) {
            panic_message = Object__getString(argv[0]);
        }
    }

    return undefined;
}

Object* Prelude__recover(int argc, Object* argv[]) {
    panic_state = false;
    return undefined;
}
