#define undefined &__undefined

typedef struct _Object {
    bool native;
    char* type;
    union {
        char* string;
        bool boolean;
        int integer;
        float number;
        Node* node;
    } value;
    bool gc;
} Object;

Object __undefined = {true, "undefined"};

Object* new_String(char* value) {
    Object* object = malloc(sizeof(Object));
    object->type = "String";
    object->native = true;
    object->value.string = value;
    object->gc = true;
    return object;
}
 
Object* new_Boolean(bool value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Boolean";
    object->native = true;
    object->value.boolean = value;
    object->gc = true;
    return object;
}

Object* new_Integer(int value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Integer";
    object->native = true;
    object->value.integer = value;
    object->gc = true;
    return object;
}

Object* new_Number(float value) {
    Object* object = malloc(sizeof(Object));
    object->type = "Number";
    object->native = true;
    object->value.number = value;
    object->gc = true;
    return object;
}

Object* new_Undefined(void) {
    Object* object = malloc(sizeof(Object));
    object->type = "undefined";
    object->native = true;
    object->gc = true;
    return object;
} 

Object* new_Object(char* type) {
    Object* object = malloc(sizeof(Object));
    object->type = type;
    object->native = false;
    object->value.node = NULL;
    object->gc = true;
    return object;
}

Object* set_Property(Object* root, char* value, Object* attr) {
    if (!root) {
        puts("Can't set property on NULL object!");
        exit(1);
    }
    
    if (root->native) {
        puts("Can't set on a native type!");
        exit(1);
    }
    
    attr->gc = false;
    return define_Node(&(root->value.node), value, attr);
}

Object* get_Property(Object* root, char* value) {
    if (!root) {
        puts("Can't get property of NULL object!");
        exit(1);
    }
    
    if (root->native) {
        puts("Can't get property of native type!");
        exit(1);
    }
    
    return get_Node(root->value.node, value);
}

Object* delete_Object(Object* object) {
    if (!object) {
        return undefined;
    }
    
    if (!object->native) {
        delete_Node(object->value.node);
    }
    
    free(object);
    
    return undefined;
}

bool Object_is(Object* object, char* type) {
    if (!strcmp(object->type, type)) {
        return true;
    }
    
    return false;
}

int indentation = 0;

Object* print_Object(Object* object) {
    if (!object) {
        return undefined;    
    }
    
    if (Object_is(object, "Integer")) {
        printf("%d\n", object->value.integer);
    } else if (Object_is(object, "Number")) {
        printf("%f\n", object->value.number);
    } else if (Object_is(object, "String")) {
        printf("\"%s\"\n", object->value.string);
    } else if (Object_is(object, "Boolean")) {
        if (object->value.boolean) {
            puts("true");
        } else {
            puts("false");
        }
    } else if (Object_is(object, "undefined")) {
        puts("undefined");        
    } else {
        printf("{ [%s]\n", object->type);
        ++indentation;
        print_Node(object->value.node);
        --indentation;
        
        int i;
        for (i = 0; i < indentation; ++i) {
            printf("  ");
        }
        puts("}");
    }
    
    return object;
}