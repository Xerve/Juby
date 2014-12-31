#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Scope.h"

struct _Scope {
    Object* context;
    Object** gc;
    int garbage;
    int capacity;
};

Scope* create_Scope(Object* context) {
    Scope* scope = malloc(sizeof(Scope));
    scope->context = context;
    scope->gc = malloc(sizeof(Object*) * 10);
    scope->garbage = 0;
    scope->capacity = 10;

    return scope;
}

void add_Garbage(Scope* scope, Object* value) {
    // if (scope->garbage == scope->capacity) {
    //     scope->capacity += 5;
    //     scope->gc = realloc(scope->gc, sizeof(Object*) * scope->garbage);
    // }
    //
    // scope->gc[scope->garbage] = value;
    scope->garbage++;
}

Object* get_Variable(Scope* scope, char* name) {
    if (!strcmp(name, "self")) {
        return scope->context;
    }
    const char split[2] = ".";
    char* token = strtok(name, split);
    Object* curr = scope->context;

    while (token != NULL) {
        curr = get_Property(curr, token);
        token = strtok(NULL, split);
    }

    return curr;
}

void collect_Garbage(Scope* scope) {
    int i;
    for (i = 0; i < scope->garbage; ++i) {
        delete_Property(Object_parent(scope->gc[i]), Object_name(scope->gc[i]));
    }

    scope->garbage = 0;
}

Object* delete_Scope(Scope* scope) {
    free(scope->gc);
    Object* context = scope->context;
    free(scope);

    return context;
}

void destroy_Scope(Scope* scope) {
    Object* context = delete_Scope(scope);
    delete_Object(context);
}
