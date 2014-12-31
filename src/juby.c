#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "juby.h"

Object* test(Scope* scope, Object* args[], int argc) {
    return new_Number(9.0);
}

Object* let(Scope* scope, Object* args[], int argc) {
    if (argc == 0) {
        panic("Cannot let nothing!", ":(");
        return undefined;
    }

    if (argc == 1) {
        add_Garbage(scope, args[0]);
        return args[0];
    }

    add_Garbage(scope, args[0]);
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
    destroy_Scope(scope);
    exit(0);

    return undefined;
}

Scope* Prelude(void) {
    Object* p = new_Object("Globals");
    PreludeFunc(test);
    PreludeFunc(let);
    PreludeFunc(name);
    PreludeFunc(quit);

    Scope* s = create_Scope(p);
    return s;
}
