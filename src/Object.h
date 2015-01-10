#ifndef Object_h
#define Object_h

#define undefined &__undefined

typedef struct _Object Object;
typedef struct _Function Function;

#include "utils.h"
#include "ObjectNode.h"
#include "Interpreter.h"
#include "Scope.h"

typedef Object* (*nativeFunction)(Scope*, Object**, int);

extern Object __undefined;

inline static bool Object_is(Object* object, char* type);

inline char* Object_name(Object* object);
inline Object* Object_parent(Object* object);
inline void set_Object_name(Object* object, char* name);
inline void set_Object_parent(Object* object, Object* parent);

Object* new_String(char* value);
Object* new_Boolean(bool value);
Object* new_Number(double value);
Object* new_uFunction(char* value);
Object* new_nFunction(nativeFunction value);
Object* new_Undefined(void);
Object* new_Object(char* type);

Object* set_Property(Object* root, char* value, Object* attr);
Object* get_Property(Object* root, char* value);
Object* delete_Property(Object* root, char* value);

Object* delete_Object(Object* object);
Object* print_Object(Object* object);
Object* apply_Object(Scope* context, Object* object, Object* args[], int argc);

#endif
