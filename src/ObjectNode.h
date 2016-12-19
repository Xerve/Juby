#ifndef ObjectNode_h
#define ObjectNode_h

typedef struct _ObjectNode ObjectNode;

#include "Object.h"

 char* ObjectNode__getValue(ObjectNode* node);
 Object* ObjectNode__getObject(ObjectNode* node);

ObjectNode* ObjectNode__create(void);
void ObjectNode__free(ObjectNode* node);
void ObjectNode__delete(ObjectNode* node);
bool ObjectNode__equals(ObjectNode* a, ObjectNode* b);
ObjectNode* ObjectNode__copy(ObjectNode* node);

void ObjectNode__do(ObjectNode* node, void (*func)(ObjectNode*));

void ObjectNode__set(ObjectNode* root, char* value, Object* object);
Object* ObjectNode__get(ObjectNode* root, char* value);
void ObjectNode__print(ObjectNode* root, int indentation);

#endif
