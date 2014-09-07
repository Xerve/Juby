#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define undefined &_undefined
#define new(type) malloc(sizeof((type)))

typedef enum { false, true } bool;

typedef struct base_symbol {
    char** value;
    unsigned int len;
} Symbol;

Symbol* Symbol_new(char* value) {
    Symbol* symbol = malloc(sizeof(Symbol));
    symbol->value = malloc(sizeof(value));
    *(symbol->value) = value;
    symbol->len = strlen(value);
    return symbol;
}

bool Symbol_equals(Symbol* A, char* B) {
    if (!A) {
        return false;
    }
    if (sizeof(*(A->value)) != sizeof(B)) {
        return false;
    }

    unsigned int i;
    for (i = 0; i < A->len; i++) {
        if ((*(A->value))[i] != B[i]) {
            return false;
        }
    }
    return true;
}

int Symbol_in_array(Symbol** array, unsigned int len, char* symbol) {
    int i;
    for (i = 0; i < len; i++) {
        if (Symbol_equals(array[i], symbol)) {
            return i;
        }
    }
    return -1;
}

void Symbol_delete(Symbol* symbol) {
    free(symbol->value);
    free(symbol);
}

typedef struct base_object {
    Symbol* type;
    union {
        int* i;
        long* l;
        float* f;
        char** c;
        bool* b;
    } value;
    Symbol** keys;
    struct base_object** values;
    unsigned int len;
    unsigned int size;
    struct base_object* parent;
} Object;

char* Object_typeof(Object* object) {
    return *(object->type->value);
}

bool Object_istype(Object* object, char* type) {
    return Symbol_equals(object->type, type);
}

Object* Object_new(char* type_c, Object* parent) {
    Symbol* type = Symbol_new(type_c);
    Object* object = malloc(sizeof(Object));
    object->type = type;
    object->parent = parent;
    object->keys = malloc(sizeof(Symbol*) * 5);
    object->values = malloc(sizeof(Object*) * 5);
    object->len = 0;
    object->size = 5;

    return object;
}

char* ___undefined = "null";
Symbol __undefined = {.value = &___undefined, .len = 4};
Object _undefined = {.type = &__undefined};

void Object_delete(Object* object) {
    unsigned int i;
    if (object->len != 0) {
        for (i = 0; i < object->len; ++i) {
            Symbol_delete(object->keys[i]);
            Object_delete(object->values[i]);
        }
    }

    if (Object_istype(object, "int")) {
        free(object->value.i);
    } else if (Object_istype(object, "str")) {
        free(object->value.c);
    } else if (Object_istype(object, "num")) {
        free(object->value.f);
    } else if (Object_istype(object, "long")) {
        free(object->value.l);
    } else if (Object_istype(object, "bool")) {
        free(object->value.b);
    } else if (Object_istype(object, "function")) {
        free(object->value.c);
    }

    Symbol_delete(object->type);
    free(object->keys);
    free(object->values);
    free(object);
}

void Object_set(Object* object, char* key, Object* value) {
    int position = Symbol_in_array(object->keys, object->len, key);
    if (position == -1) {
        if (object->len == object->size) {
            object->size *= 2;
            object->keys = (Symbol**) realloc(object->keys, sizeof(Symbol*) * object->size);
            object->values = (Object**) realloc(object->values, sizeof(Object*) * object->size);
        }
        value->parent = object;
        object->keys[object->len] = Symbol_new(key);
        object->values[object->len] = value;
        object->len++;
    } else {
        Object_delete(object->values[position]);
        object->values[position] = value;
    }
}

Object* Object_get(Object* object, char* key) {
    int position = Symbol_in_array(object->keys, object->len, key);
    if (position == -1) {
        return undefined;
    } else {
        return (object->values)[position];
    }
}

Object* Object_int(int value) {
    int* new_value = malloc(sizeof(value));
    *new_value = value;

    Object* new_object = Object_new("int", undefined);
    new_object->value.i = new_value;

    return new_object;
}

int* Object_int_value(Object* object) {
    if (!Object_istype(object, "int")) {
        puts("Error accessing int-value of a non-int!");
        exit(1);
    }

    return object->value.i;
}

