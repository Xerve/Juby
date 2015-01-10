#ifndef ObjectNode_h
#define ObjectNode_h

#include "Object.h"

typedef struct _ObjectNode ObjectNode;

Object* ObjectNode__define(ObjectNode* root, char* value, Object* object);
Object* ObjectNode__get(ObjectNode** root, char* value);

void ObjectNode__free(ObjectNode* root);
void ObjectNode__delete(ObjectNode* root);
void ObjectNode__print(ObjectNode* node, int indentation);

#endif
