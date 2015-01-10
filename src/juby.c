#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "juby.h"

Object* juby(Scope* scope, Object* args[], int argc) {
    return args[argc - 1];
}

Object* print(Scope* scope, Object* args[], int argc) {
    int i;
    for (i = 0; i < argc; ++i) {
        print_Object(args[i]);
    }

    if (argc > 0) {
        return args[0];
    }

    return undefined;
}

Object* let(Scope* scope, Object* args[], int argc) {
    if (argc == 0) {
        panic("Cannot let nothing!", ":(");
        return undefined;
    }

    if (argc == 1) {
        Scope__addGarbage(scope, args[0]);
        return args[0];
    }

    Scope__addGarbage(scope, args[0]);
    return set_Property(Object_parent(args[0]), Object_name(args[0]), args[1]);
}

Object* name(Scope* scope, Object* args[], int argc) {
    if (argc == 0) {
        panic("Cannot get the name of nothing!", ":(");
        return undefined;
    } else {
        return new_String(Object_name(args[0]));
    }
}

Object* quit(Scope* scope, Object* args[], int argc) {
    Scope__destroy(scope);
    exit(0);

    return undefined;
}

Scope* Prelude(void) {
    Object* p = new_Object("Globals");
    PreludeFunc(juby);
    PreludeFunc(print);
    PreludeFunc(let);
    PreludeFunc(name);
    PreludeFunc(quit);

    Scope* s = Scope__create(p);
    return s;
}
