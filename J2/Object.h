#ifndef Object_h
#define Object_h

#define undefined &__undefined

typedef struct _Object Object;
typedef struct _Function Function;

#include "ObjectNode.h"
#include "Scope.h"

typedef Object* (*nFunc)(Scope*, int, Object**);

extern Object __undefined;
extern Object* t_Any;
extern Object* t_String;
extern Object* t_Boolean;
extern Object* t_Number;
extern Object* t_Function;

inline bool Object__is(Object* object, Object* type);

inline char* Object__getName(Object* object);
inline void Object__setName(Object* object, char* name);
inline Object* Object__getParent(Object* object);
inline void Object__setParent(Object* object, Object* parent);
inline char* Object__getString(Object* object);
inline bool Object__getBoolean(Object* object);
inline double Object__getNumber(Object* object);

Object* Object__String(char* value);
Object* Object__Boolean(bool value);
Object* Object__Number(double value);
Object* Object__uFunction(char* value);
Object* Object__nFunction(nFunc value);
Object* Object__Undefined(void);
Object* Object__Object(Object* type);
void Object__delete(Object* object);

void Object__set(Object* object, char* value, Object* attr);
void Object__unset(Onject* object, char* value);
Object* Object__get(Object* object, char* value);
Object* Object__apply(Scope* scope, Object* object, int argc, Object* argv[]);
void Object__print(Object* object);

#endif
