#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Node.h"

struct _Node {
    struct _Node* left;
    struct _Node* right;
    char* value;
    Object* object;
};

Object* define_Node(Node** root, char* value, Object* object) {
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
        (*root)->value = malloc((strlen(value) + 1) * sizeof(char));
        strcpy((*root)->value, value);
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

Object* get_Node(Node** root, char* value) {
    if (!(*root)) {
        return undefined;
    }

    int lt = strcmp(value, (*root)->value);

    if (lt < 0) {
        return get_Node(&((*root)->left), value);
    }

    if (lt == 0) {
        return (*root)->object;
    }

    if (lt > 0) {
        return get_Node(&((*root)->right), value);
    }

    return NULL;
}

void free_Node(Node* root) {
    if (!root) {
        return;
    }

    delete_Object(root->object);
    delete_Node(root->left);
    delete_Node(root->right);
}

void delete_Node(Node* root) {
    free_Node(root);

    if (root) {
        free(root->value);
    }

    free(root);
}

void print_Node(Node* node, int indentation) {
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
    print_Node(node->left, indentation);
    print_Node(node->right, indentation);
}
