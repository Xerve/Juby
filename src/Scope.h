#ifndef Scope_h
#define Scope_h

typedef struct _Scope Scope;

#include "Object.h"

Scope* Scope__create(Object* context);
Object* Scope__addGarbage(Scope* scope, Object* object);
Object* Scope__getVariable(Scope* scope, char* name);
void Scope__collectGarbage(Scope* scope, bool all);
Object* Scope__delete(Scope* scope);
void Scope__destroy(Scope* scope);

#endif
