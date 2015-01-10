#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Scope.h"

struct _Scope {
    Object* context;
    // Object** gc;
    // int garbage;
    // int capacity;
};

Scope* Scope__create(Object* context) {
    Scope* scope = malloc(sizeof(Scope));
    scope->context = context;
//    scope->gc = malloc(sizeof(Object*) * 10);
//    scope->garbage = 0;
//    scope->capacity = 10;

    return scope;
}

//Object* Scope__addGarbage(Scope* scope, Object* value) {
//    if (scope->garbage == scope->capacity) {
//        scope->capacity += 5;
//        scope->gc = realloc(scope->gc, sizeof(Object*) * scope->garbage);
//    }
//
//    int i = scope->garbage;
//    while (scope->gc[i] != NULL) {
//        ++i;
//    }
//
//    scope->gc[i] = value;
//    scope->garbage = i + 1;
//
//    return value;
//}

Object* Scope__getVariable(Scope* scope, char* name) {
    if (!strcmp(name, "self")) {
        return scope->context;
    }
    const char split[2] = ".";
    char* token = strtok(name, split);
    Object* curr = scope->context;

    while (token != NULL) {
        curr = Object__get(curr, token);
        token = strtok(NULL, split);
    }

    return curr;
}

//void print_GC(Scope* scope) {
//    int i;
//    printf("[");
//    for (i = 0; i < scope->capacity; ++i) {
//        if (scope->gc[i] == NULL) {
//            printf("NULL ");
//        } else {
//            printf("<$%p> ", scope->gc[i]);
//        }
//    }
//    printf("]");
//}
//
//void Scope__collectGarbage(Scope* scope, bool all) {
//    print_GC(scope);
//    int i;
//    for (i = 0; i < scope->garbage; ++i) {
//        if (scope->gc[i] != NULL) {
//            if (all || Object_parent(scope->gc[i]) == NULL || Object_parent(scope->gc[i]) == undefined) {
//                delete_Property(Object_parent(scope->gc[i]), Object_name(scope->gc[i]));
//                scope->gc[i] = NULL;
//            }
//        }
//    }
//
//    scope->garbage = 0;
//}

Object* Scope__delete(Scope* scope) {
    //Scope__collectGarbage(scope, true);
    // free(scope->gc);
    Object* context = scope->context;
    free(scope);

    return context;
}

void Scope__destroy(Scope* scope) {
    Object* context = Scope__delete(scope);
    Object__delete(context);
}
