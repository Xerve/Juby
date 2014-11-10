#ifndef Interpreter_h
#define Interpreter_h

#include "utils.h"
#include "Object.h"

char* substring(char* string, int position, int length);
Object* eval(Object* content, char* input);

#endif