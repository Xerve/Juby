#ifndef Interpreter_h
#define Interpreter_h

#include "utils.h"
#include "Object.h"
#include "Scope.h"

char* substring(char* string, int position, int length);
Object* eval(Scope* scope, char* input);
Object* eval_lines(Scope* scope, char* input);

#endif
