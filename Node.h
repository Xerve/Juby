#ifndef Node_h
#define Node_h

#include "Object.h"

typedef struct _Node Node;

struct _Object* define_Node(Node** root, char* value, struct _Object* object);
struct _Object* get_Node(Node* root, char* value);

void free_Node(Node* root);
void delete_Node(Node* root);
void print_Node(Node* node, int indentation);

#endif