#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Object.h"

struct _Function {
    bool native;
    union {
        nativeFunction nf;
        char* uf;
    } value;
};

struct _Object {
    bool native;
    char* type;
    char* name;
    Object* parent;
    union {
        char* string;
        bool boolean;
        double number;
        ObjectNode* node;
        Function* function;
    } value;
};

inline static bool Object_is(Object* object, char* type) {
    return !strcmp(object->type, type) || !strcmp("Any", type);
}

inline char* Object_name(Object* object) { return object->name; }
inline Object* Object_parent(Object* object) { return object->parent; }
inline void set_Object_name(Object* object, char* name) { object->name = name; }
inline void set_Object_parent(Object* object, Object* parent) { object->parent = parent; }

Object __undefined = {true, "undefined", "undefined"};

Object* new_String(char* value) {
    Object* object = malloc(sizeof(Object));
    object->type = "String";
    object->native = true;
    object->value.string = value;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* new_Boolean(bool value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Boolean";
    object->native = true;
    object->value.boolean = value;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* new_Number(double value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Number";
    object->native = true;
    object->value.number = value;
    object->parent = NULL;
    object->name = NULL;
    return object;
}


Object* new_uFunction(char* value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Function";
    object->native = true;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = false;
    object->value.function->value.uf = value;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* new_nFunction(nativeFunction value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Function";
    object->native = true;
    object->value.function = malloc(sizeof(Function));
    object->value.function->native = true;
    object->value.function->value.nf = value;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* new_Undefined(void) {
    Object* object = malloc(sizeof(Object));
    object->type = "undefined";
    object->native = true;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* new_Object(char* type) {
    Object* object = malloc(sizeof(Object));
    object->type = malloc((strlen(type) + 1) * sizeof(char));
    strcpy(object->type, type);
    object->native = false;
    object->value.node = NULL;
    object->parent = NULL;
    object->name = NULL;
    return object;
}

Object* set_Property(Object* root, char* value, Object* attr) {
    if (!root) {
        if (attr == undefined) {
            err("Can't delete NULL object!", root, undefined);
        } else {
            err("Can't set property on NULL object!", root, undefined);
        }
    }

    if (root->native) {
        if (attr == undefined) {
            err("Can't delete native object!", root, undefined);
        } else {
            err("Can't set property on native object!", root, undefined);
        }
    }

    attr->parent = root;
    attr->name = value;
    return ObjectNode__define(root->value.node, value, attr);
}

Object* get_Property(Object* root, char* value) {
    if (!root) {
        err("Can't get property of NULL object!", root, undefined);
    }

    if (root->native) {
        err("Can't set property of native object!", root, undefined);
    }

    Object* ret = ObjectNode__get(&(root->value.node), value);
    if (ret == undefined) {
        return set_Property(root, value, new_Undefined());
    } else {
        return ret;
    }
}


Object* delete_Property(Object* root, char* value) {
    set_Property(root, value, undefined);

    return undefined;
}

Object* delete_Object(Object* object) {
    if (!object) {
        return undefined;
    }

    if (object != undefined) {
        if (!object->native) {
            free(object->type);
            ObjectNode__delete(object->value.node);
        } else if (Object_is(object, "String")) {
            free(object->value.string);
        } else if (Object_is(object, "Function")) {
            if (!object->value.function->native) {
                free(object->value.function->value.uf);
            }

            free(object->value.function);
        }

        free(object);
    }

    return undefined;
}

static int indentation = 0;
Object* print_Object(Object* object) {
    if (_panic) {
        return undefined;
    }

    if (!object) {
        return undefined;
    }

    if (Object_is(object, "Number")) {
        printf("%g\n", object->value.number);
    } else if (Object_is(object, "String")) {
        printf("'%s'\n", object->value.string);
    } else if (Object_is(object, "Boolean")) {
        if (object->value.boolean) {
            puts("true");
        } else {
            puts("false");
        }
    } else if (Object_is(object, "Function")) {
        puts("<Function>");
    } else if (Object_is(object, "undefined")) {
        puts("undefined");
    } else {
        printf("{ [%s]\n", object->type);
        ObjectNode__print(object->value.node, ++indentation);
        --indentation;

        int i;
        for (i = 0; i < indentation; ++i) {
            printf("  ");
        }
        puts("}");
    }

    return object;
}

Object* apply_Object(Scope* scope, Object* object, Object* args[], int argc) {
    if (!Object_is(object, "Function")) {
        panic("Object is not a function!", object->type);
        return undefined;
    }

    if (object->value.function == NULL) {
        return undefined;
    }

    if (object->value.function->native) {
        return (*object->value.function->value.nf)(scope, args, argc);
    } else {
        return eval_lines(scope, object->value.function->value.uf);
    }
}
