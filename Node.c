struct _Object;
struct _Object* delete_Object(struct _Object*);

typedef struct _Node {
    struct _Node* left;
    struct _Node* right;
    char* value;
    struct _Object* object;
} Node;

struct _Object* define_Node(Node** root, char* value, struct _Object* object) {
    if (!value) {
        puts("Can't define a NULL property!");
        exit(1);
    }
    
    if (!object) {
        puts("Can't define a NULL attribute!");
        exit(1);
    }
    
    if (!(*root)) {
        (*root) = malloc(sizeof(Node));
        (*root)->value = value;
        (*root)->object = object;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return (*root)->object;
    }

    int lt = strcmp(value, (*root)->value);
    
    if (lt < 0) {
        return define_Node(&((*root)->left), value, object);
    }
    
    if (lt == 0) {
        delete_Object((*root)->object);
        (*root)->object = object;
        return (*root)->object;
    }
    
    if (lt > 0) {
        return define_Node(&((*root)->right), value, object);
    }
    
    return NULL;
}

void delete_Node(Node* root);

void free_Node(Node* root) {
    if (!root) {
        return;
    }
    delete_Object(root->object);
    delete_Node(root->left);
    delete_Node(root->right);
    
    return;
}

void delete_Node(Node* root) {
    free_Node(root);
    free(root);
    
    return;
}

struct _Object* new_Undefined(void);


struct _Object* get_Node(Node* root, char* value) {
    if (!root) {
        return define_Node(&root, value, new_Undefined());
    }
    
    int lt = strcmp(value, root->value);
    
    if (lt < 0) {
        return get_Node(root->left, value);
    }
    
    if (lt == 0) {
        return root->object;
    }
    
    if (lt > 0) {
        return get_Node(root->right, value);
    }
    
    return NULL;
}

int indentation;
struct _Object* print_Object(struct _Object* object);

void print_Node(Node* node) {
    if (!node) {
        return;
    }
    
    if (!node->object) {
        return;
    }
    
    int i;
    for (i = 0; i < indentation; ++i) {
        printf("  ");
    }
    printf("%s: ", node->value);
    print_Object(node->object);
    print_Node(node->left);
    print_Node(node->right);
    
    return;
}