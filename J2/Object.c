#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Object.h"

struct _Function {
    bool native;
    union {
        nFunc nf;
        char* uf;
    } value;
};

struct _Object {
    bool native;
    Object* type;
    char* name;
    Object* parent;
    union {
        char* string;
        bool boolean;
        double number;
        Function* function;
        ObjectNode* node;
    } value;
};

Object __undefined = {true, undefined, "undefined", NULL };

Object* t_Any = malloc(sizeof(Object));
    t_Any->native = false;
    t_Any->type = t_Any;
    t_Any->parent = NULL;
    t_Any->name = NULL;
    t_Any->value.node = ObjectNode__create();

Object* t_String = malloc(sizeof(Object));
    t_String->native = false;
    t_String->type = t_Any;
    t_String->name = NULL;
    t_String->parent = NULL;
    t_String->value.node = ObjectNode__create();
    
Object* t_Boolean = malloc(sizeof(Object));
    t_Boolean->native = false;
    t_Boolean->type = t_Any;
    t_Boolean->name = NULL;
    t_Boolean->parent = NULL;
    t_Boolean->value.node = ObjectNode__create();
    
Object* t_Number = malloc(sizeof(Object));
    t_Number->native = false;
    t_Number->type = t_Any;
    t_Number->name = NULL;
    t_Number->parent = NULL;
    t_Number->value.node = ObjectNode__create();
    
Object* t_Function = malloc(sizeof(Object));
    t_Function->native = false;
    t_Function->type = t_Any;
    t_Function->name = NULL;
    t_Function->parent = NULL;
    t_Function->value.node = ObjectNode__create();
    
inline bool Object__is(Object* object, Object* type) { return object->type == type; }

inline char* Object__getName(Object* object) { return object->name; }
inline void Object__setName(Object* object, char* name) { 
    if (object->name) { free(object->name); }
    object->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(object->name, name);
}

inline Object* Object__getParent(Object* object) { return object->parent; }
inline void Object__setParent(Object* object, Object* parent) { object->parent = parent; }

inline char* Object__getString(Object* object) { 
    if (!Object__is(object, t_String)) { puts("Cannot get String of non-String type!"); exit(1); }
    return object->value.string;    
}

inline bool Object__getBoolean(Object* object) {
    if (!Object__is(object, t_String)) { puts("Cannot get Boolean of non-Boolean type!"); exit(1); }
    return object->value.boolean;
}

inline double Object__getNumber(Object* object) {
    if (!Object__is(object, t_Number)) { puts("Cannot get Number of non-Number type!"); exit(1); }
    return object->value.number;
}

Object* Object__String(char* value) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = t_String;
    object->name = NULL;
    object->parent = NULL;
    object->value.string = value;
    return object;
}

Object* Object__Boolean(bool value) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = t_Boolean;
    object->name = NULL;
    object->parent = NULL;
    object->value.boolean = value;
    return object;
}

Object* Object__Number(double value) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = t_Number;
    object->name = NULL;
    object->parent = NULL;
    object->value.number = value;
    return object;
}

Object* Object__uFunction(char* value) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = t_Function;
    object->name = NULL;
    object->parent = NULL;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = false;
    object->value.function->value.uf = value;
    return object;
}

Object* Object__nFunction(nFunc value) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = t_Function;
    object->name = NULL;
    object->parent = NULL;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = true;
    object->value.function->value.nf = value;
    return object;
}

Object* Object__Undefined(void) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->type = undefined;
    object->name = NULL;
    object->parent = NULL;
    return object;
}

Object* Object__Object(Object* type) {
    Object* object = malloc(sizeof(Object));
    object->native = false;
    object->type = type;
    object->name = NULL;
    object->parent = NULL;
    return object;
}

void Object__delete(Object* object) {
    if (!object) { return undefined; }

    if (object != undefined) {
        if (!object->native) {
            free(object->type);
            ObjectNode__delete(object->value.node);
        } else if (Object__is(object, t_String)) {
            free(object->value.string);
        } else if (Object_is(object, t_Function)) {
            if (!object->value.function->native) {
                free(object->value.function->value.uf);
            }

            free(object->value.function);
        }

        free(object);
    }
}
