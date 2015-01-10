#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ObjectNode.h"

struct _ObjectNode {
    struct _ObjectNode* left;
    struct _ObjectNode* right;
    struct _ObjectNode* parent;
    char* value;
    Object* object;
};

Object* ObjectNode__define(ObjectNode* root, char* value, Object* object) {
    if (!value) {
        puts("Can't define a NULL property!");
        exit(1);
    }

    if (!object) {
        puts("Can't define a NULL attribute!");
        exit(1);
    }

    if (!root) {
        // (*root) = malloc(sizeof(ObjectNode));
        // (*root)->value = malloc((strlen(value) + 1) * sizeof(char));
        // strcpy((*root)->value, value);
        // (*root)->object = object;
        // (*root)->left = NULL;
        // (*root)->right = NULL;
        // return (*root)->object;
        return object;
    }

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
            return object;
        } else {
            root->left->object = object;
            return object;
        }
        //return ObjectNode__define(&((*root)->left), value, object);
    }

    if (lt == 0) {
        root->object = object;
        return object;
        // (*root)->object = object;
        // return (*root)->object;
    }

    if (lt > 0) {
        if (!root->right) {
            root->right = malloc(sizeof(ObjectNode));
            root->right->value = malloc((strlen(value) + 1) * sizeof(char));
            strcpy(root->right->value, value);
            root->right->object = object;
            root->right->left = NULL;
            root->right->right = NULL;
            root->right->parent = root;
            return object;
        } else {
            root->right->object = object;
            return object;
        }
        //return ObjectNode__define(&((*root)->right), value, object);
    }

    return NULL;
}

Object* ObjectNode__get(ObjectNode** root, char* value) {
    if (!(*root)) {
        return undefined;
    }

    int lt = strcmp(value, (*root)->value);

    if (lt < 0) {
        return ObjectNode__get(&((*root)->left), value);
    }

    if (lt == 0) {
        return (*root)->object;
    }

    if (lt > 0) {
        return ObjectNode__get(&((*root)->right), value);
    }

    return NULL;
}

void ObjectNode__free(ObjectNode* root) {
    if (!root) {
        return;
    }

    delete_Object(root->object);
    ObjectNode__delete(root->left);
    ObjectNode__delete(root->right);
}

void ObjectNode__delete(ObjectNode* root) {
    ObjectNode__free(root);

    if (root) {
        free(root->value);
    }

    free(root);
}

void ObjectNode__print(ObjectNode* node, int indentation) {
    if (!node) {
        return;
    }

    if (!node->object) {
        return;
    }

    if (node->object == undefined) {
        return;
    }

    int i;
    for (i = 0; i < indentation; ++i) {
        printf("  ");
    }

    printf("%s: ", node->value);
    print_Object(node->object);
    ObjectNode__print(node->left, indentation);
    ObjectNode__print(node->right, indentation);
}