Object* Object_str(char* value) {
    char** new_value = malloc(sizeof(value));
    *new_value = value;

    Object* new_object = Object_new("str", undefined);
    new_object->value.c = new_value;

    Object_set(new_object, "len", Object_int(strlen(value)));
    return new_object;
}

char** Object_str_value(Object* object) {
    if (!Object_istype(object, "str")) {
        puts("Error accessing str-value of a non-str!");
        exit(1);
    }
    return object->value.c;
}

Object* Object_long(long value) {
    long* new_value = malloc(sizeof(long));
    *new_value = value;

    Object* new_object = Object_new("long", undefined);
    new_object->value.l = new_value;

    return new_object;
}

long* Object_long_value(Object* object) {
    if (!Object_istype(object, "long")) {
        puts("Error accessing long-value of a non-long!");
        exit(1);
    }

    return object->value.l;
}

Object* Object_num(float value) {
    float* new_value = malloc(sizeof(float));
    *new_value = value;

    Object* new_object = Object_new("num", undefined);
    new_object->value.f = new_value;

    return new_object;
}

float* Object_num_value(Object* object) {
    if (!Object_istype(object, "num")) {
        puts("Error accessing num-value of a non-num!");
        exit(1);
    }

    return object->value.f;
}

Object* Object_bool(bool value) {
    bool* new_value = malloc(sizeof(bool));
    *new_value = value;

    Object* new_object = Object_new("bool", undefined);
    new_object->value.b = new_value;

    return new_object;
}

bool* Object_bool_value(Object* object) {
    if (!Object_istype(object, "bool")) {
        puts("Error accessing bool-value of a non-bool!");
        exit(1);
    }

    return object->value.b;
}

