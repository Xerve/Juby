#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    bool gc;
    bool stack;
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

STACK_OBJECT_INIT(t_Any);
STACK_OBJECT_INIT(t_Undefined);
STACK_OBJECT_INHERITS(undefined, t_Undefined);
STACK_OBJECT_INIT(t_String);
STACK_OBJECT_INIT(t_Boolean);
STACK_OBJECT_INIT(t_Number);
STACK_OBJECT_INIT(t_Function);
STACK_OBJECT_INIT(t_Prelude);
STACK_OBJECT_INIT(t_Object);
STACK_OBJECT_INIT(t_Array);

void TYPE__INIT(void) {
    STACK_OBJECT_RT(undefined);
    STACK_OBJECT_RT(t_Any);
    STACK_OBJECT_RT(t_Undefined);
    STACK_OBJECT_RT(t_String);
    STACK_OBJECT_RT(t_Boolean);
    STACK_OBJECT_RT(t_Number);
    STACK_OBJECT_RT(t_Function);
    STACK_OBJECT_RT(t_Prelude);
    STACK_OBJECT_RT(t_Object);
    STACK_OBJECT_RT(t_Array);
}

 char* Object__getName(Object* object) { return object->name; }
 void Object__setName(Object* object, char* name) {
    if (object->name) { free(object->name); }
    object->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(object->name, name);
}

 Object* Object__getParent(Object* object) { return object->parent; }
 void Object__setParent(Object* object, Object* parent) { object->parent = parent; }

 Object* Object__getType(Object* object) { return object->type; }
 void Object__setType(Object* object, Object* type) { object->type = type; }

 bool Object__getGC(Object* object) { return object->gc; }
 void Object__setGC(Object* object, bool gc) { object->gc = gc; }

 char* Object__getString(Object* object) {
    if (!Object__is(object, t_String)) { puts("Cannot get String of non-String type!"); exit(1); }
    return object->value.string;
}

 bool Object__getBoolean(Object* object) {
    if (!Object__is(object, t_Boolean)) { puts("Cannot get Boolean of non-Boolean type!"); exit(1); }
    return object->value.boolean;
}

 double Object__getNumber(Object* object) {
    if (!Object__is(object, t_Number)) { puts("Cannot get Number of non-Number type!"); exit(1); }
    return object->value.number;
}

Object* Object__create(void) {
    Object* object = malloc(sizeof(Object));
    object->native = true;
    object->gc = false;
    object->stack = false;
    object->name = NULL;
    object->parent = NULL;

    return object;
}

Object* Object__String(char* value) {
    Object* object = Object__create();
    object->type = t_String;
    object->value.string = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(object->value.string, value);

    int len = strlen(value);
    int i;
    for (i = 0; i < len; ++i) {
        if (object->value.string[i] == '\\' && i != len - 1 && object->value.string[i + 1] == 'n') {
            object->value.string[i] = ' ';
            object->value.string[i + 1] = '\n';
        }
    }

    return object;
}

Object* Object__Boolean(bool value) {
    Object* object = Object__create();
    object->type = t_Boolean;
    object->value.boolean = value;
    return object;
}

Object* Object__Number(double value) {
    Object* object = Object__create();
    object->type = t_Number;
    object->value.number = value;
    return object;
}

Object* Object__uFunction(char* value) {
    Object* object = Object__create();
    object->type = t_Function;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = false;
    object->value.function->value.uf = malloc(sizeof((strlen(value) + 1) * sizeof(char)));
    return object;
}

Object* Object__nFunction(nFunc value) {
    Object* object = Object__create();
    object->type = t_Function;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = true;
    object->value.function->value.nf = value;
    return object;
}

Object* Object__Undefined(void) {
    Object* object = Object__create();
    object->type = t_Undefined;
    object->value.node = NULL;
    return object;
}

Object* Object__Object(Object* type) {
    Object* object = malloc(sizeof(Object));
    object->native = false;
    object->gc = false;
    object->stack = false;
    object->type = type;
    object->name = NULL;
    object->parent = NULL;
    object->value.node = ObjectNode__create();
    return object;
}

void Object__delete(Object* object) {
    if (!object) { return; }

    if (!object->native) {
        ObjectNode__delete(object->value.node);
    } else if (Object__is(object, t_String)) {
        free(object->value.string);
    } else if (Object__is(object, t_Function)) {
        if (!object->value.function->native) {
            free(object->value.function->value.uf);
        }

        free(object->value.function);
    }

    if (object->name) { free(object->name); }
    if (!object->stack) { free(object); }
}

Object* Object__copy(Object* object) {
    if (!object) { return NULL; }
    if (object->native) {
        if (object->type == t_Number) {
            return Object__Number(object->value.number);
        } else if (object->type == t_Boolean) {
            return Object__Boolean(object->value.boolean);
        } else if (object->type == t_String) {
            return Object__String(object->value.string);
        } else if (object->type == t_Undefined) {
            return Object__Undefined();
        } else if (object->type == t_Function) {
            if (object->value.function->native) {
                return Object__nFunction(object->value.function->value.nf);
            } else {
                return Object__uFunction(object->value.function->value.uf);
            }
        } else {
            return undefined;
        }
    } else {
        Object* n = malloc(sizeof(Object));
        n->native = false;
        n->type = object->type;
        n->name = NULL;
        n->parent = NULL;
        n->value.node = ObjectNode__copy(object->value.node);

        return n;
    }
}

