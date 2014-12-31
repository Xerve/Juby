#ifndef Scope_h
#define Scope_h

typedef struct _Scope Scope;

#include "Object.h"

Scope* create_Scope(Object* context);
void add_Garbage(Scope* scope, Object* object);
Object* get_Variable(Scope* scope, char* name);
void collect_Garbage(Scope* scope);
Object* delete_Scope(Scope* scope);
void destroy_Scope(Scope* scope);

#endif
