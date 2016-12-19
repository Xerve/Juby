#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ObjectNode.h"

struct _ObjectNode {
    ObjectNode* left;
    ObjectNode* right;
    ObjectNode *parent;

    char* value;
    Object* object;
};

 char* ObjectNode__getValue(ObjectNode* node) { return node->value; }
 Object* ObjectNode__getObject(ObjectNode* node) { return node->object; }

ObjectNode* ObjectNode__create(void) {
    ObjectNode* node = malloc(sizeof(ObjectNode));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->value = NULL;
    node->object = NULL;

    return node;
}

void ObjectNode__free(ObjectNode* node) {
    if (!node) { return; }
    Object__delete(node->object);
    ObjectNode__delete(node->left);
    ObjectNode__delete(node->right);
}

void ObjectNode__delete(ObjectNode* node) {
    ObjectNode__free(node);
    if (node) { free(node->value); }
    free(node);
}

bool ObjectNode__equals(ObjectNode* a, ObjectNode* b) {
    if (a == b) { return true; }
    if (!a || !b) { return false; }
    return Object__equals(a->left->object, b->left->object) && Object__equals(a->right->object, b->right->object);
}

ObjectNode* ObjectNode__copy(ObjectNode* node) {
    if (!node) { return NULL; }
    if (!node->value) { return ObjectNode__create(); }

    ObjectNode* n = malloc(sizeof(ObjectNode));
    n->object = Object__copy(node->object);
    n->value = malloc((strlen(node->value) + 1) * sizeof(char));
    strcpy(n->value, node->value);
    n->left = ObjectNode__copy(node->left);
    if (n->left) { n->left->parent = n; }
    n->right = ObjectNode__copy(node->right);
    if (n->right) { n->right->parent = n; }

    return n;
}

void ObjectNode__do(ObjectNode* node, void (*func)(ObjectNode*)) {
    if (!node) { return; }
    if (node->left) { ObjectNode__do(node->left, func); }
    (*func)(node);
    if (node->right) { ObjectNode__do(node->right, func);}
}

void ObjectNode__set(ObjectNode* root, char* value, Object* object) {
    if (!root) { puts("Can't set on NULL ObjectNode!"); exit(1); }
    if (!value) { puts("Cannot set a NULL value on ObjectNode"); exit(1); }
    if (!object) { puts("Cannot set a NULL object on ObjectNode"); exit(1); }

    if (!root->value) {
        root->value = malloc((strlen(value) + 1) * sizeof(char));
        strcpy(root->value, value);
        root->object = object;
    } else {
        int lt = strcmp(value, root->value);

        if (lt < 0) {
            if (!root->left) {
                root->left = malloc(sizeof(ObjectNode));
                root->left->value = malloc((strlen(value) + 1) * sizeof(char));
                strcpy(root->left->value, value);
                root->left->object = object;
                root->left->left = NULL;
                root->left->right = NULL;
                root->left->parent = root;
            } else {
                ObjectNode__set(root->left, value, object);
            }
        } else if (lt > 0) {
            if (!root->right) {
                root->right = malloc(sizeof(ObjectNode));
                root->right->value = malloc((strlen(value) + 1) * sizeof(char));
                strcpy(root->right->value, value);
                root->right->object = object;
                root->right->left = NULL;
                root->right->right = NULL;
                root->right->parent = root;
            } else {
                ObjectNode__set(root->right, value, object);
            }
        } else if (lt == 0) {
            root->object = object;
        }
    }
}

Object* ObjectNode__get(ObjectNode* root, char* value) {
    if (!root) { return NULL; }
    if (!root->value) { return NULL; }

    int lt = strcmp(value, root->value);
    if (lt < 0) { return ObjectNode__get(root->left, value); }
    if (lt > 0) { return ObjectNode__get(root->right, value); }
    if (lt == 0) { return root->object; }

    return undefined;
}

static int __indentation = 0;
static void _ObjectNode__print(ObjectNode* node) {
    if (node->object && node->object != undefined) {
        int i;
        for (i = 0; i < __indentation; ++i) { printf("  "); }

        printf("%s: ", node->value);
        Object__print(node->object);
        printf("\n");
    }
}
void ObjectNode__print(ObjectNode* root, int indentation) {
    if (!root) { return; }
    if (!root->object) { return; }

    int old_indentation = __indentation;
    __indentation = indentation;
    ObjectNode__do(root, _ObjectNode__print);
    __indentation = old_indentation;
}
