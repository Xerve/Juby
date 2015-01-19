#ifndef Interpreter_h
#define Interpreter_h

#include "Object.h"
#include "Scope.h"
#include "Prelude.h"

#define isNullChar(X) (iscntrl(X) || isspace(X))

char* substring(char* string, int position, int length);
Object* eval(Scope* scope, char* input);

#endif
