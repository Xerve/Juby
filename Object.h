#ifndef Object_h
#define Object_h

#include "utils.h"
#include "Node.h"

#define undefined &__undefined

typedef struct _Object Object;

extern Object __undefined;

Object* new_String(char* value);
Object* new_Boolean(bool value);
Object* new_Number(double value);
Object* new_Undefined(void);
Object* new_Object(char* type);

Object* set_Property(Object* root, char* value, Object* attr);
Object* get_Property(Object* root, char* value);
Object* delete_Object(Object* object);
Object* delete_Property(Object* root, char* value);
Object* print_Object(Object* object);

#endif