Object* Object_add(Object* A, Object* B) {
    if (Object_istype(A, "null") || Object_istype(B, "null")) {
        return undefined;
    } else if (Object_istype(A, "str")) {
        if (Object_istype(B, "str")) {
            int A_len = Object_int_value(Object_get(A, "len"));
            int B_len = Object_int_value(Object_get(B, "len"));
            char new_string[A_len + B_len + 1];
            int i;
            for (i = 0; i < A_len; i++) {
                new_string[i] = (*(Object_str_value(A)))[i];
            }
            for (i = 0; i < B_len; i++) {
                new_string[i + A_len] = (*(Object_str_value(B)))[i];
            }
            new_string[A_len + B_len] = '\0';
            return Object_str(new_string);
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "int")) {
        if (Object_istype(B, "int")) {
            return Object_int(*Object_int_value(A) + *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long((long) *Object_int_value(A) + *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_int_value(A) + *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "long")) {
        if (Object_istype(B, "int")) {
            return Object_long(*Object_long_value(A) + (long) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long(*Object_long_value(A) + *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_long_value(A) + *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "num")) {
        if (Object_istype(B, "int")) {
            return Object_num(*Object_num_value(A) + (float) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_num(*Object_num_value(A) + (float) *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num(*Object_num_value(A) + *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "bool")) {
        if (Object_istype(B, "bool")) {
            return Object_bool(*Object_bool_value(A) || *Object_bool_value(B));
        } else {
            return undefined;
        }
    } else {
        Object* new_object = Object_new(Object_typeof(A), undefined);
        int i;
        if (A->len != 0) {
            for (i = 0; i < A->len; i++) {
                Object_set(new_object, *(A->keys[i]->value), A->values[i]);
            }
        }
        if (B->len != 0) {
            for (i = 0; i < B->len; i++) {
                Object_set(new_object, *(B->keys[i]->value), B->values[i]);
            }
        }
        return new_object;
    }
}

Object* Object_subtract(Object* A, Object* B) {
    if (Object_istype(A, "int")) {
        if (Object_istype(B, "int")) {
            return Object_int(*Object_int_value(A) - *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long((long) *Object_int_value(A) - *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_int_value(A) - *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "long")) {
        if (Object_istype(B, "int")) {
            return Object_long(*Object_long_value(A) - (long) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long(*Object_long_value(A) - *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_long_value(A) - *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "num")) {
        if (Object_istype(B, "int")) {
            return Object_num(*Object_num_value(A) - (float) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_num(*Object_num_value(A) - (float) *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num(*Object_num_value(A) - *Object_num_value(B));
        } else {
            return undefined;
        }
    } else {
        return undefined;
    }
}

Object* Object_multiply(Object* A, Object* B) {
    if (Object_istype(A, "int")) {
        if (Object_istype(B, "int")) {
            return Object_int(*Object_int_value(A) * *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long((long) *Object_int_value(A) * *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_int_value(A) * *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "long")) {
        if (Object_istype(B, "int")) {
            return Object_long(*Object_long_value(A) * (long) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long(*Object_long_value(A) * *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_long_value(A) * *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "num")) {
        if (Object_istype(B, "int")) {
            return Object_num(*Object_num_value(A) * (float) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_num(*Object_num_value(A) * (float) *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num(*Object_num_value(A) * *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "bool")) {
        if (Object_istype(B, "bool")) {
            return Object_bool(*Object_bool_value(A) && *Object_bool_value(B));
        } else {
            return undefined;
        }
    } else {
        return undefined;
    }
}

Object* Object_divide(Object* A, Object* B) {
    if (Object_istype(A, "int")) {
        if (Object_istype(B, "int")) {
            return Object_int(*Object_int_value(A) / *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long((long) *Object_int_value(A) / *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_int_value(A) / *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "long")) {
        if (Object_istype(B, "int")) {
            return Object_long(*Object_long_value(A) / (long) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_long(*Object_long_value(A) / *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num((float) *Object_long_value(A) / *Object_num_value(B));
        } else {
            return undefined;
        }
    } else if (Object_istype(A, "num")) {
        if (Object_istype(B, "int")) {
            return Object_num(*Object_num_value(A) / (float) *Object_int_value(B));
        } else if (Object_istype(B, "long")) {
            return Object_num(*Object_num_value(A) / (float) *Object_long_value(B));
        } else if (Object_istype(B, "num")) {
            return Object_num(*Object_num_value(A) / *Object_num_value(B));
        } else {
            return undefined;
        }
    } else {
        return undefined;
    }
}

void print_Object(Object* object, int level) {
    char small[level + 1];
    char extra[level + 2];
    int i;
    for (i = 0; i < level + 1; i++) {
        small[i] = '\t';
        extra[i] = '\t';
    }
    small[level] = '\0';
    extra[level + 1] = '\0';
    if (Object_istype(object, "null")) {
        printf("undefined\n");
    } else if (Object_istype(object, "int")) {
        printf("%d\n", *Object_int_value(object));
    } else if (Object_istype(object, "str")) {
        printf("%s\n", *Object_str_value(object));
    } else if (Object_istype(object, "long")) {
        printf("%ld\n", *Object_long_value(object));
    } else if (Object_istype(object, "num")) {
        printf("%f\n", *Object_num_value(object));
    } else if (Object_istype(object, "bool")) {
        if (*Object_bool_value(object)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    } else {
        printf("{");
        if (object->len != 0) {
            printf("\n");
            for (i = 0; i < object->len; i++) {
                printf("%s%s: ", extra, *(object->keys[i]->value));
                print_Object(object->values[i], level + 1);
            }
            printf("%s} [%s]\n", small, Object_typeof(object));
        } else {
            printf(" } [%s]\n", Object_typeof(object));
        }
    }
}

void print_Object_memory(Object* object) {
    printf("$%p | ", object);
    if (Object_istype(object, "int")) {
        printf("%d\n", *Object_int_value(object));
    } else if (Object_istype(object, "str")) {
        printf("%s\n", *Object_str_value(object));
    } else if (Object_istype(object, "long")) {
        printf("%ld\n", *Object_long_value(object));
    } else if (Object_istype(object, "num")) {
        printf("%f\n", *Object_num_value(object));
    } else {
        printf("Object [%s]\n", Object_typeof(object));

        if (object->len != 0) {
            int i;
            for(i = 0; i < object->len; i++) {
                print_Object_memory(object->values[i]);
            }
        }
    }
}

int main(int argc, const char* argv[]) {
    Object* A = Object_new("A", undefined);
    Object_set(A, "A", Object_int(9));
    Object_set(A, "B", Object_bool(true));

    Object* B = Object_new("B", undefined);
    Object_set(B, "B", Object_long(200L));
    Object_set(B, "C", Object_str("YYY"));

    print_Object(Object_add(A, B), 0);

    return 0;
}
