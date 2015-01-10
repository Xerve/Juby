#include "Object.h"
#include "ObjectNode.h"
#include "Scope.h"
#include "Interpreter.h"

#define PreludeFunc(name) Object__set(p, #name, Object__nFunction(name))

Scope* Prelude(void);