bool Object__is(Object* object, Object* type) {
    if (!object) { return false; }
    if (object->type == t_Any) {
        return type == t_Any;
    } else if (object->type == type) {
        return true;
    } else {
        return Object__is(object->type, type);
    }
}

void Object__set(Object* object, char* value, Object* attr) {
    if (!object) { puts("Cannot set property of empty object!"); exit(1); }
    if (!value) { puts("Cannot set empty key on object!"); exit(1); }
    if (!attr) { puts("Cannot set NULL object on object!"); exit(1); }
    if (object->native) { puts("Cannot set on native object!"); exit(1); }
    if (Object__has(object, value)) { Object__unset(object, value); }

    attr->name = malloc((strlen(value) + 1) * sizeof(char));
    attr->gc = true;
    strcpy(attr->name, value);
    ObjectNode__set(object->value.node, value, attr);
    attr->parent = object;
}

void Object__unset(Object* object, char* value) {
    if (!object) { return; }
    if (!value) { return; }
    if (object->native) { return; }
    Object__delete(Object__get(object, value));
    ObjectNode__set(object->value.node, value, undefined);
}

bool Object__has(Object* object, char* value) {
    if (object == NULL) { return false; }
    if (!value) { return false; }

    if (!object->native) {
        Object* ret = ObjectNode__get(object->value.node, value);

        if (!ret) { return false; }
        else if (ret == undefined) { return false; }
        else { return true; }
    } else {
        return false;
    }
}

bool Object__hasWithType(Object* object, char* value) {
    if (!object) { return false; }
    if (!value) { return false; }

    if (!object->native) {
        Object* ret = ObjectNode__get(object->value.node, value);

        if (!ret && ret != undefined) {
                if (object == t_Any) {
                    return false;
                } else {
                    return Object__hasWithType(object->type, value);
                }
        } else { return true; }
    } else {
        return Object__hasWithType(object->type, value);
    }
}

Object* Object__getFromType(Object* object, char* value) {
    if (object == t_Any || object == undefined) { return NULL; }
    Object* ret = ObjectNode__get(object->type->value.node, value);
    if (!ret) { return Object__getFromType(object->type, value); }
    else { return ret; }
}

Object* Object__get(Object* object, char* value) {
    if (!object) { puts("Cannot get property of empty object!"); exit(1); }
    if (!value) { puts("Cannot get empty key on object!"); exit(1); }

    if (!object->native) {
        Object* ret = ObjectNode__get(object->value.node, value);

        if (!ret) {
            if (object->type) {
                ret = Object__getFromType(object, value);
                if (!ret) {
                    Object__set(object, value, Object__Undefined());
                    return Object__get(object, value);
                } else {
                    return ret;
                }
            } else {
                Object__set(object, value, Object__Undefined());
                return Object__get(object, value);
            }
        } else {
            return ret;
        }
    } else {
        if (object->type) {
            Object* ret = Object__getFromType(object, value);
            if (!ret) {
                puts("Cannot get from native value!");
                exit(1);
            } else {
                return ret;
            }
        } else {
            return undefined;
        }
    }
}

bool Object__equals(Object* a, Object* b) {
    if (a == b) { return true; }
    if (!a || !b) { return false; }
    if (a->type != b->type) { return false; }

    if (a->native && b->native) {
        if (Object__is(a, t_Number)) {
            return Object__getNumber(a) == Object__getNumber(b);
        } else if (Object__is(a, t_Boolean)) {
            return Object__getBoolean(a) == Object__getBoolean(b);
        } else if (Object__is(a, t_String)) {
            return strcmp(Object__getString(a), Object__getString(b)) == 0;
        } else if (Object__is(a, t_Undefined)) {
            return true;
        } else if (Object__is(a, t_Function)) {
            return true;
        } else {
            return false;
        }
    } else {
        return ObjectNode__equals(a->value.node, b->value.node);
    }
}

Object* Object__apply(Object* object, int argc, Object* argv[]) {
    if (Object__is(object, t_Function)) {
        if (object->value.function->native) {
            return (object->value.function->value.nf)(argc, argv);
        } else {
            return undefined; // User defined functions
        }
    } else if (Object__has(object, object->name)) {
       return Object__apply(Object__get(object, object->name), argc, argv);
    }

    return object;
}

static int indentation = 0;
void Object__print(Object* object) {
    if (object == NULL) { return; }

    if (Object__is(object, t_Number)) {
        printf("%g", object->value.number);
    } else if (Object__is(object, t_String)) {
        printf("%s", object->value.string);
    } else if (Object__is(object, t_Boolean)) {
        if (object->value.boolean) {
            printf("<true>");
        } else {
            printf("<false>");
        }
    } else if (Object__is(object, t_Function)) {
        printf("<Function>");
    } else if (Object__is(object, t_Undefined)) {
        printf("<undefined>");
    } else {
        printf("{ [%s]\n", object->type->name);
        ObjectNode__print(object->value.node, ++indentation);
        --indentation;

        int i;
        for (i = 0; i < indentation; ++i) {
            printf("  ");
        }
        printf("}");
    }
}

