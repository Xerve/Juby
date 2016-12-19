#ifndef Object_h
#define Object_h

#include <stdbool.h>

#define undefined &__undefined
#define t_Any &__t_Any
#define t_Undefined &__t_Undefined
#define t_String &__t_String
#define t_Boolean &__t_Boolean
#define t_Number &__t_Number
#define t_Function &__t_Function
#define t_Prelude &__t_Prelude
#define t_Object &__t_Object
#define t_Array &__t_Array

#define STACK_OBJECT(X) extern Object __##X
#define STACK_OBJECT_INIT(X) Object __##X = {false, true, true, t_Any, NULL, NULL, NULL}
#define STACK_OBJECT_INHERITS(X, Y) Object __##X = {false, true, true, Y, NULL, NULL, NULL}
#define STACK_OBJECT_RT(X) __##X.value.node = ObjectNode__create()

typedef struct _Object Object;
typedef struct _Function Function;

#include "ObjectNode.h"

typedef Object* (*nFunc)(int, Object**);

STACK_OBJECT(undefined);
STACK_OBJECT(t_Any);
STACK_OBJECT(t_Undefined);
STACK_OBJECT(t_String);
STACK_OBJECT(t_Boolean);
STACK_OBJECT(t_Number);
STACK_OBJECT(t_Function);
STACK_OBJECT(t_Prelude);
STACK_OBJECT(t_Object);
STACK_OBJECT(t_Array);

void TYPE__INIT(void);

 char* Object__getName(Object* object);
 void Object__setName(Object* object, char* name);
 Object* Object__getParent(Object* object);
 void Object__setParent(Object* object, Object* parent);
 Object* Object__getType(Object* object);
 void Object__setType(Object* object, Object* type);
 bool Object__getGC(Object* object);
 void Object__setGC(Object* object, bool gc);
 char* Object__getString(Object* object);
 bool Object__getBoolean(Object* object);
 double Object__getNumber(Object* object);

Object* Object__create(void);
Object* Object__String(char* value);
Object* Object__Boolean(bool value);
Object* Object__Number(double value);
Object* Object__uFunction(char* value);
Object* Object__nFunction(nFunc value);
Object* Object__Undefined(void);
Object* Object__Object(Object* type);
void Object__delete(Object* object);
Object* Object__copy(Object* object);

bool Object__is(Object* object, Object* type);

void Object__set(Object* object, char* value, Object* attr);
void Object__unset(Object* object, char* value);
bool Object__has(Object* object, char* value);
bool Object__hasWithType(Object* object, char* value);
Object* Object__get(Object* object, char* value);
bool Object__equals(Object* a, Object* b);
Object* Object__apply(Object* object, int argc, Object* argv[]);
void Object__print(Object* object);

#endif
