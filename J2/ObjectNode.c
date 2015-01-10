#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ObjectNode.h"

struct _ObjectNode {
    ObjectNode* left;
    ObjectNode* right;
    ObjectNode *parent;
    
    char* value;
    Object* object;
};

inline char* ObjectNode__getValue(ObjectNode* node) { return node->value; }
inline Object* ObjectNode__getObject(ObjectNode* node) { return node->object; }

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

ObjectNode* ObjectNode__start(ObjectNode* root) {
    if (!root) { return NULL; }
    if (root->left) { return ObjectNode__start(root->left); }
    
    return root;
}

ObjectNode* ObjectNode__end(ObjectNode* root) {
    if (!root) { return NULL; }
    if (root->right) { return ObjectNode__end(root->right); }
    
    return root;
}

ObjectNode* ObjectNode__next(ObjectNode* node) {
    if (node->left) { return node->left; }
    if (node->right) { return node->right; }
    if (!node->parent) { return NULL; }
    
    int lt = strcmp(node->value, node->parent->value);
    if (lt < 0) { return node->parent; }
    if (lt > 0) { return node->parent->parent; }
    if (lt == 0) { puts("The tree is reallyed fucked up"); exit(1); }

    return NULL;
}

ObjectNode* ObjectNode__iter(ObjectNode* iter, ObjectNode* end) {
    if (iter == end) { return NULL; }
    
    return ObjectNode__next(iter);
}

Object* ObjectNode__set(ObjectNode* root, char* value, Object* object) {
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
    if (!root) { return undefined; }
    
    int lt = strcmp(value, root->value);
    if (lt < 0) { return ObjectNode__get(root->left, value); }
    if (lt > 0) { return ObjectNode__get(root->right, value); }
    if (lt == 0) { return root->object; }
    
    return undefined;
}

void ObjectNode__print(ObjectNode* root, int indentation) {
    if (!root) { return; }
    if (!root->object) { return; }
    
    ObjectNode* i;
    ForObjectNode(i, root) {
        if (i->object) { Object__print(i->object); }
    }
}
