#ifndef ObjectNode_h
#define ObjectNode_h

#define ForObjectNode(i, node) ObjectNode* __node_end = ObjectNode__end(node); \
                               for(i = ObjectNode__start(node); i != NULL; i = ObjectNode__iter(i, __node_end))

typedef struct _ObjectNode ObjectNode;

#include "Object.h"

inline char* ObjectNode__getValue(ObjectNode* node);
inline Object* ObjectNode__getObject(ObjectNode* node);

ObjectNode* ObjectNode__create(void);
void ObjectNode__free(ObjectNode* node);
void ObjectNode__delete(ObjectNode*node);

ObjectNode* ObjectNode__start(ObjectNode* root);
ObjectNode* ObjectNode__end(ObjectNode* root);
ObjectNode* ObjectNode__next(ObjectNode* node);
ObjectNode* ObjectNode__iter(ObjectNode* iter, ObjectNode* end);

void ObjectNode__set(ObjectNode* root, char* value, Object* object);
Object* ObjectNode__get(ObjectNode* root, char* value);
void ObjectNode__print(ObjectNode* root, int indentation);
#endif
