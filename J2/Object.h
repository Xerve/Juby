#ifndef Object_h
#define Object_h

#include <stdbool.h>

#define undefined &__undefined
#define t_Any &__t_Any
#define t_String &__t_String
#define t_Boolean &__t_Boolean
#define t_Number &__t_Number
#define t_Function &__t_Function

typedef struct _Object Object;
typedef struct _Function Function;

#include "ObjectNode.h"

typedef Object* (*nFunc)(int, Object**);

extern Object __undefined;
extern Object __t_Any;
extern Object __t_String;
extern Object __t_Boolean;
extern Object __t_Number;
extern Object __t_Function;

void TYPE__INIT(void);

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
void Object__unset(Object* object, char* value);
Object* Object__get(Object* object, char* value);
Object* Object__apply(Object* object, int argc, Object* argv[]);
void Object__print(Object* object);

#endif
